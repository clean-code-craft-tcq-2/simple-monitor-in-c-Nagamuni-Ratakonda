#include <stdio.h>
#include <assert.h>
#include "Bms.h"

char ParameterName[3] = {"Temperature","SOC","ChargeRate"};

PrintEarlyWarningForHighTolerance(int BatteryParameter)
{
  printf("Higher Tolerance limit approached for %s",ParameterName[BatteryParameter]);
}

PrintEarlyWarningForLowTolerance(int BatteryParameter)
{
  printf("Lower Tolerance limit approached for %s",ParameterName[BatteryParameter]);
}

float getHigherToleranceValue(int BatteryParameter, int BatteryParameterValue)
{
  float higherToleranceValue = 0;
  
  if(BatteryParameter == BATTERYPARAMETER_TEMPERATURE )
  {
    higherToleranceValue = (float)((5/100)*TEMPERATURE_MAX);
  }
  else if(BatteryParameter == BATTERYPARAMETER_SOC )
  {
    higherToleranceValue = (float)((5/100)*SOC_MAX );
  }
  else
  {
    higherToleranceValue = (float)((5/100)*CHARGERATE_MAX  );
  }
  
  return higherToleranceValue;
}

float getLowerToleranceValue(int BatteryParameter)
{
  float lowerToleranceValue = 0;
  
  if(BatteryParameter == BATTERYPARAMETER_TEMPERATURE )
  {
    lowerToleranceValue = (float)((5/100)*TEMPERATURE_MIN );
  }
  else if(BatteryParameter == BATTERYPARAMETER_SOC )
  {
    lowerToleranceValue = (float)((5/100)*SOC_MIN  );
  }
  else
  {
    lowerToleranceValue = (float)((5/100)*CHARGERATE_MAX  );
  }
  
  return lowerToleranceValue;
}

bool IsToleranceUpperLimitApproached(int BatteryParameter, int BatteryParameterValue)
{
  float HigherToleranceValue = getHigherToleranceValue(BatteryParameter);
  
  if(HigherToleranceValue == (BatteryParameterValue-HigherToleranceValue))
  {
    PrintEarlyWarningForHighTolerance(BatteryParameter);
    return false;
  }
  
  return true;
}

bool IsToleranceLowerLimitApproached(int BatteryParameter, int BatteryParameterValue)
{
  float lowerToleranceValue = getLowerToleranceValue(BatteryParameter);
  
  if(lowerToleranceValue == (BatteryParameterValue+lowerToleranceValue))
  {
    PrintEarlyWarningForLowTolerance(BatteryParameter);
    return false;
  }
  
  return true;
}

bool CheckForEarlyWarning(int BatteryParameter, int BatteryParameterValue)
{
  int EarlyWarning = false;
  
  EarlyWarning = IsToleranceLowerLimitApproached(BatteryParameter,BatteryParameterValue);
  if(!EarlyWarning)
  {
    EarlyWarning = IsToleranceUpperLimitApproached(BatteryParameter,BatteryParameterValue);
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
