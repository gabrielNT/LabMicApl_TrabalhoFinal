#include <Stepper.h>
#define STEPS 100

Stepper stepper(STEPS, 8, 9, 11, 10);

void setup() {
  stepper.setSpeed(100);

}

void loop() {
  stepper.step(-100);

}
