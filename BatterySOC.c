#include <stdio.h>
#include "Bms.h"

bool IsSOCValid(float soc) {
  if(soc < SOC_MIN || soc > SOC_MAX) {
      printf("State of Charge out of range!\n");
      return false;
  }
  
  return true;
}

bool SOC(float soc, EarlyWarningForBatteryParameters ParamWithEarlyWarning){
  
  bool SOCResult = false;
 
  SOCResult = IsSOCValid(soc);
  if(SOCResult)
  {
    if(ParamWithEarlyWarning != WarningForNone)
    {
      SOCResult = CheckForEarlyWarning(WarningForSOC, chargeRate);
    }
  }
  
  return SOCResult;
}
