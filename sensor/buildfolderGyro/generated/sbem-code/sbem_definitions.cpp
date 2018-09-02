#include "whiteboard/Value.h"
#include "app-resources/resources.h"
#include "app_execution_contexts/resources.h"
#include "comm_ble/resources.h"
#include "comm_ble_gattsvc/resources.h"
#include "component_ds24l65/resources.h"
#include "component_eeprom/resources.h"
#include "component_led/resources.h"
#include "component_lsm6ds3/resources.h"
#include "component_max3000x/resources.h"
#include "component_nrf52/resources.h"
#include "device_systemevent/resources.h"
#include "device_system_debug/resources.h"
#include "device_system_shutdown/resources.h"
#include "dev_system/resources.h"
#include "meas_acc/resources.h"
#include "meas_ecg/resources.h"
#include "meas_gyro/resources.h"
#include "meas_hr/resources.h"
#include "meas_imu/resources.h"
#include "meas_magn/resources.h"
#include "meas_temp/resources.h"
#include "mem_datalogger/resources.h"
#include "mem_logbook/resources.h"
#include "misc_calibration/resources.h"
#include "misc_gear/resources.h"
#include "misc_manufacturing/resources.h"
#include "movesense_info/resources.h"
#include "movesense_time/resources.h"
#include "movesense_types/resources.h"
#include "system_debug/resources.h"
#include "system_energy/resources.h"
#include "system_memory/resources.h"
#include "system_mode/resources.h"
#include "system_settings/resources.h"
#include "system_states/resources.h"
#include "ui_ind/resources.h"
#include "wb-resources/resources.h"
#include "sbem_definitions.h"

CREATE_GROUP(FYSSA_GYRO_,
    static_cast<uint16_t>(FYSSA_GYRO_FRONTX),
    static_cast<uint16_t>(FYSSA_GYRO_FRONTY),
    static_cast<uint16_t>(FYSSA_GYRO_FRONTZ),
    static_cast<uint16_t>(FYSSA_GYRO_TOPX),
    static_cast<uint16_t>(FYSSA_GYRO_TOPY),
    static_cast<uint16_t>(FYSSA_GYRO_TOPZ));

CREATE_GROUP(MEAS_ACC_SAMPLERATE_ARRAYACC_,
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_X),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_Y),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_Z));

CREATE_GROUP(MEAS_ACC_SAMPLERATE_1,
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_ACC_SAMPLERATE_2,
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_ACC_SAMPLERATE_3,
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_ACC_SAMPLERATE_4,
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_ACC_SAMPLERATE_5,
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_ACC_SAMPLERATE_6,
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_ACC_SAMPLERATE_7,
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_ACC_SAMPLERATE_8,
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_ACC_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_ECG_REQUIREDSAMPLERATE_1,
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_TIMESTAMP));

CREATE_GROUP(MEAS_ECG_REQUIREDSAMPLERATE_2,
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_TIMESTAMP));

CREATE_GROUP(MEAS_ECG_REQUIREDSAMPLERATE_3,
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_TIMESTAMP));

CREATE_GROUP(MEAS_ECG_REQUIREDSAMPLERATE_4,
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_TIMESTAMP));

CREATE_GROUP(MEAS_ECG_REQUIREDSAMPLERATE_5,
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_TIMESTAMP));

CREATE_GROUP(MEAS_ECG_REQUIREDSAMPLERATE_6,
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_TIMESTAMP));

CREATE_GROUP(MEAS_ECG_REQUIREDSAMPLERATE_7,
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_TIMESTAMP));

CREATE_GROUP(MEAS_ECG_REQUIREDSAMPLERATE_8,
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(MEAS_ECG_REQUIREDSAMPLERATE_TIMESTAMP));

CREATE_GROUP(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_,
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_X),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_Y),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_Z));

CREATE_GROUP(MEAS_GYRO_SAMPLERATE_1,
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_GYRO_SAMPLERATE_2,
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_GYRO_SAMPLERATE_3,
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_GYRO_SAMPLERATE_4,
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_GYRO_SAMPLERATE_5,
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_GYRO_SAMPLERATE_6,
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_GYRO_SAMPLERATE_7,
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_GYRO_SAMPLERATE_8,
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_GYRO_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_HR_1,
    static_cast<uint16_t>(MEAS_HR_AVERAGE),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_HR_2,
    static_cast<uint16_t>(MEAS_HR_AVERAGE),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_HR_3,
    static_cast<uint16_t>(MEAS_HR_AVERAGE),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_HR_4,
    static_cast<uint16_t>(MEAS_HR_AVERAGE),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_HR_5,
    static_cast<uint16_t>(MEAS_HR_AVERAGE),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_HR_6,
    static_cast<uint16_t>(MEAS_HR_AVERAGE),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_HR_7,
    static_cast<uint16_t>(MEAS_HR_AVERAGE),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_HR_8,
    static_cast<uint16_t>(MEAS_HR_AVERAGE),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(MEAS_HR_RRDATA),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_ARRAYACC_,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_X),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_Y),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_Z));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_X),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_Y),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_Z));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_1,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_2,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_3,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_4,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_5,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_6,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_7,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6_SAMPLERATE_8,
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU6_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_ARRAYACC_,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_X),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_Y),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_Z));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_X),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_Y),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_Z));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_1,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_2,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_3,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_4,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_5,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_6,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_7,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU6M_SAMPLERATE_8,
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_ARRAYACC_,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_X),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_Y),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_Z));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_X),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_Y),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_Z));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_X),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_Y),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_Z));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_1,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_2,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_3,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_4,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_5,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_6,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_7,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_IMU9_SAMPLERATE_8,
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYACC_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYGYRO_),
    static_cast<uint16_t>(ARRAY_END),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_IMU9_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_,
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_X),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_Y),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_Z));

CREATE_GROUP(MEAS_MAGN_SAMPLERATE_1,
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_MAGN_SAMPLERATE_2,
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_MAGN_SAMPLERATE_3,
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_MAGN_SAMPLERATE_4,
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_MAGN_SAMPLERATE_5,
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_MAGN_SAMPLERATE_6,
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_MAGN_SAMPLERATE_7,
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_MAGN_SAMPLERATE_8,
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_TIMESTAMP),
    static_cast<uint16_t>(ARRAY_BEGIN),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(MEAS_MAGN_SAMPLERATE_ARRAYMAGN_),
    static_cast<uint16_t>(ARRAY_END));

CREATE_GROUP(MEAS_TEMP_,
    static_cast<uint16_t>(MEAS_TEMP_MEASUREMENT),
    static_cast<uint16_t>(MEAS_TEMP_TIMESTAMP));

CREATE_GROUP(WHITEBOARD_METRICS_COMM_,
    static_cast<uint16_t>(WHITEBOARD_METRICS_COMM_RECEIVEDBYTES),
    static_cast<uint16_t>(WHITEBOARD_METRICS_COMM_SENTBYTES));

const DescriptorItem_t s_possibleSbemItems[] = {
    {NET, "<PTH>Net\n<FRM>utf8"},
    {TIME, "<PTH>Time\n<FRM>int64,nillable=4294967295"},
    {FYSSA_GYRO_FRONTX, "<PTH>Fyssa+Gyro.Frontx\n<FRM>float32"},
    {FYSSA_GYRO_FRONTY, "<PTH>Fyssa.Gyro.Fronty\n<FRM>float32"},
    {FYSSA_GYRO_FRONTZ, "<PTH>Fyssa.Gyro.Frontz\n<FRM>float32"},
    {FYSSA_GYRO_TOPX, "<PTH>Fyssa.Gyro.Topx\n<FRM>float32"},
    {FYSSA_GYRO_TOPY, "<PTH>Fyssa.Gyro.Topy\n<FRM>float32"},
    {FYSSA_GYRO_TOPZ, "<PTH>Fyssa.Gyro.Topz\n<FRM>float32"},
    {MEAS_ACC_SAMPLERATE_ARRAYACC_X, "<PTH>Meas.Acc.SampleRate.ArrayAcc+x\n<FRM>float32"},
    {MEAS_ACC_SAMPLERATE_ARRAYACC_Y, "<PTH>Meas.Acc.SampleRate.ArrayAcc.y\n<FRM>float32"},
    {MEAS_ACC_SAMPLERATE_ARRAYACC_Z, "<PTH>Meas.Acc.SampleRate.ArrayAcc.z\n<FRM>float32"},
    {MEAS_ACC_SAMPLERATE_TIMESTAMP, "<PTH>Meas.Acc+SampleRate.Timestamp\n<FRM>uint32"},
    {MEAS_ECG_REQUIREDSAMPLERATE_SAMPLES, "<PTH>Meas.ECG+RequiredSampleRate.Samples\n<FRM>int32"},
    {MEAS_ECG_REQUIREDSAMPLERATE_TIMESTAMP, "<PTH>Meas.ECG.RequiredSampleRate.Timestamp\n<FRM>uint32"},
    {MEAS_GYRO_SAMPLERATE_ARRAYGYRO_X, "<PTH>Meas.Gyro.SampleRate.ArrayGyro+x\n<FRM>float32"},
    {MEAS_GYRO_SAMPLERATE_ARRAYGYRO_Y, "<PTH>Meas.Gyro.SampleRate.ArrayGyro.y\n<FRM>float32"},
    {MEAS_GYRO_SAMPLERATE_ARRAYGYRO_Z, "<PTH>Meas.Gyro.SampleRate.ArrayGyro.z\n<FRM>float32"},
    {MEAS_GYRO_SAMPLERATE_TIMESTAMP, "<PTH>Meas.Gyro+SampleRate.Timestamp\n<FRM>uint32"},
    {MEAS_HR_AVERAGE, "<PTH>Meas+HR.average\n<FRM>float32"},
    {MEAS_HR_RRDATA, "<PTH>Meas.HR.rrData\n<FRM>uint16"},
    {MEAS_IMU6_SAMPLERATE_ARRAYACC_X, "<PTH>Meas.IMU6.SampleRate.ArrayAcc+x\n<FRM>float32"},
    {MEAS_IMU6_SAMPLERATE_ARRAYACC_Y, "<PTH>Meas.IMU6.SampleRate.ArrayAcc.y\n<FRM>float32"},
    {MEAS_IMU6_SAMPLERATE_ARRAYACC_Z, "<PTH>Meas.IMU6.SampleRate.ArrayAcc.z\n<FRM>float32"},
    {MEAS_IMU6_SAMPLERATE_ARRAYGYRO_X, "<PTH>Meas.IMU6.SampleRate.ArrayGyro+x\n<FRM>float32"},
    {MEAS_IMU6_SAMPLERATE_ARRAYGYRO_Y, "<PTH>Meas.IMU6.SampleRate.ArrayGyro.y\n<FRM>float32"},
    {MEAS_IMU6_SAMPLERATE_ARRAYGYRO_Z, "<PTH>Meas.IMU6.SampleRate.ArrayGyro.z\n<FRM>float32"},
    {MEAS_IMU6_SAMPLERATE_TIMESTAMP, "<PTH>Meas.IMU6+SampleRate.Timestamp\n<FRM>uint32"},
    {MEAS_IMU6M_SAMPLERATE_ARRAYACC_X, "<PTH>Meas.IMU6m.SampleRate.ArrayAcc+x\n<FRM>float32"},
    {MEAS_IMU6M_SAMPLERATE_ARRAYACC_Y, "<PTH>Meas.IMU6m.SampleRate.ArrayAcc.y\n<FRM>float32"},
    {MEAS_IMU6M_SAMPLERATE_ARRAYACC_Z, "<PTH>Meas.IMU6m.SampleRate.ArrayAcc.z\n<FRM>float32"},
    {MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_X, "<PTH>Meas.IMU6m.SampleRate.ArrayMagn+x\n<FRM>float32"},
    {MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_Y, "<PTH>Meas.IMU6m.SampleRate.ArrayMagn.y\n<FRM>float32"},
    {MEAS_IMU6M_SAMPLERATE_ARRAYMAGN_Z, "<PTH>Meas.IMU6m.SampleRate.ArrayMagn.z\n<FRM>float32"},
    {MEAS_IMU6M_SAMPLERATE_TIMESTAMP, "<PTH>Meas.IMU6m+SampleRate.Timestamp\n<FRM>uint32"},
    {MEAS_IMU9_SAMPLERATE_ARRAYACC_X, "<PTH>Meas.IMU9.SampleRate.ArrayAcc+x\n<FRM>float32"},
    {MEAS_IMU9_SAMPLERATE_ARRAYACC_Y, "<PTH>Meas.IMU9.SampleRate.ArrayAcc.y\n<FRM>float32"},
    {MEAS_IMU9_SAMPLERATE_ARRAYACC_Z, "<PTH>Meas.IMU9.SampleRate.ArrayAcc.z\n<FRM>float32"},
    {MEAS_IMU9_SAMPLERATE_ARRAYGYRO_X, "<PTH>Meas.IMU9.SampleRate.ArrayGyro+x\n<FRM>float32"},
    {MEAS_IMU9_SAMPLERATE_ARRAYGYRO_Y, "<PTH>Meas.IMU9.SampleRate.ArrayGyro.y\n<FRM>float32"},
    {MEAS_IMU9_SAMPLERATE_ARRAYGYRO_Z, "<PTH>Meas.IMU9.SampleRate.ArrayGyro.z\n<FRM>float32"},
    {MEAS_IMU9_SAMPLERATE_ARRAYMAGN_X, "<PTH>Meas.IMU9.SampleRate.ArrayMagn+x\n<FRM>float32"},
    {MEAS_IMU9_SAMPLERATE_ARRAYMAGN_Y, "<PTH>Meas.IMU9.SampleRate.ArrayMagn.y\n<FRM>float32"},
    {MEAS_IMU9_SAMPLERATE_ARRAYMAGN_Z, "<PTH>Meas.IMU9.SampleRate.ArrayMagn.z\n<FRM>float32"},
    {MEAS_IMU9_SAMPLERATE_TIMESTAMP, "<PTH>Meas.IMU9+SampleRate.Timestamp\n<FRM>uint32"},
    {MEAS_MAGN_SAMPLERATE_ARRAYMAGN_X, "<PTH>Meas.Magn.SampleRate.ArrayMagn+x\n<FRM>float32"},
    {MEAS_MAGN_SAMPLERATE_ARRAYMAGN_Y, "<PTH>Meas.Magn.SampleRate.ArrayMagn.y\n<FRM>float32"},
    {MEAS_MAGN_SAMPLERATE_ARRAYMAGN_Z, "<PTH>Meas.Magn.SampleRate.ArrayMagn.z\n<FRM>float32"},
    {MEAS_MAGN_SAMPLERATE_TIMESTAMP, "<PTH>Meas.Magn+SampleRate.Timestamp\n<FRM>uint32"},
    {MEAS_TEMP_MEASUREMENT, "<PTH>Meas+Temp.Measurement\n<FRM>float32"},
    {MEAS_TEMP_TIMESTAMP, "<PTH>Meas.Temp.Timestamp\n<FRM>uint32"},
    {WHITEBOARD_METRICS_COMM_RECEIVEDBYTES, "<PTH>Whiteboard.Metrics+Comm.receivedBytes\n<FRM>uint32"},
    {WHITEBOARD_METRICS_COMM_SENTBYTES, "<PTH>Whiteboard.Metrics.Comm.sentBytes\n<FRM>uint32"},
    {ARRAY_BEGIN, "<PTH>["},
    {ARRAY_END, "<PTH>]"},
};

const DescriptorGroup_t s_possibleSbemGroups[] = {
    FYSSA_GYRO__Group,
    MEAS_ACC_SAMPLERATE_ARRAYACC__Group,
    MEAS_ACC_SAMPLERATE_1_Group,
    MEAS_ACC_SAMPLERATE_2_Group,
    MEAS_ACC_SAMPLERATE_3_Group,
    MEAS_ACC_SAMPLERATE_4_Group,
    MEAS_ACC_SAMPLERATE_5_Group,
    MEAS_ACC_SAMPLERATE_6_Group,
    MEAS_ACC_SAMPLERATE_7_Group,
    MEAS_ACC_SAMPLERATE_8_Group,
    MEAS_ECG_REQUIREDSAMPLERATE_1_Group,
    MEAS_ECG_REQUIREDSAMPLERATE_2_Group,
    MEAS_ECG_REQUIREDSAMPLERATE_3_Group,
    MEAS_ECG_REQUIREDSAMPLERATE_4_Group,
    MEAS_ECG_REQUIREDSAMPLERATE_5_Group,
    MEAS_ECG_REQUIREDSAMPLERATE_6_Group,
    MEAS_ECG_REQUIREDSAMPLERATE_7_Group,
    MEAS_ECG_REQUIREDSAMPLERATE_8_Group,
    MEAS_GYRO_SAMPLERATE_ARRAYGYRO__Group,
    MEAS_GYRO_SAMPLERATE_1_Group,
    MEAS_GYRO_SAMPLERATE_2_Group,
    MEAS_GYRO_SAMPLERATE_3_Group,
    MEAS_GYRO_SAMPLERATE_4_Group,
    MEAS_GYRO_SAMPLERATE_5_Group,
    MEAS_GYRO_SAMPLERATE_6_Group,
    MEAS_GYRO_SAMPLERATE_7_Group,
    MEAS_GYRO_SAMPLERATE_8_Group,
    MEAS_HR_1_Group,
    MEAS_HR_2_Group,
    MEAS_HR_3_Group,
    MEAS_HR_4_Group,
    MEAS_HR_5_Group,
    MEAS_HR_6_Group,
    MEAS_HR_7_Group,
    MEAS_HR_8_Group,
    MEAS_IMU6_SAMPLERATE_ARRAYACC__Group,
    MEAS_IMU6_SAMPLERATE_ARRAYGYRO__Group,
    MEAS_IMU6_SAMPLERATE_1_Group,
    MEAS_IMU6_SAMPLERATE_2_Group,
    MEAS_IMU6_SAMPLERATE_3_Group,
    MEAS_IMU6_SAMPLERATE_4_Group,
    MEAS_IMU6_SAMPLERATE_5_Group,
    MEAS_IMU6_SAMPLERATE_6_Group,
    MEAS_IMU6_SAMPLERATE_7_Group,
    MEAS_IMU6_SAMPLERATE_8_Group,
    MEAS_IMU6M_SAMPLERATE_ARRAYACC__Group,
    MEAS_IMU6M_SAMPLERATE_ARRAYMAGN__Group,
    MEAS_IMU6M_SAMPLERATE_1_Group,
    MEAS_IMU6M_SAMPLERATE_2_Group,
    MEAS_IMU6M_SAMPLERATE_3_Group,
    MEAS_IMU6M_SAMPLERATE_4_Group,
    MEAS_IMU6M_SAMPLERATE_5_Group,
    MEAS_IMU6M_SAMPLERATE_6_Group,
    MEAS_IMU6M_SAMPLERATE_7_Group,
    MEAS_IMU6M_SAMPLERATE_8_Group,
    MEAS_IMU9_SAMPLERATE_ARRAYACC__Group,
    MEAS_IMU9_SAMPLERATE_ARRAYGYRO__Group,
    MEAS_IMU9_SAMPLERATE_ARRAYMAGN__Group,
    MEAS_IMU9_SAMPLERATE_1_Group,
    MEAS_IMU9_SAMPLERATE_2_Group,
    MEAS_IMU9_SAMPLERATE_3_Group,
    MEAS_IMU9_SAMPLERATE_4_Group,
    MEAS_IMU9_SAMPLERATE_5_Group,
    MEAS_IMU9_SAMPLERATE_6_Group,
    MEAS_IMU9_SAMPLERATE_7_Group,
    MEAS_IMU9_SAMPLERATE_8_Group,
    MEAS_MAGN_SAMPLERATE_ARRAYMAGN__Group,
    MEAS_MAGN_SAMPLERATE_1_Group,
    MEAS_MAGN_SAMPLERATE_2_Group,
    MEAS_MAGN_SAMPLERATE_3_Group,
    MEAS_MAGN_SAMPLERATE_4_Group,
    MEAS_MAGN_SAMPLERATE_5_Group,
    MEAS_MAGN_SAMPLERATE_6_Group,
    MEAS_MAGN_SAMPLERATE_7_Group,
    MEAS_MAGN_SAMPLERATE_8_Group,
    MEAS_TEMP__Group,
    WHITEBOARD_METRICS_COMM__Group,
};

size_t writeToSbemBuffer_FYSSA_GYRO(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::FYSSA_GYRO::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.frontx;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    {
        auto value = data.fronty;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    {
        auto value = data.frontz;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    {
        auto value = data.topx;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    {
        auto value = data.topy;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    {
        auto value = data.topz;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    return bytesWritten;
}



size_t writeToSbemBuffer_MEAS_ACC_SAMPLERATE(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.timestamp;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    for(size_t loopidx_1=0; loopidx_1<data.arrayAcc.size(); loopidx_1++)
    {
        {
            auto value = data.arrayAcc[loopidx_1].x;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayAcc[loopidx_1].y;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayAcc[loopidx_1].z;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
    }
    return bytesWritten;
}



size_t writeToSbemBuffer_MEAS_ECG_REQUIREDSAMPLERATE(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    for(size_t loopidx_1=0; loopidx_1<data.samples.size(); loopidx_1++)
    {
    {
        auto value = data.samples[loopidx_1];
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    }
        {
            auto value = data.timestamp;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
    return bytesWritten;
}



size_t writeToSbemBuffer_MEAS_GYRO_SAMPLERATE(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.timestamp;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    for(size_t loopidx_1=0; loopidx_1<data.arrayGyro.size(); loopidx_1++)
    {
        {
            auto value = data.arrayGyro[loopidx_1].x;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayGyro[loopidx_1].y;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayGyro[loopidx_1].z;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
    }
    return bytesWritten;
}



size_t writeToSbemBuffer_MEAS_HR(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::MEAS_HR::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.average;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    for(size_t loopidx_1=0; loopidx_1<data.rrData.size(); loopidx_1++)
    {
    {
        auto value = data.rrData[loopidx_1];
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    }
    return bytesWritten;
}



size_t writeToSbemBuffer_MEAS_IMU6_SAMPLERATE(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.timestamp;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    for(size_t loopidx_1=0; loopidx_1<data.arrayAcc.size(); loopidx_1++)
    {
        {
            auto value = data.arrayAcc[loopidx_1].x;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayAcc[loopidx_1].y;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayAcc[loopidx_1].z;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
    }
        for(size_t loopidx_2=0; loopidx_2<data.arrayGyro.size(); loopidx_2++)
    {
            {
                auto value = data.arrayGyro[loopidx_2].x;
                const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                    if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
            }
            {
                auto value = data.arrayGyro[loopidx_2].y;
                const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                    if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
            }
            {
                auto value = data.arrayGyro[loopidx_2].z;
                const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                    if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
            }
        }
    return bytesWritten;
}



size_t writeToSbemBuffer_MEAS_IMU6M_SAMPLERATE(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.timestamp;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    for(size_t loopidx_1=0; loopidx_1<data.arrayAcc.size(); loopidx_1++)
    {
        {
            auto value = data.arrayAcc[loopidx_1].x;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayAcc[loopidx_1].y;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayAcc[loopidx_1].z;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
    }
        for(size_t loopidx_2=0; loopidx_2<data.arrayMagn.size(); loopidx_2++)
    {
            {
                auto value = data.arrayMagn[loopidx_2].x;
                const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                    if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
            }
            {
                auto value = data.arrayMagn[loopidx_2].y;
                const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                    if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
            }
            {
                auto value = data.arrayMagn[loopidx_2].z;
                const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                    if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
            }
        }
    return bytesWritten;
}



size_t writeToSbemBuffer_MEAS_IMU9_SAMPLERATE(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.timestamp;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    for(size_t loopidx_1=0; loopidx_1<data.arrayAcc.size(); loopidx_1++)
    {
        {
            auto value = data.arrayAcc[loopidx_1].x;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayAcc[loopidx_1].y;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayAcc[loopidx_1].z;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
    }
        for(size_t loopidx_2=0; loopidx_2<data.arrayGyro.size(); loopidx_2++)
    {
            {
                auto value = data.arrayGyro[loopidx_2].x;
                const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                    if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
            }
            {
                auto value = data.arrayGyro[loopidx_2].y;
                const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                    if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
            }
            {
                auto value = data.arrayGyro[loopidx_2].z;
                const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                    if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
            }
        }
            for(size_t loopidx_3=0; loopidx_3<data.arrayMagn.size(); loopidx_3++)
    {
                {
                    auto value = data.arrayMagn[loopidx_3].x;
                    const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                    for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                        if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
                }
                {
                    auto value = data.arrayMagn[loopidx_3].y;
                    const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                    for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                        if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
                }
                {
                    auto value = data.arrayMagn[loopidx_3].z;
                    const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
                    for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                        if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
                }
            }
    return bytesWritten;
}



size_t writeToSbemBuffer_MEAS_MAGN_SAMPLERATE(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.timestamp;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    for(size_t loopidx_1=0; loopidx_1<data.arrayMagn.size(); loopidx_1++)
    {
        {
            auto value = data.arrayMagn[loopidx_1].x;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayMagn[loopidx_1].y;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
        {
            auto value = data.arrayMagn[loopidx_1].z;
            const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
            for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
                if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
        }
    }
    return bytesWritten;
}



size_t writeToSbemBuffer_MEAS_TEMP(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::MEAS_TEMP::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.measurement;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    {
        auto value = data.timestamp;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    return bytesWritten;
}



size_t writeToSbemBuffer_TIME(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::TIME::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    return bytesWritten;
}



size_t writeToSbemBuffer_WHITEBOARD_METRICS_COMM(void *buffer, size_t bufferLen, size_t startOffset, const WB_RES::LOCAL::WHITEBOARD_METRICS_COMM::EVENT::NotificationType &data){
    size_t bytesRead = 0;
    size_t bytesWritten = 0;
    uint8_t *byteBuf = static_cast<uint8_t*>(buffer);
    {
        auto value = data.receivedBytes;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    {
        auto value = data.sentBytes;
        const uint8_t *src = reinterpret_cast<const uint8_t*>(&value);
        for(size_t i=0; i<sizeof(value); i++, src++, bytesRead++)
            if ((bytesRead >= startOffset) && (bytesWritten < bufferLen)) byteBuf[bytesWritten++] = *src;
    }
    return bytesWritten;
}



size_t getSbemLength_FYSSA_GYRO(const WB_RES::LOCAL::FYSSA_GYRO::EVENT::NotificationType &data)
{
    return (0 + 4 + 4 + 4 + 4 + 4 + 4);
}



size_t getSbemLength_MEAS_ACC_SAMPLERATE(const WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::EVENT::NotificationType &data)
{
    return (0 + 4 + data.arrayAcc.size() * (0  + 4 + 4 + 4 ) );
}



size_t getSbemLength_MEAS_ECG_REQUIREDSAMPLERATE(const WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::EVENT::NotificationType &data)
{
    return (0 + data.samples.size() * (0  + 4 )  + 4);
}



size_t getSbemLength_MEAS_GYRO_SAMPLERATE(const WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::EVENT::NotificationType &data)
{
    return (0 + 4 + data.arrayGyro.size() * (0  + 4 + 4 + 4 ) );
}



size_t getSbemLength_MEAS_HR(const WB_RES::LOCAL::MEAS_HR::EVENT::NotificationType &data)
{
    return (0 + 4 + data.rrData.size() * (0  + 2 ) );
}



size_t getSbemLength_MEAS_IMU6_SAMPLERATE(const WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::EVENT::NotificationType &data)
{
    return (0 + 4 + data.arrayAcc.size() * (0  + 4 + 4 + 4 )  + data.arrayGyro.size() * (0  + 4 + 4 + 4 ) );
}



size_t getSbemLength_MEAS_IMU6M_SAMPLERATE(const WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::EVENT::NotificationType &data)
{
    return (0 + 4 + data.arrayAcc.size() * (0  + 4 + 4 + 4 )  + data.arrayMagn.size() * (0  + 4 + 4 + 4 ) );
}



size_t getSbemLength_MEAS_IMU9_SAMPLERATE(const WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::EVENT::NotificationType &data)
{
    return (0 + 4 + data.arrayAcc.size() * (0  + 4 + 4 + 4 )  + data.arrayGyro.size() * (0  + 4 + 4 + 4 )  + data.arrayMagn.size() * (0  + 4 + 4 + 4 ) );
}



size_t getSbemLength_MEAS_MAGN_SAMPLERATE(const WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::EVENT::NotificationType &data)
{
    return (0 + 4 + data.arrayMagn.size() * (0  + 4 + 4 + 4 ) );
}



size_t getSbemLength_MEAS_TEMP(const WB_RES::LOCAL::MEAS_TEMP::EVENT::NotificationType &data)
{
    return (0 + 4 + 4);
}



size_t getSbemLength_TIME(const WB_RES::LOCAL::TIME::EVENT::NotificationType &data)
{
    return (0 + 8);
}



size_t getSbemLength_WHITEBOARD_METRICS_COMM(const WB_RES::LOCAL::WHITEBOARD_METRICS_COMM::EVENT::NotificationType &data)
{
    return (0 + 4 + 4);
}



int16_t getSbemLengthConst(whiteboard::LocalResourceId localResId)
{
    switch(localResId)
    {
    case WB_RES::LOCAL::FYSSA_GYRO::LID:
        return (24);
    case WB_RES::LOCAL::MEAS_TEMP::LID:
        return (8);
    case WB_RES::LOCAL::TIME::LID:
        return (8);
    case WB_RES::LOCAL::WHITEBOARD_METRICS_COMM::LID:
        return (8);
    }
    return -1;
}


size_t getSbemLength(whiteboard::LocalResourceId localResId, const whiteboard::Value &data)
{
    switch(localResId)
    {
    case WB_RES::LOCAL::FYSSA_GYRO::LID:
        return getSbemLength_FYSSA_GYRO(data.convertTo<WB_RES::LOCAL::FYSSA_GYRO::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID:
        return getSbemLength_MEAS_ACC_SAMPLERATE(data.convertTo<WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID:
        return getSbemLength_MEAS_ECG_REQUIREDSAMPLERATE(data.convertTo<WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID:
        return getSbemLength_MEAS_GYRO_SAMPLERATE(data.convertTo<WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_HR::LID:
        return getSbemLength_MEAS_HR(data.convertTo<WB_RES::LOCAL::MEAS_HR::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID:
        return getSbemLength_MEAS_IMU6_SAMPLERATE(data.convertTo<WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID:
        return getSbemLength_MEAS_IMU6M_SAMPLERATE(data.convertTo<WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID:
        return getSbemLength_MEAS_IMU9_SAMPLERATE(data.convertTo<WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID:
        return getSbemLength_MEAS_MAGN_SAMPLERATE(data.convertTo<WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_TEMP::LID:
        return getSbemLength_MEAS_TEMP(data.convertTo<WB_RES::LOCAL::MEAS_TEMP::EVENT::NotificationType>());
    case WB_RES::LOCAL::TIME::LID:
        return getSbemLength_TIME(data.convertTo<WB_RES::LOCAL::TIME::EVENT::NotificationType>());
    case WB_RES::LOCAL::WHITEBOARD_METRICS_COMM::LID:
        return getSbemLength_WHITEBOARD_METRICS_COMM(data.convertTo<WB_RES::LOCAL::WHITEBOARD_METRICS_COMM::EVENT::NotificationType>());
    }
    DEBUGLOG("getSbemLength error: Unknown localResourceId: %u", localResId);
    return 0;
}


size_t writeToSbemBuffer(void *buffer, size_t bufferLen, size_t startOffset, whiteboard::LocalResourceId localResId, const whiteboard::Value &data)
{
    switch(localResId)
    {
    case WB_RES::LOCAL::FYSSA_GYRO::LID:
        return writeToSbemBuffer_FYSSA_GYRO(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::FYSSA_GYRO::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID:
        return writeToSbemBuffer_MEAS_ACC_SAMPLERATE(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID:
        return writeToSbemBuffer_MEAS_ECG_REQUIREDSAMPLERATE(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID:
        return writeToSbemBuffer_MEAS_GYRO_SAMPLERATE(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_HR::LID:
        return writeToSbemBuffer_MEAS_HR(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::MEAS_HR::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID:
        return writeToSbemBuffer_MEAS_IMU6_SAMPLERATE(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID:
        return writeToSbemBuffer_MEAS_IMU6M_SAMPLERATE(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID:
        return writeToSbemBuffer_MEAS_IMU9_SAMPLERATE(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID:
        return writeToSbemBuffer_MEAS_MAGN_SAMPLERATE(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::EVENT::NotificationType>());
    case WB_RES::LOCAL::MEAS_TEMP::LID:
        return writeToSbemBuffer_MEAS_TEMP(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::MEAS_TEMP::EVENT::NotificationType>());
    case WB_RES::LOCAL::TIME::LID:
        return writeToSbemBuffer_TIME(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::TIME::EVENT::NotificationType>());
    case WB_RES::LOCAL::WHITEBOARD_METRICS_COMM::LID:
        return writeToSbemBuffer_WHITEBOARD_METRICS_COMM(buffer, bufferLen, startOffset, data.convertTo<WB_RES::LOCAL::WHITEBOARD_METRICS_COMM::EVENT::NotificationType>());
    }
    DEBUGLOG("writeToSbemBuffer error: Unknown localResourceId: %u", localResId);
    return 0;
}


const SbemResID2ItemIdMapping s_sbemResID2ItemIdMap[] = {
    {WB_RES::LOCAL::TIME::LID, s_possibleSbemItems[1] },
};

const SbemResID2GrpIdMapping s_sbemResID2GrpIdMap[] = {
    {WB_RES::LOCAL::FYSSA_GYRO::LID,  + 4 + 4 + 4 + 4 + 4 + 4, FYSSA_GYRO__Group },
    {WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID,  + 4 +  (1)  * (0  + 4 + 4 + 4 ) , MEAS_ACC_SAMPLERATE_1_Group },
    {WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID,  + 4 +  (2)  * (0  + 4 + 4 + 4 ) , MEAS_ACC_SAMPLERATE_2_Group },
    {WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID,  + 4 +  (3)  * (0  + 4 + 4 + 4 ) , MEAS_ACC_SAMPLERATE_3_Group },
    {WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID,  + 4 +  (4)  * (0  + 4 + 4 + 4 ) , MEAS_ACC_SAMPLERATE_4_Group },
    {WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID,  + 4 +  (5)  * (0  + 4 + 4 + 4 ) , MEAS_ACC_SAMPLERATE_5_Group },
    {WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID,  + 4 +  (6)  * (0  + 4 + 4 + 4 ) , MEAS_ACC_SAMPLERATE_6_Group },
    {WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID,  + 4 +  (7)  * (0  + 4 + 4 + 4 ) , MEAS_ACC_SAMPLERATE_7_Group },
    {WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::LID,  + 4 +  (8)  * (0  + 4 + 4 + 4 ) , MEAS_ACC_SAMPLERATE_8_Group },
    {WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID,  +  (1)  * (0  + 4 )  + 4, MEAS_ECG_REQUIREDSAMPLERATE_1_Group },
    {WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID,  +  (2)  * (0  + 4 )  + 4, MEAS_ECG_REQUIREDSAMPLERATE_2_Group },
    {WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID,  +  (3)  * (0  + 4 )  + 4, MEAS_ECG_REQUIREDSAMPLERATE_3_Group },
    {WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID,  +  (4)  * (0  + 4 )  + 4, MEAS_ECG_REQUIREDSAMPLERATE_4_Group },
    {WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID,  +  (5)  * (0  + 4 )  + 4, MEAS_ECG_REQUIREDSAMPLERATE_5_Group },
    {WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID,  +  (6)  * (0  + 4 )  + 4, MEAS_ECG_REQUIREDSAMPLERATE_6_Group },
    {WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID,  +  (7)  * (0  + 4 )  + 4, MEAS_ECG_REQUIREDSAMPLERATE_7_Group },
    {WB_RES::LOCAL::MEAS_ECG_REQUIREDSAMPLERATE::LID,  +  (8)  * (0  + 4 )  + 4, MEAS_ECG_REQUIREDSAMPLERATE_8_Group },
    {WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID,  + 4 +  (1)  * (0  + 4 + 4 + 4 ) , MEAS_GYRO_SAMPLERATE_1_Group },
    {WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID,  + 4 +  (2)  * (0  + 4 + 4 + 4 ) , MEAS_GYRO_SAMPLERATE_2_Group },
    {WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID,  + 4 +  (3)  * (0  + 4 + 4 + 4 ) , MEAS_GYRO_SAMPLERATE_3_Group },
    {WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID,  + 4 +  (4)  * (0  + 4 + 4 + 4 ) , MEAS_GYRO_SAMPLERATE_4_Group },
    {WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID,  + 4 +  (5)  * (0  + 4 + 4 + 4 ) , MEAS_GYRO_SAMPLERATE_5_Group },
    {WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID,  + 4 +  (6)  * (0  + 4 + 4 + 4 ) , MEAS_GYRO_SAMPLERATE_6_Group },
    {WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID,  + 4 +  (7)  * (0  + 4 + 4 + 4 ) , MEAS_GYRO_SAMPLERATE_7_Group },
    {WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::LID,  + 4 +  (8)  * (0  + 4 + 4 + 4 ) , MEAS_GYRO_SAMPLERATE_8_Group },
    {WB_RES::LOCAL::MEAS_HR::LID,  + 4 +  (1)  * (0  + 2 ) , MEAS_HR_1_Group },
    {WB_RES::LOCAL::MEAS_HR::LID,  + 4 +  (2)  * (0  + 2 ) , MEAS_HR_2_Group },
    {WB_RES::LOCAL::MEAS_HR::LID,  + 4 +  (3)  * (0  + 2 ) , MEAS_HR_3_Group },
    {WB_RES::LOCAL::MEAS_HR::LID,  + 4 +  (4)  * (0  + 2 ) , MEAS_HR_4_Group },
    {WB_RES::LOCAL::MEAS_HR::LID,  + 4 +  (5)  * (0  + 2 ) , MEAS_HR_5_Group },
    {WB_RES::LOCAL::MEAS_HR::LID,  + 4 +  (6)  * (0  + 2 ) , MEAS_HR_6_Group },
    {WB_RES::LOCAL::MEAS_HR::LID,  + 4 +  (7)  * (0  + 2 ) , MEAS_HR_7_Group },
    {WB_RES::LOCAL::MEAS_HR::LID,  + 4 +  (8)  * (0  + 2 ) , MEAS_HR_8_Group },
    {WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID,  + 4 +  (1)  * (0  + 4 + 4 + 4 )  +  (1)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6_SAMPLERATE_1_Group },
    {WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID,  + 4 +  (2)  * (0  + 4 + 4 + 4 )  +  (2)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6_SAMPLERATE_2_Group },
    {WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID,  + 4 +  (3)  * (0  + 4 + 4 + 4 )  +  (3)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6_SAMPLERATE_3_Group },
    {WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID,  + 4 +  (4)  * (0  + 4 + 4 + 4 )  +  (4)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6_SAMPLERATE_4_Group },
    {WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID,  + 4 +  (5)  * (0  + 4 + 4 + 4 )  +  (5)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6_SAMPLERATE_5_Group },
    {WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID,  + 4 +  (6)  * (0  + 4 + 4 + 4 )  +  (6)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6_SAMPLERATE_6_Group },
    {WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID,  + 4 +  (7)  * (0  + 4 + 4 + 4 )  +  (7)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6_SAMPLERATE_7_Group },
    {WB_RES::LOCAL::MEAS_IMU6_SAMPLERATE::LID,  + 4 +  (8)  * (0  + 4 + 4 + 4 )  +  (8)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6_SAMPLERATE_8_Group },
    {WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID,  + 4 +  (1)  * (0  + 4 + 4 + 4 )  +  (1)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6M_SAMPLERATE_1_Group },
    {WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID,  + 4 +  (2)  * (0  + 4 + 4 + 4 )  +  (2)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6M_SAMPLERATE_2_Group },
    {WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID,  + 4 +  (3)  * (0  + 4 + 4 + 4 )  +  (3)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6M_SAMPLERATE_3_Group },
    {WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID,  + 4 +  (4)  * (0  + 4 + 4 + 4 )  +  (4)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6M_SAMPLERATE_4_Group },
    {WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID,  + 4 +  (5)  * (0  + 4 + 4 + 4 )  +  (5)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6M_SAMPLERATE_5_Group },
    {WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID,  + 4 +  (6)  * (0  + 4 + 4 + 4 )  +  (6)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6M_SAMPLERATE_6_Group },
    {WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID,  + 4 +  (7)  * (0  + 4 + 4 + 4 )  +  (7)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6M_SAMPLERATE_7_Group },
    {WB_RES::LOCAL::MEAS_IMU6M_SAMPLERATE::LID,  + 4 +  (8)  * (0  + 4 + 4 + 4 )  +  (8)  * (0  + 4 + 4 + 4 ) , MEAS_IMU6M_SAMPLERATE_8_Group },
    {WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID,  + 4 +  (1)  * (0  + 4 + 4 + 4 )  +  (1)  * (0  + 4 + 4 + 4 )  +  (1)  * (0  + 4 + 4 + 4 ) , MEAS_IMU9_SAMPLERATE_1_Group },
    {WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID,  + 4 +  (2)  * (0  + 4 + 4 + 4 )  +  (2)  * (0  + 4 + 4 + 4 )  +  (2)  * (0  + 4 + 4 + 4 ) , MEAS_IMU9_SAMPLERATE_2_Group },
    {WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID,  + 4 +  (3)  * (0  + 4 + 4 + 4 )  +  (3)  * (0  + 4 + 4 + 4 )  +  (3)  * (0  + 4 + 4 + 4 ) , MEAS_IMU9_SAMPLERATE_3_Group },
    {WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID,  + 4 +  (4)  * (0  + 4 + 4 + 4 )  +  (4)  * (0  + 4 + 4 + 4 )  +  (4)  * (0  + 4 + 4 + 4 ) , MEAS_IMU9_SAMPLERATE_4_Group },
    {WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID,  + 4 +  (5)  * (0  + 4 + 4 + 4 )  +  (5)  * (0  + 4 + 4 + 4 )  +  (5)  * (0  + 4 + 4 + 4 ) , MEAS_IMU9_SAMPLERATE_5_Group },
    {WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID,  + 4 +  (6)  * (0  + 4 + 4 + 4 )  +  (6)  * (0  + 4 + 4 + 4 )  +  (6)  * (0  + 4 + 4 + 4 ) , MEAS_IMU9_SAMPLERATE_6_Group },
    {WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID,  + 4 +  (7)  * (0  + 4 + 4 + 4 )  +  (7)  * (0  + 4 + 4 + 4 )  +  (7)  * (0  + 4 + 4 + 4 ) , MEAS_IMU9_SAMPLERATE_7_Group },
    {WB_RES::LOCAL::MEAS_IMU9_SAMPLERATE::LID,  + 4 +  (8)  * (0  + 4 + 4 + 4 )  +  (8)  * (0  + 4 + 4 + 4 )  +  (8)  * (0  + 4 + 4 + 4 ) , MEAS_IMU9_SAMPLERATE_8_Group },
    {WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID,  + 4 +  (1)  * (0  + 4 + 4 + 4 ) , MEAS_MAGN_SAMPLERATE_1_Group },
    {WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID,  + 4 +  (2)  * (0  + 4 + 4 + 4 ) , MEAS_MAGN_SAMPLERATE_2_Group },
    {WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID,  + 4 +  (3)  * (0  + 4 + 4 + 4 ) , MEAS_MAGN_SAMPLERATE_3_Group },
    {WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID,  + 4 +  (4)  * (0  + 4 + 4 + 4 ) , MEAS_MAGN_SAMPLERATE_4_Group },
    {WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID,  + 4 +  (5)  * (0  + 4 + 4 + 4 ) , MEAS_MAGN_SAMPLERATE_5_Group },
    {WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID,  + 4 +  (6)  * (0  + 4 + 4 + 4 ) , MEAS_MAGN_SAMPLERATE_6_Group },
    {WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID,  + 4 +  (7)  * (0  + 4 + 4 + 4 ) , MEAS_MAGN_SAMPLERATE_7_Group },
    {WB_RES::LOCAL::MEAS_MAGN_SAMPLERATE::LID,  + 4 +  (8)  * (0  + 4 + 4 + 4 ) , MEAS_MAGN_SAMPLERATE_8_Group },
    {WB_RES::LOCAL::MEAS_TEMP::LID,  + 4 + 4, MEAS_TEMP__Group },
    {WB_RES::LOCAL::WHITEBOARD_METRICS_COMM::LID,  + 4 + 4, WHITEBOARD_METRICS_COMM__Group },
};

uint16_t getSbemDescriptorIdFromResource(whiteboard::LocalResourceId localResourceId, size_t dataLength)
{
    for (size_t i=0; i<ELEMENTS(s_sbemResID2ItemIdMap); i++)
    {
        if (s_sbemResID2ItemIdMap[i].wbResId == localResourceId)
        {
            return s_sbemResID2ItemIdMap[i].sbemItem.id;
        }
    }

    for (size_t i=0; i<ELEMENTS(s_sbemResID2GrpIdMap); i++)
    {
        if (s_sbemResID2GrpIdMap[i].wbResId == localResourceId && s_sbemResID2GrpIdMap[i].sbemBytes == dataLength)
        {
            return s_sbemResID2GrpIdMap[i].sbemGrp.id;
        }
    }
    return 0;
}

uint16_t getSbemItemsCount()
{
    return SbemValueIds_COUNT;
}

uint16_t getSbemGroupsCount()
{
    return ELEMENTS(s_possibleSbemGroups);
}

uint16_t getFirstSbemGroupId()
{
    return BEFORE_GROUPS_ID + 1;
}
