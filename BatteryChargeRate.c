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
  return (IsChargeRateValid(chargeRate) && (CheckForEarlyWarning(BATTERYPARAMETER_TEMPERATURE, chargeRate)));
}
