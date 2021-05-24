//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Stepper.h>
//--------------Code for antenna-------/
//create an RF24 object
RF24 radio(9, 8);  // CE, CSN 
const byte address[6] = "00001";//address through which two modules communicate.
//--------------Code for Stepper-------/
const int stepPin = 3; 
const int dirPin = 2; 
const int stepsPerRevolution = 6400;  
Stepper myStepper(stepsPerRevolution,2,3);// initialize the stepper library on pins 8 through 11:

void setup()
{
    myStepper.setSpeed(1);

  //--------------Code for antenna-------/
  Serial.begin(9600);
  radio.begin();
  //set the address
  radio.openReadingPipe(0, address);
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  cock();
  anticock();
}

void cock()
{
  int i = 6400;
  while(i > 0)
  {
    if (radio.available())
    {
      int text = 0;
      radio.read(&text, sizeof(text));
      Serial.println(text);
      if(text==1111)
      {
        digitalWrite(stepPin,LOW);
        digitalWrite(dirPin,LOW);
        break;
      }
      else
      {
        myStepper.step(1);
        i--;
      }
        
    }
    else
      continue;
  }
}

void anticock()
{
    int i = 6400;
    while(i > 0)
    { 
      if (radio.available())
      {
        int text = 0;
        radio.read(&text, sizeof(text));
        Serial.println(text);
        if(text==1111)
        {
          digitalWrite(stepPin,LOW);
          digitalWrite(dirPin,LOW);
          break;
        }
        else
        {
          myStepper.step(-1);
          i--;
        }
          
      }
      else
        continue;
    }
}

//void Clockwise() 
//{
//  for(int x = 0; x < 200; x++) 
//  { 
//    if (radio.available())
//    {
//      int text = 0;
//      radio.read(&text, sizeof(text));
//      Serial.println(text);
//      if(text==1111)
//      {
//        digitalWrite(stepPin,LOW);
//        digitalWrite(dirPin,LOW);
//      }
//      else
//      {
//        myStepper.step(1);
//      }
//        
//    }
//    else
//      continue;
//  }
//}
//
//void anticlock()
//{
//  for(int x = 0; x < 200; x++) 
//  {
//    if (radio.available())
//    {
//      int text = 0;
//      radio.read(&text, sizeof(text));
//      Serial.println(text);
//      if(text==1111)
//      {
//        digitalWrite(stepPin,LOW);
//        digitalWrite(dirPin,LOW);
//      }
//      else
//      {
//        myStepper.step(-1);
//      }
//        
//    }
//    else
//      continue;
//  }
//}                 
