#define TEMPERATURE_MIN 0
#define TEMPERATURE_MAX 45

#define SOC_MIN 20
#define SOC_MAX 80

#define CHARGERATE_MAX 0.8

int IsChargeRateValid(float chargeRate);
int IsSOCValid(float soc);
int IsTemperatureValid(float temperature);
int batteryIsOk(float temperature, float soc, float chargeRate, int(*IsTemperatureValid_FuncPtr)(float), int(IsSOCValid_FuncPtr)(float), int(*IsChargeRateValid_FncPtr)(float));
