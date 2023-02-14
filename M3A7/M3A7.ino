#include <Servo.h>
#include <LiquidCrystal.h>

using namespace std;


int
  S = 7,
  RS = 8,
  EN = 9,
  D4 = 10,
  D5 = 11,
  D6 = 12,
  D7 = 13;

Servo servo;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  pinMode(RS,OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  Serial.begin(9600);
  servo.attach(S);
  lcd.begin(0,0);
}

void loop() {
  
  for(int a = 0; a <= 180; a+= 15){
    servo.write(a);
    lcd.clear();
    lcd.print(a);
    delay(250);
  }
  for(int a = 180; a >= 0; a-= 15){
    servo.write(a);
    lcd.clear();
    lcd.print(a);
    delay(250);
  }



}
