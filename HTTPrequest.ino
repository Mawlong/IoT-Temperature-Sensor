/*
 * Developed by: Leon Patrick Mawlong
 * Designation: Student (3rd Year Computer and Science Engineering)
 * Institute: National Institute of Technology Meghalaya
 * 
 * #include <ESP8266HTTPClient.h>
 * This library provides functionality to use Hyper Text Transfer Protocal with the ESP8266.
 * 
 * #include <ESP8266WiFi.h>
 * This library provides ESP8266 specific Wi-Fi routines to connect to network.
 * link: https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
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
 * link: https://www.arduino.cc/en/Reference/SoftwareSerial
 *
 * link: https://github.com/esp8266/Arduino.git
 * 
 * To enabe notifications via EMAIL.
 * We implement it using IFTTT via webhooks (HTTP GET)
 * What is a webhook? (https://zapier.com/blog/what-are-webhooks/)
 * 
 * links: https://ifttt.com/discover
 *        https://ifttt.com/services/maker_webhooks
 * 
 */
 

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>

SoftwareSerial s(0,1); //Rx, Tx

int value = 0;

void setup() {

  //setting the baud rate to communicate between UART devices
  s.begin(9600);

  Serial.begin(19200);

  //WiFi.begin("network-name", "password");
  
  WiFi.begin("Sohjew", "***LEKA@68970468");

  Serial.print("Connecting");

  //to try and connect every 0.5 ms 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();

  Serial.print("Connected, IP address: ");
  
  //WiFi.localIP provides the IP Address assigned by DHCP
  Serial.println(WiFi.localIP());

}

void loop() {

  if(WiFi.status() == WL_CONNECTED)
  {
    // declaring our HTTP object as http.
    HTTPClient http;

    // we pass the URL to the object to which we want to make a HTTP request
    http.begin("http://maker.ifttt.com/trigger/temperature/with/key/dAwXVs5GUmWyK7__zEch2d");

    // check if the stream is available across the serial connection    
    if(s.available()> 0)
    {
      //read the value on the stream
      value = s.read();
      Serial.print("Sensed value: ");
      Serial.println(value);
      if(value > 20)
      {
        // used to get the HTTP response code that is returned by the function GET();
        // make an HTTP GET request to the URL specified in the <object>.begin() function
        int responseCode = http.GET();

        //we display the response code to help identify any potential problems
        Serial.print("HTTP Response Code: ");
        Serial.println(responseCode);
        delay(1000);          
      }      
    }
  }
  else
  {
    Serial.println("Error in Connection");
  }

}
