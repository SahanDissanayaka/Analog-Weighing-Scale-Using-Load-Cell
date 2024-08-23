#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define potpin1 34
#define potpin2 35

LiquidCrystal_I2C Lcd(0x27,16,2);

int current_value;
int current_value1;
int current_value2;
//float weight;
//int initial_value = 940;
//int value_per_unit= 540 ;

void setup() {
  Serial.begin(115200);
  pinMode(potpin1,INPUT);
  pinMode(potpin2,INPUT);

  Lcd.begin();
  Lcd.setCursor(0,0);

  //initial_value = analogRead(potpin);
//  Lcd.print(" Analog Project ");
//  Lcd.setCursor(0,1);

}

void loop() {
  current_value1 = analogRead(potpin1);
  current_value2 = analogRead(potpin2);
//  weight = (current_value-initial_value)/value_per_unit;
//  Serial.print("Weight: ");
  Lcd.clear();
  //Serial.println(weight);
//  Lcd.print(weight);
  current_value = current_value1 - current_value2;
  
  Lcd.print(current_value);
  delay(500);
  
}
