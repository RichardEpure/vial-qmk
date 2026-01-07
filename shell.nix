{ pkgs ? import <nixpkgs> {}
, avr ? true
, arm ? true
, teensy ? true
}:

with pkgs;
let
  pythonEnv = python3.withPackages (ps: with ps; [
    # QMK requirements
    argcomplete
    colorama
    dotty-dict
    hid
    hjson
    jsonschema
    milc
    pygments
    pyserial
    pyusb
    pillow
  ]);
in
mkShell {
  name = "qmk-firmware";

  buildInputs = [
    clang-tools
    dfu-programmer
    dfu-util
    diffutils
    git
    gnumake
    pythonEnv
    qmk  # QMK CLI tool
  ]
    ++ lib.optionals avr [
      pkgsCross.avr.buildPackages.binutils
      pkgsCross.avr.buildPackages.gcc
      avrdude
    ]
    ++ lib.optionals arm [ gcc-arm-embedded ]
    ++ lib.optionals teensy [ teensy-loader-cli ];

  shellHook = ''
    # Prevent the avr-gcc wrapper from picking up host GCC flags
    # like -iframework, which is problematic on Darwin
    unset NIX_CFLAGS_COMPILE_FOR_TARGET
    echo "Vial-QMK development environment loaded"
  '';
}
