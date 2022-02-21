#include <stdio.h>
#include "Bms.h"

bool IsTemperatureValid(float temperature) {
  if(temperature < TEMPERATURE_MIN || temperature > TEMPERATURE_MAX) {
      PrintInvalidParameterRange(BATTERYPARAMETER_TEMPERATURE);
      return false;
  }
  
  return true;
}

bool BatteryTemperature(float temperature, EarlyWarningForBatteryParameters ParamWithEarlyWarning){
  bool batteryTemperatureResult = false;
  
  batteryTemperatureResult = IsTemperatureValid(temperature);
  
  if(batteryTemperatureResult)
  {
    if(isEarlyWarningRequested(BATTERYPARAMETER_TEMPERATURE,ParamWithEarlyWarning))
    {
      batteryTemperatureResult = CheckForEarlyWarning(BATTERYPARAMETER_TEMPERATURE, temperature);
    }
  }
  
  return batteryTemperatureResult;
}
