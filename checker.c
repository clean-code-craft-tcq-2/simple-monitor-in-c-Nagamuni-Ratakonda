#include <stdio.h>
#include <assert.h>

#define TEMPERATURE_MIN 0
#define TEMPERATURE_MAX 45

#define SOC_MIN 20
#define SOC_MAX 80

#define CHARGERATE_MAX 0.8

int IsChargeRateValid(float chargeRate) {
  if(chargeRate > CHARGERATE_MAX) {
      printf("Charge Rate out of range!\n");
      return 0;
  }
  else {
    return 1;
  }
}

int IsSOCValid(float soc) {
  if(soc < SOC_MIN || soc > SOC_MAX) {
      printf("State of Charge out of range!\n");
      return 0;
  }
  else {
    return 1;
  }
}

int IsTemperatureValid(float temperature) {
  if(temperature < TEMPERATURE_MIN || temperature > TEMPERATURE_MAX) {
      printf("Temperature out of range!\n");
      return 0;
  }
  else {
    return 1;
  }
}


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
