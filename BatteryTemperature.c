#include <stdio.h>
#include "Bms.h"

bool IsTemperatureValid(float temperature, EarlyWarningForBatteryParameters ParamWithEarlyWarning) {
  if(temperature < TEMPERATURE_MIN || temperature > TEMPERATURE_MAX) {
      printf("Temperature out of range!\n");
      return false;
  }
  
  return true;
}
