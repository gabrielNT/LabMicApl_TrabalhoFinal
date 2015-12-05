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
int inputPassword[5];
int lastStateButton[4] = {0,0,0,0};
bool isCorrect = true;
int numberOfErrors = 0;
int pushCounter = 0;

//arduino ports
int passButton[4] = {13,12,7,6};

int button = 4;
int buzzer = 3;
int touchSensor = 1;
Stepper motor(STEPS,8, 9,11,10);
rgb_lcd passwordDisplay;

void setup() {
    
  pinMode(touchSensor, INPUT);
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
  for (int i = 0; i < 4; i++)
    pinMode(passButton[i], INPUT);
    
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
          savedPassword[i] = random(1,5);
        passwordDisplay.clear();
        passwordDisplay.print("Nova senha:");
        passwordDisplay.setCursor(0,1);
        for (int j = 0; j < 5; j++)
          passwordDisplay.print((char)(savedPassword[j] + 48));
        delay(5000);
        passwordDisplay.clear();
        passwordDisplay.print("Portao Fechado.");
        passwordDisplay.setCursor(0,1);
        passwordDisplay.print("Insira a senha...");
      }
      break;
      
      
      
    case Closed:      
      if(pushCounter == 5)
      {
        for (int j = 0; j < 5; j++)
        {
          Serial.println((char)(savedPassword[j] + 48));
          Serial.println(inputPassword[j]);
          if (inputPassword[j] != savedPassword[j])
          {
            if (numberOfErrors > 1)
            {
              while (true)
              {
                passwordDisplay.clear();
                passwordDisplay.print("Intruso! Intruso!");
                passwordDisplay.setRGB(255,0,0);
                delay(500);
                passwordDisplay.setRGB(0,0,0);
                delay(500);
              }
            }
            else
            {
              isCorrect = false;
              passwordDisplay.clear();
              passwordDisplay.print("Senha incorreta!");
              passwordDisplay.setCursor(0,1);
              numberOfErrors++;
              passwordDisplay.print(3-numberOfErrors);
              passwordDisplay.print(" chances");
            }
            break;
          }
        }
        pushCounter = 0;
        if (isCorrect)
        {
          gateState = Opening;
          passwordDisplay.clear();
          passwordDisplay.print("Abrindo Portao...");
        }
      }
      else
      {
        for (int k = 0; k < 4; k++)
        {
          if (digitalRead(passButton[k]) == 1 && lastStateButton[k] == 0)
          {
            Serial.println(k+1);
            inputPassword[pushCounter] = k+1;
            digitalWrite(buzzer,HIGH);
            pushCounter++;
            lastStateButton[k] = 1;
            break;
          }
          delay(5); //para capturar apenas um clique do botao
          digitalWrite(buzzer,LOW);
          lastStateButton[k] = digitalRead(passButton[k]);
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



