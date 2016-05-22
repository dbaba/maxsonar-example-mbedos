MaxSonar MB1242 Example for mbed OS
===

[![GitHub release](https://img.shields.io/github/release/dbaba/maxsonar-example-mbedos.svg)](https://github.com/dbaba/maxsonar-example-mbedos/releases/latest)
[![License MIT](https://img.shields.io/github/license/dbaba/maxsonar-example-mbedos.svg)](http://opensource.org/licenses/MIT)

MaxSonar Ultrasonic Distance Sensor MB1242 Example on mbed OS with Sync and Async I2C API

# How to migrate from v1.0.0

    git pull
    yt update
    yt clean


# How to setup (w/ ST Nucleo F401RE)

    yt target st-nucleo-f401re-gcc
    yt install

# How to build

    yt build

# How to flash

Copy `build/st-nucleo-f401re-gcc/source/maxsonar-example.bin` to the mbed folder or use st-flash as shown below.

    st-flash write build/st-nucleo-f401re-gcc/source/maxsonar-example.bin 0x8000000

# Choose I2C Async API or I2C Sync API

Edit `ASYNC` definition in app.cpp.

    #define ASYNC 1

The value `1` for enabling asynchronous API and `0` for enabling synchronous API.

`ASYNC` is `1` by default.

# USB Serial Baud rate

Set 115200 bps in order to connect to the USB serial port. The baud rate is set in config.json file.

# Revision History
* 1.1.0
    - [I2C Asynchronous API](https://docs.mbed.com/docs/getting-started-mbed-os/en/latest/Full_Guide/I2C/) support
    - NOTICE) The mbed OS I2C Asynchronous API is still unstable, the project MAY not work on mbed OS in the future

* 1.0.0
  - Initial Release
