#include <rgb_lcd.h>
#include <Wire.h>
#include <Stepper.h>
#define STEPS 100

Stepper stepper(STEPS, 8, 9, 11, 10);
rgb_lcd lcd;


void setup() {
  stepper.setSpeed(100);
  lcd.begin(16,2);
  lcd.setRGB(0,0,255);
  lcd.print("Teste do LCD");
  delay(1000);
}

void loop() {
  stepper.step(-100);

}
