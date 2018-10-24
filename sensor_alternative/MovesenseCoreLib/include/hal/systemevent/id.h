#pragma once
/******************************************************************************

Copyright (c) Suunto Oy 2016.
All rights reserved.

******************************************************************************/

// Module definitions for System Event logging

// System Event Module IDs.
// Please note: ID codes MUST be 12 bit in length or shorter (max module ID 0xfff)
// **
// ** NOTE: Remember to execute tools/wbtool/systemevent/autogen.sh after
// **       modifying the origin ID list (hal/systemevent/id.h)
// **
enum SystemEventModule
{

    // Reserved for hard faults, asserts and similar
    SYSTEM_EVENT_ID_FAULT = 0x000,

    // Whiteboard

    SYSTEM_EVENT_ID_WBAPI = 0x100,
    SYSTEM_EVENT_ID_WBCOMM = 0x101,
    SYSTEM_EVENT_ID_WBDEVD = 0x102,
    SYSTEM_EVENT_ID_WBMAIN = 0x103,
    SYSTEM_EVENT_ID_WBPORT = 0x104,

    // Operating System internals

    SYSTEM_EVENT_ID_SCHEDULER = 0x200,
    SYSTEM_EVENT_ID_MPU = 0x201,
    SYSTEM_EVENT_ID_WATCHDOG = 0x202,
    SYSTEM_EVENT_ID_POWER_STATE = 0x203,
    SYSTEM_EVENT_ID_DRT = 0x204,
    SYSTEM_EVENT_ID_BOOTLOOP = 0x205,

    // Communications

    SYSTEM_EVENT_ID_SPI = 0x300,
    SYSTEM_EVENT_ID_I2C = 0x301,
    SYSTEM_EVENT_ID_UART = 0x302,
    SYSTEM_EVENT_ID_BLE = 0x303,
    SYSTEM_EVENT_ID_WIFI = 0x304,

    // Software Platform

    SYSTEM_EVENT_ID_LOGGER = 0x400,
    SYSTEM_EVENT_ID_FILESYSTEM = 0x401,
    SYSTEM_EVENT_ID_SPEEDFUSION = 0x402,
    SYSTEM_EVENT_ID_INTERCHIP = 0x403,
    SYSTEM_EVENT_ID_SETTINGS = 0x404,
    SYSTEM_EVENT_ID_COMPASS = 0x405,
    SYSTEM_EVENT_ID_PERIPHERAL_FIRMWARE = 0x406,
    SYSTEM_EVENT_ID_FWUPDATE = 0x407,
    SYSTEM_EVENT_ID_ALTIFUSION = 0x408,

    // Application Middleware Modules

    SYSTEM_EVENT_ID_ACTIVITY = 0x500,
    SYSTEM_EVENT_ID_NAVIGATION = 0x501,
    SYSTEM_EVENT_ID_LAPENGINE = 0x502,
    SYSTEM_EVENT_ID_SYNC = 0x503,
    SYSTEM_EVENT_ID_TRAININGLAB = 0x504,
    SYSTEM_EVENT_ID_SLEEP = 0x505,

    // Application User Interface Engine

    SYSTEM_EVENT_ID_APPLICATION = 0x600,
    SYSTEM_EVENT_ID_UI_FRAMEWORK = 0x601,
    SYSTEM_EVENT_ID_DUKTAPE = 0x602,

    // Sensors and devices

    SYSTEM_EVENT_ID_MAGNETOMETER = 0x701,
    SYSTEM_EVENT_ID_GPS = 0x702,
    SYSTEM_EVENT_ID_DISPLAY = 0x703,
    SYSTEM_EVENT_ID_TOUCH = 0x704,
    SYSTEM_EVENT_ID_ACCELEROMETER = 0x705,
    SYSTEM_EVENT_ID_GYROSCOPE = 0x706,
    SYSTEM_EVENT_ID_VIBRA = 0x707,
    SYSTEM_EVENT_ID_BUZZER = 0x708,
    SYSTEM_EVENT_ID_EXT_FLASH = 0x709,
    SYSTEM_EVENT_ID_INT_FLASH = 0x70A,
    SYSTEM_EVENT_ID_PMIC = 0x70B,
    SYSTEM_EVENT_ID_FUEL_GAUGE = 0x70C,
    SYSTEM_EVENT_ID_BUTTON = 0x70D,
    SYSTEM_EVENT_ID_PRESSURE = 0x70E,
    SYSTEM_EVENT_ID_OHR = 0x70F,
};
