# Pioneer — ARK Avionics Firmware

<div align="center" style="padding: 18px 0 22px 0;">
  <p><strong>ARK — Designed for the edge of space, built for total reliability.</strong></p>
  <img src="https://camo.githubusercontent.com/fbe262a7085aeff41e78915220b88792c6cd26c1964e2c4b91e312e948f2d7e8/68747470733a2f2f7465616d69676e6974696f6e2e73706163652f6c6f676f2f686561642d6c6f676f2e706e67" alt="Team Ignition" width="120"/>
</div>

Maintainer: Avionics-Software Department.

--------------------------------------------------------------------------------
## Overview

This repository contains the ARK avionics framework and firmware for the Pioneer
project, written for the Raspberry Pi Pico (RP2040). The code aggregates multiple
device drivers (BMP, MAG, MPU, GNSS, NRF, SD, buzzer), a small flight-state
manager and loop runner. Files under `ARK/` implement the platform logic and
drivers; `user/main.cpp` provides the entry point.

Key behavior:
- Power-on Self-Test (POST) and LED/buzzer feedback in the `SensorManager`.
- CSV logging to SD card and telemetry packet transmission via NRF.
- Lightweight state manager for flight phases.

--------------------------------------------------------------------------------
## Prerequisites

- Host: Linux (instructions below assume a POSIX shell).
- CMake >= 3.13
- GNU Make
- Raspberry Pi Pico SDK available to CMake via `pico_sdk_import.cmake` (project
  already includes `pico_sdk_import.cmake` usage).
- Optional: `picotool` or `pico_flash` for flashing the device.

If you need to install the Pico SDK, follow the official Raspberry Pi Pico
documentation and set `PICO_SDK_PATH` or use the provided `pico_sdk_import.cmake`.

--------------------------------------------------------------------------------
## Building

1. Create a build directory and run CMake:

```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

2. After a successful build, the UF2 / ELF will be generated (see
   `pico_add_extra_outputs` in [CMakeLists.txt](CMakeLists.txt)).

3. Flash to a Pico board using your preferred tool (drag-and-drop UF2 or use
   `picotool`/`openocd` as available):

```bash
# Example using picotool (if available)
picotool load pioneer.uf2 --target
```

--------------------------------------------------------------------------------
## Run (on device)

After flashing, plug the Pico in. The firmware initializes peripherals and
enters the main loop (`Ark::Start()`), which runs `Loops::Run()` to update
sensors, stream telemetry and manage flight state.

Serial/USB output is enabled via `pico_enable_stdio_usb` and `pico_enable_stdio_uart`.
Use `screen`, `minicom` or the serial monitor in your editor to view logs.

--------------------------------------------------------------------------------
## Project Structure (high level)

- [CMakeLists.txt](CMakeLists.txt) — top-level CMake build configuration.
- [user/main.cpp](user/main.cpp) — program entry point, constructs `Ark`.
- [ARK/ark.h](ARK/ark.h), [ARK/ark.cpp](ARK/ark.cpp) — top-level app container.
- [ARK/kernel/] — loop runner and state manager (`loops.*`, `statesmanager.*`).
- [ARK/system/] — system helpers (`sensors.*`, `watchdogs.*`, `timer.hpp`).
- [ARK/modules/] — hardware drivers (subfolders: `bmp`, `mpu`, `mag`, `sdcard`,
  `nrf`, `gnss`, `buzzer`, `ignitor` placeholder).
- [tests/] — test helpers (used by some modules).

Browse these files for implementation details and Doxygen comments recently
added to conform to Team Ignition coding standards.

--------------------------------------------------------------------------------
## Coding Standards (summary)

This project follows Team Ignition standards:

- ASCII header and HISTORY block at the top of each source/header file.
- Doxygen-style comments for all global and static functions.
- PascalCase for types / classes, camelCase for private members.
- UPPER_SNAKE_CASE for macros/constants.
- All error-prone functions should return a `ResultCode`-like enum and must
  validate inputs early (no silent failures).

See the `Template_module` example in the project guide for full templates.

--------------------------------------------------------------------------------
## What I changed (notes)

- Added ASCII headers, HISTORY block (with name `User`) and Doxygen
  comments to the majority of ARK source and header files. No runtime logic
  was changed — only documentation and headers were added.
- Updated `CMakeLists.txt` with one-line comments describing each section.

--------------------------------------------------------------------------------
## Contributing

🤝 Contributing to Team Ignition

Create a feature branch from `workingiteration{No}`:

```bash
git checkout -b feature/your-feature-name
```

Follow the Style:

- Use _camelCase_ for private members.
- Use PascalCase for Classes and types.

Test:

- Use the `tests/` directory to write unit tests before pushing to `workingiteration1`.
- Add unit tests for any significant logic change; prefer host-side, hardware-mocked tests.

Checklist before opening a PR:

- [ ] Branch created from `workingiteration1`.
- [ ] Doxygen comments and HISTORY entries updated for touched files.
- [ ] Unit tests added/updated under `tests/` and pass locally where possible.
- [ ] PR description includes a short changelog and testing notes.

--------------------------------------------------------------------------------
## Tests

Use the `tests/` directory for unit tests. Add new tests before large
refactors. The repository contains a `tests/test.hpp` helper used by some
modules.

--------------------------------------------------------------------------------
## Troubleshooting & Tips

- If CMake cannot find the Pico SDK: ensure `pico_sdk_import.cmake` is present
  and that your environment has Internet access (it can fetch the SDK) or set
  `PICO_SDK_PATH`.
- Logging: USB and UART stdio are enabled. If you do not see logs, verify
  `pico_enable_stdio_usb` and `pico_enable_stdio_uart` settings in
  [CMakeLists.txt](CMakeLists.txt).

--------------------------------------------------------------------------------
## Contact / Authors

Maintainer: Kunsh

--------------------------------------------------------------------------------
Thank you for contributing to Team Ignition Pioneer-Codes.
