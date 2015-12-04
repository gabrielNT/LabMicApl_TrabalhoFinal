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
int numberOfErrors = 0;

//arduino ports
int button = 4;
int buzzer = 3;
int touchSensor = 1;
Stepper motor(STEPS,8, 9,11,10);
rgb_lcd passwordDisplay;

void setup() {
  pinMode(touchSensor, INPUT);
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
  
  passwordDisplay.begin(16,2);
  passwordDisplay.setRGB(255,100,100);
  passwordDisplay.print("Portao Aberto");
  gateState = Open; //The gate starts open
  Serial.begin(9600);
  motor.setSpeed(100);
  
  // if analog input pin 2 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(2));
}

void loop() 
{
  Serial.println(gateState);
  switch (gateState)
  {
    case Open:
      if(digitalRead(button) == HIGH)
      {
        gateState = Closing;
        passwordDisplay.clear();        
        passwordDisplay.print("Fechando Portao...");
      }
      break;
    case Closing:
      motor.step(-100);

      if (analogRead(touchSensor) > 500)// the gate has closed
      {
        gateState = Closed;
        for (int i = 0; i < 5; i++)
          savedPassword[i] = (char)random(33,126);
        passwordDisplay.clear();
        passwordDisplay.print("Nova senha:");
        passwordDisplay.setCursor(0,1);
        passwordDisplay.print(savedPassword);
        delay(5000);
        passwordDisplay.clear();
        passwordDisplay.print("Portao Fechado.");
        passwordDisplay.setCursor(0,1);
        passwordDisplay.print("Insira a senha...");
      }
      break;
    case Closed:
      Serial.println(savedPassword);
      if (Serial.available() == 5)
      { 
        isCorrect = true;
        for (int j = 0; j < 5; j++)
        {
          if (savedPassword[j] !=  Serial.read())
          {
            isCorrect = false;
            passwordDisplay.clear();
            passwordDisplay.print("Senha incorreta!");
            passwordDisplay.setCursor(0,1);
            numberOfErrors++;
            passwordDisplay.print(3-numberOfErrors);
            passwordDisplay.print(" chances");
            break;
          }
        }
        if (isCorrect)
        {
          gateState = Opening;
          passwordDisplay.clear();
          passwordDisplay.print("Abrindo Portao...");
        }
      }
      break;
    case Opening:
      motor.step(100);
      if (analogRead(touchSensor) > 500)// the gate has closed
      {
        gateState = Open;
        passwordDisplay.clear();
        passwordDisplay.print("Portao Aberto");
        //delay(5000);
      }
      break;
    
  }
}



