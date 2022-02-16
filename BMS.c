#include <stdio.h>
#include <assert.h>
#include "Bms.h"

PrintEarlyWarningForLowTolerance(int BatteryParameter)
{
  printf("Lower Tolerance limit approached for");
}

bool IsToleranceLowerLimitApproached(int BatteryParameter, int BatteryParamLowerLimit)
{
  float lowerToleranceValue = getLowerToleranceValue(BatteryParameter,BatteryParamLowerLimit);
  
  if(lowerToleranceValue == (BatteryParamLowerLimit+lowerToleranceValue))
  {
    PrintEarlyWarningForLowTolerance(BatteryParameter);
    return false;
  }
  
  return true;
}

bool CheckForEarlyWarning(int BatteryParameter, int BatteryParamLowerLimit, int BatteryParamHigherLimit, EarlyWarningForBatteryParameters ParamWithEarlyWarning)
{
  int EarlyWarning = false;
  
  EarlyWarning = IsToleranceLowerLimitApproached(BatteryParameter,BatteryParamLowerLimit);
  if(!EarlyWarning)
  {
    EarlyWarning = IsToleranceUpperLimitApproached(BatteryParameter,BatteryParamHigherLimit);
  }
  
  return EarlyWarning;
}

bool batteryIsOk(float temperature, float soc, float chargeRate, EarlyWarningForBatteryParameters ParamWithEarlyWarning, int(*IsTemperatureValid_FuncPtr)(float), int(IsSOCValid_FuncPtr)(float), int(*IsChargeRateValid_FncPtr)(float)){
  bool TemperatureCheck = IsTemperatureValid_FuncPtr(temperature,ParamWithEarlyWarning);
  bool SOCCheck = IsSOCValid_FuncPtr(soc,ParamWithEarlyWarning);
  bool ChargeRateCheck = IsChargeRateValid_FncPtr(chargeRate,ParamWithEarlyWarning);
  return (TemperatureCheck && SOCCheck && ChargeRateCheck,ParamWithEarlyWarning);
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
