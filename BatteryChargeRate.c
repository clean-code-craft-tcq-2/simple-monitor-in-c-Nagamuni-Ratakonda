#include <stdio.h>
#include "Bms.h>

int IsChargeRateValid(float chargeRate) {
  if(chargeRate > CHARGERATE_MAX) {
      printf("Charge Rate out of range!\n");
      return 0;
  }
  
  return 1;
}
