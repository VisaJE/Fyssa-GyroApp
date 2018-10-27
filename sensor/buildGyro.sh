#!/bin/sh
mkdir buildfolderGyro
cd buildfolderGyro
cmake -G Ninja -DMOVESENSE_CORE_LIBRARY=../../../movesense-device-lib/MovesenseCoreLib/ -DCMAKE_TOOLCHAIN_FILE=../../../movesense-device-lib/MovesenseCoreLib/toolchain/gcc-nrf52.cmake ../gyro_app

ninja dfupkg
mv Movesense_dfu.zip ../movesense_dfu.zip
cd ..
rm -r buildfolderGyro
cp movesense_dfu.zip ../src/main/res/raw/

