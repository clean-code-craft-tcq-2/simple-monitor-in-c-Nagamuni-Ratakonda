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
    if(ParamWithEarlyWarning != WarningForNone)
    {
       batteryChargeRateResult = CheckForEarlyWarning(BATTERYPARAMETER_TEMPERATURE, chargeRate);
    }
  }
  
  return batteryChargeRateResult;
}
