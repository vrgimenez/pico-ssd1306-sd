# Rpi Pico + SSD1306 + SD

Example using SSD1306 Display Module and a SD with FAT File System on a Raspberry Pi Pico.

## Introduction

The goal is to be able to import images and fonts from the SD card without having to embed them in the code.\
Using:
* [Simple SSD1306 Diplay Library](https://github.com/daschr/pico-ssd1306) written by [David Schramm](https://github.com/daschr).
* [C/C++ Library for SD Cards on the Pico](https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/) written by [Carl J Kugler III](https://github.com/carlk3).

## External Component Licenses

This project incorporates material from the following open-source projects, each subject to their respective licenses:

* **Simple SSD1306 Diplay Library**: Licensed under the [MIT License](https://opensource.org/licenses/MIT).
* **C/C++ Library for SD Cards on the Pico**: Licensed under the [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0).

For complete details on the licenses and attributions, please refer to the [`NOTICE`](./NOTICE.md) file at the root of this repository.

## Setup 

Checkout repo and do on submodules
```
git submodule update --init
```

## Building

```sh
mkdir build && cd build/
cmake ..
make
```

## Contributing
Share and contribute with Pull requests

## License

This project itself is licensed under the [MIT License](https://opensource.org/licenses/MIT).