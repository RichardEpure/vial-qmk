# RichardEpure Keymap

## Build In QMK MSYS

Open QMK MSYS, then go to this QMK/Vial repo:

```sh
cd "/e/Program Files (x86)/repos/vial-qmk"
```

Build this custom keymap with `qmk compile`:

```sh
qmk compile -kb cyboard/imprint/custom/richard_custom -km RichardEpure
```

Equivalent `make` command:

```sh
make cyboard/imprint/custom/richard_custom:RichardEpure
```

The compiled firmware is written to the repo root. For this RP2040 keyboard, the output should be a `.uf2` file.
