//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
const byte address[6] = "00001";//address through which two modules communicate.

int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor /// =9999

const int text = 1234;
const int msg1 = 1111;
void setup()
{
  radio.begin();
  radio.openWritingPipe(address);//set the address
  radio.stopListening();//Set module as transmitter
  Serial.begin(9600);
}
void loop()
{
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  if(sensorValue<100)
  {
    radio.write(&msg1, sizeof(msg1));
  }
  else
  {
    radio.write(&text, sizeof(text));
  }  
}
