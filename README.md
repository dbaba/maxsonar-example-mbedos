MaxSonar Sensor Example for Mbed OS
===

[![GitHub release](https://img.shields.io/github/release/dbaba/maxsonar-example-mbedos.svg)](https://github.com/dbaba/maxsonar-example-mbedos/releases/latest)
[![License MIT](https://img.shields.io/github/license/dbaba/maxsonar-example-mbedos.svg)](http://opensource.org/licenses/MIT)

Sample code for retrieving the range data in cm via I2C.

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

# Revision History
* 1.0.0
  - Initial Release
