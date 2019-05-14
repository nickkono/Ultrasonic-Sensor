#include <Adafruit_FONA.h>

#include <Wire.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup(){
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16,2);
}

int readingInCms = 0;
float readingInInches = 0;
float readingIn10th = 0;
float readingInFeet = 0;
int address = 112;
int getDistance(int address){
  Wire.beginTransmission(address);
  Wire.write(byte(0x00));
  Wire.write(byte(0x51));
  Wire.endTransmission();
  delay(70);
  Wire.beginTransmission(address);
  Wire.write(byte(0x02));
  Wire.endTransmission();

  Wire.requestFrom(112,2);
  if(2<= Wire.available()){
    readingInCms = Wire.read();
    readingInCms = readingInCms << 0;
    readingInCms |= Wire.read();
    return readingInCms;
  }
}
void loop(){
    lcd.clear();
    readingInCms = getDistance(address);
    Serial.print ("Object detected at ");
    Serial.print (readingInFeet);
    readingInInches = readingInCms *.393701;
    readingIn10th = readingInInches * .0833;
    readingInFeet = readingInInches /12;
    Serial.println (" Feet");
    lcd.print("Distance is: ");
    lcd.setCursor(0,2);
    lcd.print (readingInFeet);
    lcd.print (" Feet");
    
    delay (5000);
  }



