#include <stdio.h>
#include "Bms.h"

bool IsTemperatureValid(float temperature) {
  if(temperature < TEMPERATURE_MIN || temperature > TEMPERATURE_MAX) {
      printf("Temperature out of range!\n");
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
