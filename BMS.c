#include <stdio.h>
#include <assert.h>
#include "Bms.h"

int batteryIsOk(float temperature, float soc, float chargeRate, EarlyWarningForBatteryParameters ParamWithEarlyWarning, int(*IsTemperatureValid_FuncPtr)(float), int(IsSOCValid_FuncPtr)(float), int(*IsChargeRateValid_FncPtr)(float)){
  int TemperatureCheck = IsTemperatureValid_FuncPtr(temperature);
  int SOCCheck = IsSOCValid_FuncPtr(soc);
  int ChargeRateCheck = IsChargeRateValid_FncPtr(chargeRate);
  return (TemperatureCheck && SOCCheck && ChargeRateCheck);
}

int main() {
  assert(batteryIsOk(25, 70, 0.7,WarningForNone,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  /*assert(batteryIsOk(0, 20, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(batteryIsOk(45, 80, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(50, 85, 0,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(46, 70, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(-1, 70, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(10, 18, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(10, 81, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(10, 40, 0.9,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));*/
}
