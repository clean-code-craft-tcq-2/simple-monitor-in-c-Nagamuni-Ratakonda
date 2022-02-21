#include <stdbool.h>

#define BATTERYPARAMETER_TEMPERATURE 0
#define BATTERYPARAMETER_SOC 1
#define BATTERYPARAMETER_CHARGERATE 2

#define TEMPERATURE_MIN 0
#define TEMPERATURE_MAX 45

#define SOC_MIN 20
#define SOC_MAX 80

#define CHARGERATE_MIN 0.0
#define CHARGERATE_MAX 0.8

#define TOLERANCE_LOWERLIMIT_APPROACHED 0
#define TOLERANCE_HIGHERLIMIT_APPROACHED 1

#define TOLERANCE_PERCENTILE 5

typedef enum
{
  WarningForTemperature = 0,
  WarningForSOC = 1,
  WarningForChargeRate = 2,
  WarningForAll = 3,
  WarningForNone = 4
}EarlyWarningForBatteryParameters;

typedef enum
{
  English = 0,
  German,
  TotalLanguages
}earlyWarningLanguages_en;

bool IsChargeRateValid(float chargeRate);
bool BatteryChargeRate(float chargeRate, EarlyWarningForBatteryParameters ParamWithEarlyWarning);
bool SOC(float soc, EarlyWarningForBatteryParameters ParamWithEarlyWarning);
bool IsSOCValid(float soc);
bool BatteryTemperature(float temperature, EarlyWarningForBatteryParameters ParamWithEarlyWarning);
bool IsTemperatureValid(float temperature);
bool batteryIsOk(float temperature, float soc, float chargeRate, EarlyWarningForBatteryParameters ParamWithEarlyWarning, earlyWarningLanguages_en Language, bool(*IsTemperatureValid_FuncPtr)(float,EarlyWarningForBatteryParameters), bool(IsSOCValid_FuncPtr)(float,EarlyWarningForBatteryParameters), bool(*IsChargeRateValid_FncPtr)(float,EarlyWarningForBatteryParameters));
bool CheckForEarlyWarning(int BatteryParameter, float BatteryParameterValue);
bool IsToleranceLowerLimitApproached(int BatteryParameter, float BatteryParameterValue);
bool IsToleranceUpperLimitApproached(int BatteryParameter, float BatteryParameterValue);
float getLowerToleranceValue(int BatteryParameter);
float getHigherToleranceValue(int BatteryParameter);
void PrintEarlyWarningForLowTolerance(int BatteryParameter);
void PrintEarlyWarningForHighTolerance(int BatteryParameter);
bool isEarlyWarningRequested(int BatteryParameter, EarlyWarningForBatteryParameters ParamWithEarlyWarning);
void PrintInvalidParameterRange(int BatteryParameter);
