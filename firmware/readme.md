# Silakka54

![Silakka54](https://i.imgur.com/JrsS0kY.png)

Silakka54 is a RP2040 Zero based 54-key column staggered split keyboard. PCB uses hotswap sockets. Design is inspired from REVIUNG41 and Corne keyboards.

* Keyboard Maintainer: [Squalius-cephalus](https://github.com/Squalius-cephalus)
* Hardware Supported: Silakka54 PCB
* Hardware Availability: https://github.com/Squalius-cephalus/silakka54

## QMK

Make example for this keyboard (after setting up your QMK build environment):

    make silakka54:default

Flashing example for this keyboard:

    make silakka54:default:flash

## Vial

Make example for this keyboard (after setting up your Vial build environment):

    make silakka54:vial

Flashing example for this keyboard:

    make silakka54:vial:flash

## Firmware Compilation For Both Sides

1. Add `#define MASTER_RIGHT` to the `firmware/config.h`.
1. Compile the firmware; this will be the `.uf2` for the `right` side.
1. Comment the line from `Step 1`.
1. Compile the firmware; this will be the `.uf2` for the `left` side.

## Bootloader

Enter the bootloader in 2 ways:

* **Physical boot button**: Hold BOOT button down and connect MCU to the PC
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
