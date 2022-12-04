#include <LiquidCrystal.h>

using namespace std;


int 
  RS = 8,
  EN = 9,
  D4 = 10,
  D5 = 11,
  D6 = 12,
  D7 = 13;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  pinMode(RS,OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
}

void loop() {

  lcd.begin(0,0);
  lcd.print("Hello!");


}
