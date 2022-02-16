#include <stdio.h>
#include "Bms.h"

int IsSOCValid(float soc, EarlyWarningForBatteryParameters ParamWithEarlyWarning) {
  if(soc < SOC_MIN || soc > SOC_MAX) {
      printf("State of Charge out of range!\n");
      return 0;
  }
  
  return 1;
}
