#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define reset_button 12
#define initializing_button 13
#define set_zero_button 14
#define potpin 34


LiquidCrystal_I2C Lcd(0x27,16,2);

int current_value;
int current_initial_value;
double weight;
int initial_value;
int value_per_unit;
float average_current_value;
int check_value;
double previous_weight;

void set_initial_value();
void reset_programm();
void set_value_zero();

void setup() {
  Serial.begin(115200);
  pinMode(potpin,INPUT);

  Lcd.begin();
  Lcd.setCursor(0,0);
  Lcd.print("Powered By Techno Beasts");
  delay(2000);
  Lcd.clear();

  current_value = 0;
  current_initial_value = 0;
  value_per_unit = 190;
  previous_weight = 0;
  
  set_initial_value();

  attachInterrupt(reset_button,reset_programme,RISING);
  attachInterrupt(set_zero_button,set_value_zero,RISING);
  attachInterrupt(initializing_button,set_initial_value,RISING);

}

void loop() {
  for (int i = 0;i < 10000;i++){
    current_value += analogRead(potpin);
    }
  average_current_value = current_value/10000;
  current_value = 0;
  check_value = average_current_value - initial_value;

  if ( check_value <= 10 || check_value >= -10){
    weight = 0;
    }
  else{
    weight = (average_current_value-initial_value)*1000/value_per_unit;
    if (weight - previous_weight <= 0.05 || weight - previous_weight <= -0.05 ){
      weight = previous_weight;
      }
    }

  
  Serial.print("Weight: ");
  Lcd.clear();
  Serial.println(weight);
  Lcd.print(weight);
  delay(500);

  previous_weight = weight;
  
}

void set_initial_value(){
  Lcd.print("Initializing...");
  delay(1000);
  for (int i = 0;i < 10000;i++){
    current_initial_value += analogRead(potpin);
    }
  initial_value = current_initial_value/10000;
  current_initial_value = 0;
  Lcd.clear();
  Lcd.print(0);
  delay(100);
  
  }

void reset_programme(){

  Lcd.clear();
  Lcd.print("Resetting...");
  for (int i = 0;i < 10000;i++){
    current_value += analogRead(potpin);
    }
    
  average_current_value = current_value/10000;
  current_value = 0;
  check_value = average_current_value - initial_value;
  weight = (average_current_value-initial_value)*1000/value_per_unit;
  
  Lcd.clear();
  Lcd.print(weight);
  delay(500);
  previous_weight = weight;
  }

void set_value_zero(){
  Lcd.print("Setting Zero...");
  delay(1000);
  for (int i = 0;i < 10000;i++){
    current_initial_value += analogRead(potpin);
    }
  initial_value = current_initial_value/10000;
  current_initial_value = 0;
  Lcd.clear();
  Lcd.print(0);
  delay(100);
  }
