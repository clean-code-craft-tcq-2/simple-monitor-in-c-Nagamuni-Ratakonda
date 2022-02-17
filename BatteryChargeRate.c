#include <stdio.h>
#include "Bms.h"

bool IsChargeRateValid(float chargeRate)
{
  if(chargeRate > CHARGERATE_MAX )
  {
    printf("Charge Rate out of range!\n");
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
       batteryChargeRateResult = CheckForEarlyWarning(BATTERYPARAMETER_CHARGERATE , chargeRate);
    }
  }
  
  return batteryChargeRateResult;
}
