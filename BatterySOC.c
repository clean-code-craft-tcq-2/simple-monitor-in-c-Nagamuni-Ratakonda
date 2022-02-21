#include <stdio.h>
#include "Bms.h"

bool IsSOCValid(float soc) {
  if(soc < SOC_MIN || soc > SOC_MAX) {
      PrintInvalidParameterRange(BATTERYPARAMETER_SOC);
      return false;
  }
  
  return true;
}

bool SOC(float soc, EarlyWarningForBatteryParameters ParamWithEarlyWarning){
  
  bool SOCResult = false;
 
  SOCResult = IsSOCValid(soc);
  if(SOCResult)
  {
    if(isEarlyWarningRequested(BATTERYPARAMETER_SOC,ParamWithEarlyWarning))
    {
      SOCResult = CheckForEarlyWarning(BATTERYPARAMETER_SOC, soc);
    }
  }
  
  return SOCResult;
}
