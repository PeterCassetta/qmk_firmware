LFK87
===

The original creator is now defunct. Here, I (Peter) attempt to document setup steps to modify my LFK87 revision D in the future.

1. Run make command from QMK MSYS terminal.
2. Put keyboard into bootloader mode. (Fn + Shift to enter settings mode, then Enter to enter bootloader mode.)
3. Flash firmware using QMK Toolbox. (Select the .hex file and set the MCU to AT90USB646.)
4. Upon successful flash, keyboard will reboot with new firmware.

---

A standard TKL with RGB underglow, in switch backlighting and audio support.

Keyboard Maintainer: [LFKeyboards](https://github.com/lfkeyboards)  
Hardware Supported: LFK87, SMK87  
Hardware Availability: [LFKeyboards.com](https://www.lfkeyboards.com/)

Make command for this keyboard (after setting up your build environment):

    make lfkeyboards/lfk87:custom

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.