#include <stdio.h>
#include <assert.h>
#include "Bms.h"

int batteryIsOk(float temperature, float soc, float chargeRate) {
  int TemperatureCheck = IsTemperatureValid(temperature);
  int SOCCheck = IsSOCValid(soc);
  int ChargeRateCheck = IsChargeRateValid(chargeRate);
  return (TemperatureCheck && SOCCheck && ChargeRateCheck);
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
