#include <stdio.h>
#include "Bms.h"

bool IsChargeRateValid(float chargeRate)
{
  if(chargeRate < 0.0 || chargeRate > 0.8)
  {
    PrintInvalidParameterRange(BATTERYPARAMETER_CHARGERATE);
    return false;
  }
  
  return true;
}

bool BatteryChargeRate(float chargeRate, EarlyWarningForBatteryParameters ParamWithEarlyWarning) {
  
  bool batteryChargeRateResult = false;
  
  batteryChargeRateResult = IsChargeRateValid(chargeRate);
  if(batteryChargeRateResult)
  {
    if(isEarlyWarningRequested(BATTERYPARAMETER_CHARGERATE,ParamWithEarlyWarning))
    {
       batteryChargeRateResult = CheckForEarlyWarning(BATTERYPARAMETER_CHARGERATE, chargeRate);
    }
  }
  
  return batteryChargeRateResult;
}
