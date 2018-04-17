/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 52
 * LCD Enable pin to digital pin 53
 * LCD D4 pin to digital pin 51
 * LCD D5 pin to digital pin 49
 * LCD D6 pin to digital pin 47
 * LCD D7 pin to digital pin 45
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:

#include <LiquidCrystal.h>
#include "dht.h"
#define dht_apin A1 // Analog Pin sensor is connected to
 
dht DHT;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 22, en = 23, d4 = 24, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(22,23,24, 25, 26, 27);
int h=11 ; 
int m= 53; 
int s = 30; 
int flag; 
int TIME; 
int min_temp;
int max_temp; 
void setup() {

   Serial.begin(9600);
    pinMode(40, INPUT_PULLUP);
  //pinMode(13, OUTPUT);
   delay(500);
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);
 
   lcd.display();
 lcd.begin(20, 2);
 lcd.print("hello");     
  
  
  delay(10000);
   lcd.clear();
   DHT.read11(dht_apin);
  max_temp = DHT.temperature;
  min_temp = DHT.temperature;
 
}

void loop() {
   int sensorVal = digitalRead(40);
  DHT.read11(dht_apin);
  int humd = DHT.humidity;
  int temp =  DHT.temperature;
    s=s+1;
    if(temp > max_temp) {
      max_temp = temp;
    }

    if(temp < min_temp) {
      min_temp = temp;
    }
   if(s==60){ 
      s=0; 
       m=m+1; 
    } 
      
    if(m==60) {  
        m=0; 
        h=h+1;  
      } 
    if(h==13) { 
      h=1; 
     } 

   
      if (sensorVal == HIGH) {
    print_time();
      }
      else
      {
         print_temp_humd(temp,humd);
        
        }
           
}

void print_time()
{
  lcd.clear();
  lcd.setCursor(0,0);

 lcd.print("TIME:");
 lcd.print(h);
 lcd.print(":");
 lcd.print(m);
 lcd.setCursor(0,1);
 lcd.print("Max = " + String(max_temp) + "c ");
 lcd.print("Min = " + String(min_temp) + "c ");
 
 
 delay(2000);
  }
  void print_temp_humd(int temp,int humd)
  {
    lcd.setCursor(0,0);
    lcd.print("humidity = "  + String(humd) + "%");
    lcd.setCursor(0, 1);
    lcd.print("Temperature = " + String(temp) + "c ");
     Serial.print(DHT.temperature); 
     delay(1000); 
    }
