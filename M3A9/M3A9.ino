#include <LiquidCrystal.h>

using namespace std;

long
  dur,
  cm;
int 
  BN = A0,
  EC = 6,
  TR = 7,
  RS = 8,
  EN = 9,
  D4 = 10,
  D5 = 11,
  D6 = 12,
  D7 = 13;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


void setup() {
  pinMode(BN,INPUT);
  pinMode(EC,INPUT);
  pinMode(TR,OUTPUT);
  pinMode(RS,OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  Serial.begin(9600);
}

int scan(){
  digitalWrite(TR,LOW);
  delayMicroseconds(5);
  digitalWrite(TR,HIGH);
  delayMicroseconds(10);
  digitalWrite(TR,LOW);
  dur = pulseIn(EC,HIGH);
  return (dur/2)/29.1;
}

void loop() {
  delay(200);
  digitalWrite(BN,HIGH);
  // Serial.println(digitalRead(BN));

  if(!digitalRead(BN)){
    lcd.clear();
    lcd.print(scan());
    lcd.print("cm");

  }


}
