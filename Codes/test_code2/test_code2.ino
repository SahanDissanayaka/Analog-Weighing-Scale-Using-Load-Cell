#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define potpin1 34
#define potpin2 35

LiquidCrystal_I2C Lcd(0x27,16,2);
int value = 0;
int value1 = 0;
int value2 = 0;
float voltage;
float average_value;
float average_value1;
float average_value2;
int value_per_kilo = 270;
int initial_value = 869;
float weight = 0;

void setup() {
  Serial.begin(115200);
  pinMode(potpin1,INPUT);
  pinMode(potpin2,INPUT);

  Lcd.begin();
  Lcd.setCursor(0,0);
  Lcd.print("   Powered by   ");
  Lcd.setCursor(0,1);
  Lcd.print(" TECHNO BEASTS ");

}

void loop() {
  for (int i = 0;i < 10000;i++){
    value1 += analogRead(potpin1);
    value2 += analogRead(potpin2);
    }
  average_value1 = value1/10000;
  Lcd.clear();
  //Lcd.print(average_value1);
  average_value2 = value2/10000;
  //Lcd.print(average_value2);
  value2 = 0;
  value1 = 0;

  average_value = average_value1-average_value2;

  //voltage = average_value*3.3/4095;
  //Serial.print("Voltage: ");
  //Serial.println(average_value);
  Lcd.setCursor(0,1);
  //Lcd.print(average_value);
  Lcd.setCursor(0,1);
  weight = round((average_value-initial_value)/value_per_kilo);
  Lcd.print("Weight: ");
  Lcd.print(weight);
  Lcd.print(" Kg");
  //Lcd.print(voltage);
  //Lcd.print(voltage);
  delay(500);
  
}
