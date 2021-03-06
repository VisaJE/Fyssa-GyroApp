#include "GyroService.h"
#include "movesense.h"

MOVESENSE_APPLICATION_STACKSIZE(1024)

MOVESENSE_PROVIDERS_BEGIN(1)

MOVESENSE_PROVIDER_DEF(GyroService)

MOVESENSE_PROVIDERS_END(1)

MOVESENSE_FEATURES_BEGIN()
// Explicitly enable or disable Movesense framework core modules.
// List of modules and their default state is found in documentation
OPTIONAL_CORE_MODULE(DataLogger, true)
OPTIONAL_CORE_MODULE(Logbook, true)
OPTIONAL_CORE_MODULE(LedService, true)
OPTIONAL_CORE_MODULE(IndicationService, true)
OPTIONAL_CORE_MODULE(BleService, true)
OPTIONAL_CORE_MODULE(EepromService, true)
OPTIONAL_CORE_MODULE(BypassService, false)
OPTIONAL_CORE_MODULE(BleStandardHRS, false)
OPTIONAL_CORE_MODULE(BleNordicUART, false)

//Debug!
OPTIONAL_CORE_MODULE(DebugService, true)

APPINFO_NAME("FyssaGyro");
APPINFO_VERSION("0.1.1.IMU");
APPINFO_COMPANY("Fyysikkokilta");

SERIAL_COMMUNICATION(false) // Warning: enabling this feature will increase power consumption
BLE_COMMUNICATION(true)
MOVESENSE_FEATURES_END()
