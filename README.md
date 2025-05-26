# Introduction

Example using SSD1306 Display Module and a SD with FAT File System on a Raspberry Pi Pico.\
The goal is to be able to import images and fonts from the SD card without having to embed them in the code.\
Using:
* [Simple SSD1306 Diplay Library](https://github.com/daschr/pico-ssd1306) written by [David Schramm](https://github.com/daschr).
* [C/C++ Library for SD Cards on the Pico](https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/) written by [Carl J Kugler III](https://github.com/carlk3).

# Setup 

Checkout repo and do on submodules
```
git submodule update --init
```

# Building

```sh
mkdir build && cd build/
cmake ..
make
```

# Contribute
Share and contribute with Pull requests
