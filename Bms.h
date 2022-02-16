#define TEMPERATURE_MIN 0
#define TEMPERATURE_MAX 45

#define SOC_MIN 20
#define SOC_MAX 80

#define CHARGERATE_MAX 0.8

typedef enum
{
  WarningForNone = 0,
  WarningForTemperature = 1,
  WarningForSOC = 2,
  WarningForChargeRate = 3,
  WarningForAll = 4
}EarlyWarningForBatteryParameters;

int IsChargeRateValid(float chargeRate, EarlyWarningForBatteryParameters ParamWithEarlyWarning);
int IsSOCValid(float soc, EarlyWarningForBatteryParameters ParamWithEarlyWarning);
int IsTemperatureValid(float temperature, EarlyWarningForBatteryParameters ParamWithEarlyWarning);
int batteryIsOk(float temperature, float soc, float chargeRate, EarlyWarningForBatteryParameters ParamWithEarlyWarning, int(*IsTemperatureValid_FuncPtr)(float), int(IsSOCValid_FuncPtr)(float), int(*IsChargeRateValid_FncPtr)(float));
