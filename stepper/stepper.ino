#include <Stepper.h>
#define STEPS 200

Stepper stepper(STEPS, 5, 4, 3, 2);

void setup() {
  stepper.setSpeed(60);

}

void loop() {
  stepper.step(200);

}
