/*
 * Developed by: Leon Patrick Mawlong
 * Designation: Student (3rd Year Computer and Science Engineering)
 * Institute: National Institute of Technology Meghalaya
 * 
 * #include<SoftwareSerial.h>
 * The Arduino hardware has built-in support for serial communication
 * via a piece of hardware (built into the chip) called a UART - Universal Asynchronous Receiver-Transmitter.
 * 
 * The SoftwareSerial library has been developed to allow serial communication on other digital pins of the Arduino
 * using software to replicate the functionality.
 * 
 * We designate two pins to Receive (Rx) and Transmit (Tx) data over the serial connection.
 * It is possible to have multiple software serial ports with speeds up to 115200 bps.
 * 
 * links: https://www.arduino.cc/en/Reference/SoftwareSerial
 * 
*/
#include<SoftwareSerial.h>

SoftwareSerial communicationObject(6,7); //Rx, Tx

int sensorPin = A0;
int value = 0;

void setup() {

  //setting the baud rate to communicate between UART devices
  communicationObject.begin(9600);
  
  pinMode(sensorPin, INPUT);
  
  Serial.begin(9600);  
}

void loop() {

  //temperature in celsius = ((5.0 * analogRead(TemperaturePin)) / 1024) * 100.0
  
  value = analogRead(sensorPin)*0.48828125;

  if(value > 20) //take threshold as 20 Degrees
  {
    //Prints data to the transmit pin of the software serial port as raw bytes
    communicationObject.write(value);
  } 
   
  Serial.print("Temperature in Leon's Room = ");
  Serial.print(value);
  Serial.print(" degrees Celcius");
  Serial.println(" ");
  delay(1000);

}
