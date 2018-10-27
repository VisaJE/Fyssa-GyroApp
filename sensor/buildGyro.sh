#!/bin/sh
mkdir buildfolderGyro
cd buildfolderGyro
cmake -G Ninja -DMOVESENSE_CORE_LIBRARY=../MovesenseCoreLib/ -DCMAKE_TOOLCHAIN_FILE=../MovesenseCoreLib/toolchain/gcc-nrf52.cmake ../gyro_app

ninja dfupkg
mv Movesense_dfu.zip ../Movesense_dfu.zip
cd ..
rm -r buildfolderGyro

