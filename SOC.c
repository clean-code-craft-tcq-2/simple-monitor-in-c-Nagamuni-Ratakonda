#include <stdio.h>
#include "Bms.h"

int IsSOCValid(float soc) {
  if(soc < SOC_MIN || soc > SOC_MAX) {
      printf("State of Charge out of range!\n");
      return 0;
  }
  
  return 1;
}
