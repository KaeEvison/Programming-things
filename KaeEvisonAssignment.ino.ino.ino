#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Pushbutton.h>

const int ledPin = 13; // the pin that the LED is attached to
int incomingByte;      // holds keystrokes
ZumoMotors motors;
ZumoReflectanceSensorArray reflectanceSensors;
Pushbutton button(ZUMO_BUTTON);
#define NUM_SENSORS 6
unsigned int sensorValues[NUM_SENSORS];
const int THRESHOLD = 500;
bool roomCheck = false;
int roomNumber = 0;
bool roomNumberBroadcast = true;
String rooms[10];


void setup()
{
   //initialisation
  Serial.begin(9600);
  Serial.println("\n\n\n\n\n\nInitialising...");
  pinMode(ledPin, OUTPUT);
  reflectanceSensors.init();
   //wait for user
  digitalWrite(ledPin, HIGH);
  Serial.println("Initialisation complete");
  Serial.println("Place Zumo on the marked line and press button for calibration");
  button.waitForButton();
  delay(1000);
   //calibrate
  Serial.println("Calibrating...");
  for (int speed = 0; speed <= 50; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  unsigned long startTime = millis();
  while(millis() - startTime < 1500)
  {
    reflectanceSensors.calibrate();
  }
  for (int speed = 50; speed > 0; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  for (int speed = 0; speed <= 50; speed++)
  {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(-speed);
    delay(2);
  }
  startTime = millis();
  while(millis() - startTime < 1500)
  {
    reflectanceSensors.calibrate();
  }
  for (int speed = 50; speed > 0; speed--)
  {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(-speed);
    delay(2);
  }
  for (int speed = 0; speed <= 50; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  startTime = millis();
  while(millis() - startTime < 1500)
  {
    reflectanceSensors.calibrate();
  }
  for (int speed = 50; speed > 0; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  for (int speed = 0; speed <= 50; speed++)
  {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(-speed);
    delay(2);
  }
  startTime = millis();
  while(millis() - startTime < 1500)
  {
    reflectanceSensors.calibrate();
  }
  for (int speed = 50; speed > 0; speed--)
  {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(-speed);
    delay(2);
  }

//  Outputs maximum and minimum sensor values during calibration for testing purposes
//  for (byte i = 0; i < NUM_SENSORS; i++)
//  {
//    Serial.print("\n\nSensor: ");
//    Serial.print(i);
//    Serial.print("\nMinimum value: ");
//    Serial.print(reflectanceSensors.calibratedMinimumOn[i]);
//    Serial.print("\nMaximum value: ");
//    Serial.print(reflectanceSensors.calibratedMaximumOn[i]);
//  }
  
   //calibration complete
  Serial.println("Calibration complete");
  digitalWrite(ledPin, LOW);
}

void loop()
{
   //Read incoming keystrokes
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();

     //LED test
    if (incomingByte == 'H')
    {
      digitalWrite(ledPin, HIGH);
    }
    if (incomingByte == 'L')
    {
      digitalWrite(ledPin, LOW);
    }
    

     //Manual control
      if (incomingByte == 'W')
      {
        for (int speed = 0; speed <= 100; speed++)
        {
          motors.setLeftSpeed(speed);
          motors.setRightSpeed(speed);
          delay(2);
        }
        
        for (int speed = 100; speed >= 0; speed--)
        {
          motors.setLeftSpeed(speed);
          motors.setRightSpeed(speed);
          delay(2);
        }
      }
  
  
      if (incomingByte == 'A')
      {   
        motors.setRightSpeed(200);
        motors.setLeftSpeed(-200);
  
        delay(95);
        
        motors.setRightSpeed(0);
        motors.setLeftSpeed(0);

        if (roomNumberBroadcast == false)
        {
          roomNumberBroadcast = true;
          Serial.print("\nEntering room number ");
          Serial.print(roomNumber);
          Serial.println(" on the left");
          rooms[roomNumber] = "LEFT";
        }
      }
          
      
      if (incomingByte == 'S')
      {
        for (int speed = 0; speed <= 100; speed++)
        {
          motors.setRightSpeed(-speed);
          motors.setLeftSpeed(-speed)  ;
          delay(2);
        }
        
        for (int speed = 100; speed >= 0; speed--)
        {
            motors.setRightSpeed(-speed);
            motors.setLeftSpeed(-speed);
            delay(2);
        }
      }
      
      
      if (incomingByte == 'D')
      {
        motors.setRightSpeed(-200);
        motors.setLeftSpeed(200);
  
        delay(95);
        
        motors.setRightSpeed(0);
        motors.setLeftSpeed(0);

        if (roomNumberBroadcast == false)
        {
          roomNumberBroadcast = true;
          Serial.print("\nEntering room number ");
          Serial.print(roomNumber);
          Serial.println(" on the right");
          rooms[roomNumber] = "RIGHT";
        }
      }

    if (incomingByte == 'F')
    {
      if (roomCheck == true)
      {
        roomCheck = false;
        Serial.println("\nRoom check complete");
      }
        
      for (int speed = 0; speed <= 50; speed++)
      { 
        motors.setLeftSpeed(speed);
        motors.setRightSpeed(speed);
        delay(2);
      }
    }

    if (incomingByte == ' ')
    {
      motors.setLeftSpeed(0);
      motors.setRightSpeed(0);
    }


     //Signal room check
    if (incomingByte == 'R')
    {
      if (roomCheck == false)
      {
        roomCheck = true;
        roomNumber++;
        Serial.println("\nRoom check initiated");
        roomNumberBroadcast = false;
      }
      else
      {
        Serial.println("\nScanning room...");
        delay(1000);
        motors.setLeftSpeed(100);
        motors.setRightSpeed(-100);
        delay(750);
        motors.setLeftSpeed(0);
        motors.setRightSpeed(0);
        delay(1000);
        for (int i = 0; i < 6; i++)
        {
          motors.setLeftSpeed(-100);
          motors.setRightSpeed(100);
          delay(250);
          motors.setLeftSpeed(0);
          motors.setRightSpeed(0);
          //scan
          delay(500);
        }
        delay(1000);
        motors.setLeftSpeed(100);
        motors.setRightSpeed(-100);
        delay(1000);
        motors.setLeftSpeed(0);
        motors.setRightSpeed(0);
        Serial.println("Scan complete");
      }
    }


     //Output variables for testing purposes
    if (incomingByte == 'V')
    {
      for (int i = 0; i < 10; i++)
      {
        Serial.print("\nRoom number: ");
        Serial.println(i);
        Serial.print("Direction: ");
        Serial.println(rooms[i]);
      }
    }
  }
  
  unsigned int position = reflectanceSensors.readLine(sensorValues);

  for (byte i = 0; i < NUM_SENSORS; i++)
  {
//    Ouput sensor values for testing purposes
//    Serial.print(i);
//    Serial.print(":");
//    Serial.println(sensorValues[i]);
    if (sensorValues[i] > THRESHOLD)
    {
      motors.setLeftSpeed(0);
      motors.setRightSpeed(0);
      Serial.println("Wall detected");
    }
  }
}
