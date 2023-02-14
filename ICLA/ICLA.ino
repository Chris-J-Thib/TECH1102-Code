#include <Servo.h>
#include <LiquidCrystal.h>

using namespace std;

long dur;

int
  B = 2,
  R = 3,
  G = 4,  
  S = 5,
  EC = 6,
  TR = 7,
  RS = 8,
  EN = 9,
  D4 = 10,
  D5 = 11,
  D6 = 12,
  D7 = 13,
  OPEN = 90,
  CLOSED = 180;

Servo gate;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  pinMode(EC,INPUT);
  pinMode(TR,OUTPUT);
  pinMode(RS,OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  Serial.begin(9600);
  gate.attach(S);
  gate.write(CLOSED);
  lcd.begin(16,2);
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
int pos = CLOSED;
int dis = scan();
digitalWrite(B,HIGH);
lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("Hello!");


if (dis <= 5){
Serial.println(dis) ;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please Wait,");
  lcd.setCursor(0, 1);
  lcd.print("Opening Gate...");
  digitalWrite(B,LOW);
  digitalWrite(R,HIGH);
    delay(2000);
  while(pos > OPEN){
    // Serial.println(pos);
    gate.write(pos);
    pos--;
    delay(10);    
  }
  digitalWrite(R,LOW);
  digitalWrite(G,HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  lcd.print("Please Proceed.");
  while(dis <= 5){
    dis = scan();
    delay(2000);
  }
  digitalWrite(G,LOW);
  digitalWrite(R,HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please Wait,");
  lcd.setCursor(0, 1);
  lcd.print("Closing Gate...");
  delay(1000);
  while(pos <= CLOSED){
    gate.write(pos);
    pos++;
    delay(10);    
  }
  digitalWrite(R,LOW);
}

}
