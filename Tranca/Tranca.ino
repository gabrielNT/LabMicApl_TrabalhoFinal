#include <rgb_lcd.h>
#include <Stepper.h>
#include <Wire.h>

//motor steps
#define STEPS 100

//system states
#define Open 0
#define Closing 1
#define Closed 2
#define Opening 3

//program variables
int gateState;
char savedPassword[5];
char inputPassword[5];
bool isCorrect = false;

//arduino ports
int button = 4;
int touchSensor = 0;
Stepper motor(STEPS,8, 9,11,10);
rgb_lcd passwordDisplay;

void setup() {
  pinMode(touchSensor, INPUT);
  pinMode(button, INPUT);
  
  passwordDisplay.begin(16,2);
  passwordDisplay.setRGB(255,100,100);
  passwordDisplay.noDisplay();
  gateState = Open; //The gate starts open
  Serial.begin(9600);
  motor.setSpeed(100);
}

void loop() 
{
  switch (gateState)
  {
    case Open:
      if(digitalRead(button) == HIGH)
      {
        gateState = Closing;        
      }
      break;
    case Closing:
      motor.step(-100);
      if (analogRead(touchSensor) > 900)// the gate has closed
      {
        gateState = Closed;
        for (int i = 0; i < 5; i++)
          savedPassword[i] = (char)random(33,126);
        passwordDisplay.display();
        passwordDisplay.print(savedPassword);
        delay(5000);
        passwordDisplay.clear();
        passwordDisplay.noDisplay();
      }
      break;
    case Closed:
      if (Serial.available() == 5)
      {
        isCorrect = true;
        for (int j = 0; j < 5; j++)
        {
          if (savedPassword[j] !=  Serial.read())
          {
            isCorrect = false;
            break;
          }
        }
        if (isCorrect)
          gateState = Opening;
      }
      break;
    case Opening:
      break;
    
  }
}



