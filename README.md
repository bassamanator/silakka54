
# Silakka54

Silakka54 is a RP2040 Zero based 54-key column staggered split keyboard. PCB uses hotswap sockets. Design is inspired from REVIUNG41 and Corne keyboards.

PCB is designed for MX style key switches. Current top plate only supports MX style switches. 5-pin switches are supported. I recommend using Vial firmware.

**For more information visit https://github.com/Squalius-cephalus/silakka54/wiki**

![](https://raw.githubusercontent.com/Squalius-cephalus/silakka54/main/silakka54.png)

PCB design uses footprints from [ScottoKeebs](https://github.com/joe-scotto/scottokeebs/tree/main/Extras/ScottoKicad "ScottoKeebs") and [kbd library.](https://github.com/foostan/kbd "kbd library.")

## Keymap tooling

`vil2keymap.py` converts a Vial layout export (`.vil` file) into the `keymaps`
array of a QMK `keymap.c`, e.g. after editing layers in the Vial GUI:

```
python3 vil2keymap.py 26-aug.vil --keymap-c firmware/keymaps/vial_enthium_led/keymap.c
```

It maps the `.vil` matrix onto the `LAYOUT` macro using `firmware/keyboard.json`,
normalizes the keycodes (layer-taps, mod shorthands, aliases, shifted symbols)
and only replaces the `keymaps` array, preserving the rest of the file (RGB
code, callbacks, etc.).  Tap dances, combos and macros stay in EEPROM and are
handled by Vial itself, so load the `.vil` in Vial once after flashing.
