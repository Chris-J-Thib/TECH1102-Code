#include <DHT.h>
#include <LiquidCrystal.h>

using namespace std;


int
  R = 2,
  B = 3,
  DT = 6,
  RS = 8,
  EN = 9,
  D4 = 10,
  D5 = 11,
  D6 = 12,
  D7 = 13;

float temp, hum;

DHT sens(DT,DHT11);
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  pinMode(DT,INPUT);
  pinMode(R,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(RS,OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);

  Serial.begin(9600);
  lcd.begin(16,2);
  sens.begin();
}

void loop() {
  delay(2000);
  temp = sens.readTemperature();
  hum = sens.readHumidity();
  delay(1000);

  Serial.print("Temp: ");
  Serial.println(temp);
  Serial.print("Hum.: ");
  Serial.println(hum);

  if(isnan(temp)||isnan(hum)){
    Serial.println("Failed to read, trying again...");
    return;
  }

  if(temp > 23){
    digitalWrite(R,HIGH);
  } else {
    digitalWrite(R,LOW);
  }
  if(hum >= 28){
    digitalWrite(B,HIGH);
  } else {
    digitalWrite(B,LOW);
  }


  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(7,0);
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("Hum.: ");
  lcd.setCursor(7,1);
  lcd.print(hum);


}
