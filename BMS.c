#include <stdio.h>
#include <assert.h>
#include "Bms.h"

char ParameterName[][20] = {"Temperature","SOC","ChargeRate"};

void PrintEarlyWarningForHighTolerance(int BatteryParameter)
{
  printf("Higher Tolerance limit approached for %s",ParameterName[BatteryParameter]);
}

void PrintEarlyWarningForLowTolerance(int BatteryParameter)
{
  printf("Lower Tolerance limit approached for %s",ParameterName[BatteryParameter]);
}

float getHigherToleranceValue(int BatteryParameter)
{
  float higherToleranceValue = 0;
  
  if(BatteryParameter == BATTERYPARAMETER_TEMPERATURE )
  {
    higherToleranceValue = (float)((TOLERANCE_PERCENTILE/100)*TEMPERATURE_MAX);
  }
  else if(BatteryParameter == BATTERYPARAMETER_SOC )
  {
    higherToleranceValue = (float)((TOLERANCE_PERCENTILE/100)*SOC_MAX );
  }
  else
  {
    higherToleranceValue = (float)((TOLERANCE_PERCENTILE/100)*CHARGERATE_MAX  );
  }
  
  return higherToleranceValue;
}

float getLowerToleranceValue(int BatteryParameter)
{
  float lowerToleranceValue = 0;
  
  if(BatteryParameter == BATTERYPARAMETER_TEMPERATURE )
  {
    lowerToleranceValue = (float)((TOLERANCE_PERCENTILE/100)*TEMPERATURE_MIN );
  }
  else if(BatteryParameter == BATTERYPARAMETER_SOC )
  {
    lowerToleranceValue = (float)((TOLERANCE_PERCENTILE/100)*SOC_MIN  );
  }
  else
  {
    lowerToleranceValue = (float)((TOLERANCE_PERCENTILE/100)*CHARGERATE_MAX  );
  }
  
  return lowerToleranceValue;
}

bool IsToleranceUpperLimitApproached(int BatteryParameter, int BatteryParameterValue)
{
  float HigherToleranceValue = getHigherToleranceValue(BatteryParameter);
  
  if(HigherToleranceValue >= (BatteryParameterValue-HigherToleranceValue))
  {
    PrintEarlyWarningForHighTolerance(BatteryParameter);
    return true;
  }
  
  return false;
}

bool IsToleranceLowerLimitApproached(int BatteryParameter, int BatteryParameterValue)
{
  float lowerToleranceValue = getLowerToleranceValue(BatteryParameter);
  
  if(lowerToleranceValue <= (BatteryParameterValue+lowerToleranceValue))
  {
    PrintEarlyWarningForLowTolerance(BatteryParameter);
    return true;
  }
  
  return false;
}

bool CheckForEarlyWarning(int BatteryParameter, float BatteryParameterValue)
{
  int EarlyWarning = false;
  
  EarlyWarning = IsToleranceLowerLimitApproached(BatteryParameter,BatteryParameterValue);
  if(!EarlyWarning)
  {
    EarlyWarning = IsToleranceUpperLimitApproached(BatteryParameter,BatteryParameterValue);
  }
  
  return EarlyWarning;
}

bool batteryIsOk(float temperature, float soc, float chargeRate, EarlyWarningForBatteryParameters ParamWithEarlyWarning, bool(*BatteryTemperature_FuncPtr)(float,EarlyWarningForBatteryParameters), bool(BatterySOC_FuncPtr)(float,EarlyWarningForBatteryParameters), bool(*BatteryChargeRate_FncPtr)(float,EarlyWarningForBatteryParameters)){
  bool TemperatureCheck = BatteryTemperature_FuncPtr(temperature,ParamWithEarlyWarning);
  bool SOCCheck = BatterySOC_FuncPtr(soc,ParamWithEarlyWarning);
  bool ChargeRateCheck = BatteryChargeRate_FncPtr(chargeRate,ParamWithEarlyWarning);
  return (TemperatureCheck && SOCCheck && ChargeRateCheck);
}

int main() {
  /* Early warning not requested: Testcases to check that early warning is not given even though tolerance limit approached */
  assert(batteryIsOk(25, 70, 0.7,WarningForNone,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(batteryIsOk(0, 20, 0.7,WarningForNone,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(batteryIsOk(45, 80, 0.7,WarningForNone,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  
  /* Early warning requested for all parameters: Testcases to check that early warning is given for all parameters when tolerance limit approached */
  assert(!batteryIsOk(25, 70, 0.7,WarningForAll,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(0, 20, 0.7,WarningForAll,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(45, 80, 0.7,WarningForAll,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  
  /*assert(!batteryIsOk(50, 85, 0,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(46, 70, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(-1, 70, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(10, 18, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(10, 81, 0.7,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));
  assert(!batteryIsOk(10, 40, 0.9,&IsTemperatureValid,&IsSOCValid,&IsChargeRateValid));*/
}
