#include "Bms.h"

int IsTemperatureValid(float temperature) {
  if(temperature < TEMPERATURE_MIN || temperature > TEMPERATURE_MAX) {
      printf("Temperature out of range!\n");
      return 0;
  }
  else {
    return 1;
  }
}
