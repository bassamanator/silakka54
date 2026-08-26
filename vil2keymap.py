#!/usr/bin/env python3
"""vil2keymap.py -- convert Vial layout files (.vil) into a QMK keymap.c.

A .vil file is the JSON export of a Vial keyboard's *dynamic* configuration:
layers, macros, tap dances, combos, key overrides, alt-repeat keys and
settings.  Of all of that only the LAYERS belong in keymap.c:

  * Tap dances, combos, macros, key overrides and alt-repeat keys are
    handled by Vial itself from EEPROM (vial.c defines tap_dance_actions[]
    and key_combos[] internally), so baking them into keymap.c would cause
    duplicate-symbol errors.  They travel with the .vil file instead: flash
    the firmware, then load the .vil in Vial once to restore them.

The converter therefore regenerates just the `keymaps` array of an existing
keymap.c (everything else -- RGB code, callbacks, etc. -- is preserved), or
emits a minimal standalone keymap.c when no template is given.

Layout mapping
--------------
The .vil `layout` is a JSON matrix indexed [layer][matrix_row][matrix_col]
(10 rows x 6 cols for the silakka54).  The order of arguments in the LAYOUT
macro is taken from `keyboard.json`: its LAYOUT definition lists every key's
matrix coordinate in macro order (the right hand side is stored mirrored in
the matrix, and keyboard.json unwraps it), so no mirroring logic needs to
be hard-coded here.

Usage
-----
    python3 vil2keymap.py 26-aug.vil                        # in-place on the detected keymap.c
    python3 vil2keymap.py 26-aug.vil -o keymap.c
    python3 vil2keymap.py layout.vil --keymap-c path/to/keymap.c \
        --keyboard-json firmware/keyboard.json

Template detection: when --keymap-c is omitted the script looks under
firmware/keymaps; it picks the single keymap if there is only one, otherwise
one whose VIAL_KEYBOARD_UID matches the .vil's uid.  If it still can't decide
it errors and lists the candidates (this repo has several keymap variants, so
pass --keymap-c).

Other keyboards: --keyboard-json points at the board's keyboard.json (the
LAYOUT definition drives the conversion), and --rows lists the LAYOUT macro's
row sizes (silakka54 default: 12,12,12,12,6).
"""

import argparse
import json
import re
import sys
from pathlib import Path

# ---------------------------------------------------------------------------
# Keycode normalization.
#
# Vial serializes keycodes using QMK's long, canonical names.  The keymap.c
# in this repo uses the short aliases; both compile, these tables keep the
# generated file consistent with the rest of the keymap.  Anything not in a
# table is passed through unchanged (and is a valid QMK keycode by
# construction, since Vial only emits names the firmware understands).
# ---------------------------------------------------------------------------

# Long Vial name -> short alias used in this keymap.
KEY_ALIASES = {
    "KC_GRAVE": "KC_GRV",
    "KC_EQUAL": "KC_EQL",
    "KC_MINUS": "KC_MINS",
    "KC_SCOLON": "KC_SCLN",
    "KC_SLASH": "KC_SLSH",
    "KC_BSLASH": "KC_BSLS",
    "KC_QUOTE": "KC_QUOT",
    "KC_LBRACKET": "KC_LBRC",
    "KC_RBRACKET": "KC_RBRC",
    "KC_ENTER": "KC_ENT",
    "KC_SPACE": "KC_SPC",
    "KC_ESCAPE": "KC_ESC",
    "KC_BSPACE": "KC_BSPC",
    "KC_DELETE": "KC_DEL",
    "KC_INSERT": "KC_INS",
    "KC_CAPSLOCK": "KC_CAPS",
    "KC_PSCREEN": "KC_PSCR",
    "KC_PGDOWN": "KC_PGDN",
    "KC_RIGHT": "KC_RGHT",
    "KC_LCTRL": "KC_LCTL",
    "KC_RCTRL": "KC_RCTL",
    "KC_LSHIFT": "KC_LSFT",
    "KC_RSHIFT": "KC_RSFT",
    "KC_MS_U": "MS_UP",
    "KC_MS_D": "MS_DOWN",
    "KC_MS_L": "MS_LEFT",
    "KC_MS_R": "MS_RGHT",
    "KC_WH_U": "MS_WHLU",
    "KC_WH_D": "MS_WHLD",
    "KC_WH_L": "MS_WHLL",
    "KC_WH_R": "MS_WHLR",
    "KC_BTN1": "MS_BTN1",
    "KC_BTN2": "MS_BTN2",
    "QK_LAYER_LOCK": "QK_LLCK",
    "QK_REBOOT": "QK_RBT",
}

# US-ANSI shifted symbols: "LSFT(KC_GRAVE)" -> "KC_TILD", etc.  Keyed by the
# *inner* keycode exactly as Vial spells it (long names), so this runs before
# the generic alias pass.
SHIFTED_SYMBOLS = {
    "KC_GRAVE": "KC_TILD",
    "KC_1": "KC_EXLM",
    "KC_2": "KC_AT",
    "KC_3": "KC_HASH",
    "KC_4": "KC_DLR",
    "KC_5": "KC_PERC",
    "KC_6": "KC_CIRC",
    "KC_7": "KC_AMPR",
    "KC_8": "KC_ASTR",
    "KC_9": "KC_LPRN",
    "KC_0": "KC_RPRN",
    "KC_MINUS": "KC_UNDS",
    "KC_EQUAL": "KC_PLUS",
    "KC_LBRACKET": "KC_LCBR",
    "KC_RBRACKET": "KC_RCBR",
    "KC_BSLASH": "KC_PIPE",
    "KC_SCOLON": "KC_COLN",
    "KC_QUOTE": "KC_DQUO",
    "KC_COMMA": "KC_LABK",
    "KC_DOT": "KC_RABK",
    "KC_SLASH": "KC_QUES",
}

# Vial's modifier shorthand -> QMK macro name.  QMK defines C/A/S/G on its
# own, but the underscored combos ("C_S(KC_C)") do not exist in QMK and must
# be expanded into nested LCTL(LSFT(...)).
MOD_NAMES = {"C": "LCTL", "S": "LSFT", "A": "LALT", "G": "LGUI"}

# Functions whose first argument is a layer number (used to substitute enum
# layer names when the template keymap.c defines them).
LAYER_FN_RE = re.compile(r"\b(MO|TT|TG|OSL|TO|DF|PDF|LT|LM)\((\d+)(?=(?:,|\)))")

# Valid characters for a keycode token (QMK "Any" entries may be hex numbers).
KEYCODE_CHARS = re.compile(r"^[A-Za-z0-9_()|, ]+$")


def expand_mod_shortcuts(s):
    """Expand Vial modifier shorthands like C_S(KC_C) -> LCTL(LSFT(KC_C))."""
    pattern = re.compile(r"\b([CAGS](?:_[CAGS])*)(\((?:[^()]|\([^()]*\))*\))")

    def repl(m):
        mods = m.group(1).split("_")
        inner = m.group(2)[1:-1]  # strip the outer parentheses
        for mod in reversed(mods):
            inner = "%s(%s)" % (MOD_NAMES[mod], inner)
        return inner

    return pattern.sub(repl, s)


def normalize_keycode(kc, layer_names):
    """Turn one Vial keycode string into a QMK keycode expression."""
    if isinstance(kc, int):  # numeric "Any" entry
        return "0x%04X" % kc
    kc = kc.strip()
    if kc == "KC_NO":
        return kc
    # Vial's "LT1(KC_Y)" -> QMK "LT(1, KC_Y)" (numeric layer-tap).
    kc = re.sub(r"\bLT(\d+)\s*\(", r"LT(\1, ", kc)
    kc = expand_mod_shortcuts(kc)
    # Vial's "M0" -> QMK "MC_0" (macro keycodes; M0 is not a QMK name).
    kc = re.sub(r"\bM\((\d+)\)", r"MC_\1", kc)
    kc = re.sub(r"\bM(\d+)\b", r"MC_\1", kc)
    # Shifted US-ANSI symbols.
    for inner, out in SHIFTED_SYMBOLS.items():
        kc = re.sub(r"\bLSFT\(%s\)" % re.escape(inner), out, kc)
    # Long keycode names -> short aliases used in this keymap.
    for old, new in KEY_ALIASES.items():
        kc = re.sub(r"\b%s\b" % re.escape(old), new, kc)
    # Layer numbers -> enum layer names when the template defines them.
    if layer_names is not None:
        kc = LAYER_FN_RE.sub(
            lambda m: "%s(%s" % (m.group(1), layer_names.get(int(m.group(2)), m.group(2))),
            kc,
        )
    if not KEYCODE_CHARS.match(kc):
        raise ValueError("unexpected keycode token: %r" % kc)
    return kc


# ---------------------------------------------------------------------------
# Layout conversion.
# ---------------------------------------------------------------------------

def convert_layout(vil, layout_def, layer_names):
    """Map the .vil matrix layout onto LAYOUT() argument order.

    layout_def is keyboard.json's LAYOUT list: one {"matrix": [r, c]} entry
    per macro argument, in macro order.
    """
    matrix = vil["layout"]
    max_row = max(e["matrix"][0] for e in layout_def)
    max_col = max(e["matrix"][1] for e in layout_def)
    out_layers = []
    for li, layer in enumerate(matrix):
        if len(layer) <= max_row:
            raise SystemExit("error: layer %d has %d rows, need %d" % (li, len(layer), max_row + 1))
        args = []
        for e in layout_def:
            r, c = e["matrix"]
            if c >= len(layer[r]):
                raise SystemExit(
                    "error: layer %d row %d has %d cols, need %d" % (li, r, len(layer[r]), c + 1)
                )
            kc = layer[r][c]
            if kc == -1:
                raise SystemExit("error: layer %d matrix [%d, %d] is -1 but is part of LAYOUT" % (li, r, c))
            args.append(normalize_keycode(kc, layer_names))
        out_layers.append(args)
    return out_layers


def parse_layer_names(keymap_c_text):
    """Return {layer_index: name} from `enum layers`, or None.

    Only used when the enum's values are exactly 0..N-1 in order, which is
    how Vial numbers the dynamic layers.
    """
    text = re.sub(r"/\*.*?\*/", "", keymap_c_text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    m = re.search(r"enum\s+layers\s*\{([^}]*)\};", text)
    if not m:
        return None
    index_to_name = {}
    next_value = 0
    for part in m.group(1).split(","):
        part = part.strip()
        if not part:
            continue
        mm = re.fullmatch(r"([A-Za-z_][A-Za-z0-9_]*)(?:\s*=\s*(\d+))?", part)
        if not mm:
            return None
        name = mm.group(1)
        value = int(mm.group(2)) if mm.group(2) else next_value
        next_value = value + 1
        index_to_name[value] = name
    for i in range(len(index_to_name)):
        if i not in index_to_name:
            return None
    return index_to_name


# ---------------------------------------------------------------------------
# C code generation.
# ---------------------------------------------------------------------------

def format_keymaps(out_layers, layer_names, rows, source_name):
    lines = []
    lines.append("// Generated by vil2keymap.py from %s" % source_name)
    lines.append("const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {")
    for i, args in enumerate(out_layers):
        if layer_names is not None and i in layer_names:
            lines.append("    [%s] = LAYOUT(" % layer_names[i])
        else:
            lines.append("    [%d] = LAYOUT(" % i)
        pos = 0
        for row_len in rows:
            row = args[pos : pos + row_len]
            pos += row_len
            half = row_len // 2
            left, right = row[:half], row[half:]
            # Fixed 9-char columns, matching the rest of this keymap.
            fmt = lambda ks: ", ".join(k.ljust(9) for k in ks)  # noqa: E731
            if row_len >= 8:
                lines.append("        %s,%s%s," % (fmt(left), " " * 28, fmt(right)))
            else:
                lines.append("        %s%s,%s%s" % (" " * 36, fmt(left), " " * 10, fmt(right)))
        lines.append("    ),")
    lines.append("};")
    return "\n".join(lines)


ARRAY_RE = re.compile(
    r"const\s+uint16_t\s+PROGMEM\s+keymaps\s*\[\s*\]\s*\[\s*MATRIX_ROWS\s*\]\s*\[\s*MATRIX_COLS\s*\]\s*=\s*\{.*?\};",
    re.DOTALL,
)


def splice_template(template_text, new_array_block):
    # Drop any previous generator comment so re-running stays idempotent.
    template_text = re.sub(r"^// Generated by vil2keymap\.py from .*$\n", "", template_text, flags=re.M)
    m = ARRAY_RE.search(template_text)
    if not m:
        raise SystemExit("error: could not find the keymaps array in the template keymap.c")
    return template_text[: m.start()] + new_array_block + template_text[m.end() :]


STANDALONE_TEMPLATE = """\
#include QMK_KEYBOARD_H

{array}
"""


# ---------------------------------------------------------------------------
# CLI.
# ---------------------------------------------------------------------------

def main(argv=None):
    ap = argparse.ArgumentParser(
        description="Convert a Vial .vil layout export into a QMK keymap.c.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    ap.add_argument("vil", help="Vial layout export (.vil, JSON)")
    ap.add_argument(
        "--keymap-c",
        metavar="FILE",
        help="template keymap.c whose keymaps array is replaced (default: auto-detect under firmware/keymaps)",
    )
    ap.add_argument("-o", "--output", metavar="FILE", help="output file (default: the template keymap.c)")
    ap.add_argument(
        "--keyboard-json",
        metavar="FILE",
        default="firmware/keyboard.json",
        help="keyboard.json defining the LAYOUT macro",
    )
    ap.add_argument(
        "--rows",
        metavar="LIST",
        default="12,12,12,12,6",
        help="LAYOUT row sizes; silakka54 is 4x12 keys + a 6-key thumb row",
    )
    args = ap.parse_args(argv)

    vil_path = Path(args.vil)
    try:
        vil = json.loads(vil_path.read_text())
    except (OSError, ValueError) as e:
        raise SystemExit("error: cannot read %s: %s" % (vil_path, e))
    if "layout" not in vil:
        raise SystemExit("error: %s has no 'layout' field; not a Vial layout export?" % vil_path)

    kb_path = Path(args.keyboard_json)
    try:
        kb = json.loads(kb_path.read_text())
    except (OSError, ValueError) as e:
        raise SystemExit("error: cannot read %s: %s" % (kb_path, e))
    try:
        layout_def = kb["layouts"]["LAYOUT"]["layout"]
    except KeyError:
        raise SystemExit("error: %s has no layouts.LAYOUT definition" % kb_path)

    rows = [int(x) for x in args.rows.split(",")]
    if sum(rows) != len(layout_def):
        raise SystemExit(
            "error: --rows sums to %d but LAYOUT has %d keys" % (sum(rows), len(layout_def))
        )

    template_path = None
    if args.keymap_c:
        template_path = Path(args.keymap_c)
    else:
        keymaps_dir = Path("firmware/keymaps")
        cands = sorted(keymaps_dir.glob("*/keymap.c")) if keymaps_dir.exists() else []
        if len(cands) == 1:
            template_path = cands[0]
        elif len(cands) > 1:
            # Prefer the keymap whose VIAL_KEYBOARD_UID matches the .vil's uid.
            uid = vil.get("uid")
            uid_matches = []
            for cand in cands:
                cfg = cand.with_name("config.h")
                if uid is not None and cfg.exists():
                    m = re.search(r"VIAL_KEYBOARD_UID\s*\{([^}]+)\}", cfg.read_text())
                    if m:
                        try:
                            # .vil stores the 8 UID bytes little-endian as one integer.
                            cfg_bytes = [int(b.strip().replace("0x", ""), 16) for b in m.group(1).split(",")]
                            cfg_uid = sum(v << (8 * i) for i, v in enumerate(cfg_bytes))
                        except ValueError:
                            cfg_uid = None
                        if cfg_uid == uid:
                            uid_matches.append(cand)
            if len(uid_matches) == 1:
                template_path = uid_matches[0]
            else:
                raise SystemExit(
                    "error: multiple keymaps found, use --keymap-c: " + ", ".join(str(c) for c in cands)
                )

    template_text = None
    if template_path is not None:
        if not template_path.exists():
            raise SystemExit("error: template keymap.c not found: %s" % template_path)
        template_text = template_path.read_text()

    layer_names = parse_layer_names(template_text) if template_text is not None else None
    if layer_names is not None and len(layer_names) != len(vil["layout"]):
        print(
            "note: enum layers has %d entries but the .vil has %d layers; using numeric designators"
            % (len(layer_names), len(vil["layout"])),
            file=sys.stderr,
        )
        layer_names = None

    try:
        out_layers = convert_layout(vil, layout_def, layer_names)
    except ValueError as e:
        raise SystemExit("error: %s" % e)

    block = format_keymaps(out_layers, layer_names, rows, vil_path.name)

    if template_text is not None:
        result = splice_template(template_text, block)
    else:
        result = STANDALONE_TEMPLATE.format(array=block)

    if args.output:
        out_path = Path(args.output)
    elif template_path is not None:
        out_path = template_path
    else:
        raise SystemExit("error: no template keymap.c found and no -o given")

    out_path.write_text(result)
    print(
        "wrote %s (%d layers x %d keys, template: %s)"
        % (out_path, len(out_layers), len(out_layers[0]), template_path if template_path else "none")
    )


if __name__ == "__main__":
    main()
