#include <stdio.h>
#include <assert.h>
#include "Bms.h"

char ParameterName[][20] = {"Temperature","SOC","ChargeRate"};
char *WarningLanguages[TotalLanguages][20] = {{"High Tolerance approaching for ","Low Tolerance approaching for"},{"Hohe Toleranz nähert sich für ","Niedrige Toleranz nähert sich für "}};
earlyWarningLanguages_en languageNumber = 0;

void PrintInvalidParameterRange(int BatteryParameter)
{
  printf("%s out of range\n",ParameterName[BatteryParameter]);
}

bool isEarlyWarningRequested(int BatteryParameter, EarlyWarningForBatteryParameters ParamWithEarlyWarning)
{
  if((ParamWithEarlyWarning == WarningForAll) || (ParamWithEarlyWarning == BatteryParameter))
  {
    return true;
  }
  
  return false;
}

void PrintEarlyWarningForHighTolerance(int BatteryParameter)
{
  printf("%s%s\n",WarningLanguages[languageNumber][0],ParameterName[BatteryParameter]);
}

void PrintEarlyWarningForLowTolerance(int BatteryParameter)
{
  printf("%s%s\n",WarningLanguages[languageNumber][1],ParameterName[BatteryParameter]);
}

float getHigherToleranceValue(int BatteryParameter)
{
  float higherToleranceValue = 0;
  
  if(BatteryParameter == BATTERYPARAMETER_TEMPERATURE )
  {
    higherToleranceValue = (float)(TEMPERATURE_MAX - ((TOLERANCE_PERCENTILE/100)*TEMPERATURE_MAX));
  }
  else if(BatteryParameter == BATTERYPARAMETER_SOC )
  {
    higherToleranceValue = (float)(SOC_MAX - ((TOLERANCE_PERCENTILE/100)*SOC_MAX));
  }
  else
  {
    higherToleranceValue = (float)(CHARGERATE_MAX - ((TOLERANCE_PERCENTILE/100)*CHARGERATE_MAX));
  }
  
  return higherToleranceValue;
}

float getLowerToleranceValue(int BatteryParameter)
{
  float lowerToleranceValue = 0;
  
  if(BatteryParameter == BATTERYPARAMETER_TEMPERATURE )
  {
    lowerToleranceValue = (float)(((TOLERANCE_PERCENTILE/100)*TEMPERATURE_MAX )+TEMPERATURE_MIN);
  }
  else if(BatteryParameter == BATTERYPARAMETER_SOC )
  {
    lowerToleranceValue = (float)(((TOLERANCE_PERCENTILE/100)*SOC_MAX)+SOC_MIN);
  }
  else
  {
    lowerToleranceValue = (float)(((TOLERANCE_PERCENTILE/100)*CHARGERATE_MAX)+CHARGERATE_MIN);
  }
  
  return lowerToleranceValue;
}

bool IsToleranceUpperLimitApproached(int BatteryParameter, float BatteryParameterValue)
{
  float HigherToleranceValue = getHigherToleranceValue(BatteryParameter);
  
  if(BatteryParameterValue >= HigherToleranceValue)
  {
    PrintEarlyWarningForHighTolerance(BatteryParameter);
    return true;
  }
  
  return false;
}

bool IsToleranceLowerLimitApproached(int BatteryParameter, float BatteryParameterValue)
{
  float lowerToleranceValue = getLowerToleranceValue(BatteryParameter);
  
  if(BatteryParameterValue <= lowerToleranceValue)
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
  
  return (!EarlyWarning);
}

bool batteryIsOk(float temperature, float soc, float chargeRate, EarlyWarningForBatteryParameters ParamWithEarlyWarning, earlyWarningLanguages_en Language, bool(*BatteryTemperature_FuncPtr)(float,EarlyWarningForBatteryParameters), bool(BatterySOC_FuncPtr)(float,EarlyWarningForBatteryParameters), bool(*BatteryChargeRate_FncPtr)(float,EarlyWarningForBatteryParameters)){
  languageNumber = Language;
  bool TemperatureCheck = BatteryTemperature_FuncPtr(temperature,ParamWithEarlyWarning);
  bool SOCCheck = BatterySOC_FuncPtr(soc,ParamWithEarlyWarning);
  bool ChargeRateCheck = BatteryChargeRate_FncPtr(chargeRate,ParamWithEarlyWarning);
  return (TemperatureCheck && SOCCheck && ChargeRateCheck);
}

int main() {
  /* Language choosen English */
  /* Early warning not requested: Testcases to check that early warning is not given even though tolerance limit approached */
  assert(batteryIsOk(25, 70, 0.7,WarningForNone,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(batteryIsOk(0, 20, 0.7,WarningForNone,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(batteryIsOk(45, 80, 0.7,WarningForNone,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  
  /* Early warning requested for all parameters: Testcases to check that early warning is not given for the parameters when tolerance limit is not approached */
  assert(batteryIsOk(25, 70, 0.5,WarningForAll,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  
  /* Early warning requested for all parameters: Testcases to check that early warning is given for the parameters whose tolerance limit is approached */
  assert(!batteryIsOk(0, 20, 0.0,WarningForAll,English,&BatteryTemperature,&SOC,&BatteryChargeRate)); //Low tolerance approach
  assert(!batteryIsOk(45, 80, 0.8,WarningForAll,English,&BatteryTemperature,&SOC,&BatteryChargeRate)); //High tolerance approach
  
  /* Early warning requested for only temperature: Testcase to check that early warning is given only for temperature even when other parameters tolerance approached */
  assert(!batteryIsOk(0, 20, 0.7,WarningForTemperature,English,&BatteryTemperature,&SOC,&BatteryChargeRate)); //Low tolerance
  assert(!batteryIsOk(45, 20, 0.7,WarningForTemperature,English,&BatteryTemperature,&SOC,&BatteryChargeRate)); //High tolerance
  
  /* Early warning requested for only SOC: Testcase to check that early warning is given only for SOC even when other parameters tolerance approached */
  assert(!batteryIsOk(45, 20, 0.7,WarningForSOC,English,&BatteryTemperature,&SOC,&BatteryChargeRate)); //Low tolerance
  assert(!batteryIsOk(45, 80, 0.7,WarningForSOC,English,&BatteryTemperature,&SOC,&BatteryChargeRate)); //High tolerance
  
  /* Early warning requested for only ChargeRate: Testcase to check that early warning is given only for ChargeRate even when other parameters tolerance approached */
  assert(!batteryIsOk(45, 80, 0.0,WarningForSOC,English,&BatteryTemperature,&SOC,&BatteryChargeRate)); //Low tolerance
  assert(!batteryIsOk(45, 80, 0.8,WarningForSOC,English,&BatteryTemperature,&SOC,&BatteryChargeRate)); //High tolerance
  
  /* Testcases to check whether early warning is not given when the parameters are out of range */
  assert(!batteryIsOk(50, 85, 0,WarningForAll,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(46, 70, 0.7,WarningForAll,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(-1, 70, 0.7,WarningForAll,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(10, 18, 0.8,WarningForAll,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(10, 81, 0.7,WarningForAll,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(10, 40, 0.9,WarningForAll,English,&BatteryTemperature,&SOC,&BatteryChargeRate));
  
  /* Language choosen German */
  /* Early warning not requested: Testcases to check that early warning is not given even though tolerance limit approached */
  assert(batteryIsOk(25, 70, 0.7,WarningForNone,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(batteryIsOk(0, 20, 0.7,WarningForNone,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(batteryIsOk(45, 80, 0.7,WarningForNone,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
  
  /* Early warning requested for all parameters: Testcases to check that early warning is not given for the parameters when tolerance limit is not approached */
  assert(batteryIsOk(25, 70, 0.5,WarningForAll,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
  
  /* Early warning requested for all parameters: Testcases to check that early warning is given for the parameters whose tolerance limit is approached */
  assert(!batteryIsOk(0, 20, 0.0,WarningForAll,German,&BatteryTemperature,&SOC,&BatteryChargeRate)); //Low tolerance approach
  assert(!batteryIsOk(45, 80, 0.8,WarningForAll,German,&BatteryTemperature,&SOC,&BatteryChargeRate)); //High tolerance approach
  
  /* Early warning requested for only temperature: Testcase to check that early warning is given only for temperature even when other parameters tolerance approached */
  assert(!batteryIsOk(0, 20, 0.7,WarningForTemperature,German,&BatteryTemperature,&SOC,&BatteryChargeRate)); //Low tolerance
  assert(!batteryIsOk(45, 20, 0.7,WarningForTemperature,German,&BatteryTemperature,&SOC,&BatteryChargeRate)); //High tolerance
  
  /* Early warning requested for only SOC: Testcase to check that early warning is given only for SOC even when other parameters tolerance approached */
  assert(!batteryIsOk(45, 20, 0.7,WarningForSOC,German,&BatteryTemperature,&SOC,&BatteryChargeRate)); //Low tolerance
  assert(!batteryIsOk(45, 80, 0.7,WarningForSOC,German,&BatteryTemperature,&SOC,&BatteryChargeRate)); //High tolerance
  
  /* Early warning requested for only ChargeRate: Testcase to check that early warning is given only for ChargeRate even when other parameters tolerance approached */
  assert(!batteryIsOk(45, 80, 0.0,WarningForSOC,German,&BatteryTemperature,&SOC,&BatteryChargeRate)); //Low tolerance
  assert(!batteryIsOk(45, 80, 0.8,WarningForSOC,German,&BatteryTemperature,&SOC,&BatteryChargeRate)); //High tolerance
  
  /* Testcases to check whether early warning is not given when the parameters are out of range */
  assert(!batteryIsOk(50, 85, 0,WarningForAll,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(46, 70, 0.7,WarningForAll,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(-1, 70, 0.7,WarningForAll,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(10, 18, 0.8,WarningForAll,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(10, 81, 0.7,WarningForAll,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
  assert(!batteryIsOk(10, 40, 0.9,WarningForAll,German,&BatteryTemperature,&SOC,&BatteryChargeRate));
}
