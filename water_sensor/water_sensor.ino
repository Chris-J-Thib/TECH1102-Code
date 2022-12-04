#define fan 8
#define pmp 9
#define snr A0
#define pot A1 
#define cal 60

int val,dLvl;

void setup() {
  Serial.begin(9600);
  pinMode(fan, OUTPUT);
  pinMode(pmp, OUTPUT);
}

void loop() {

  val = analogRead(snr);
  dLvl = analogRead(pot)/cal;
  Serial.print("Water Level: ");
  Serial.print(val);
  Serial.print("mm \t Desired Level: ");
  Serial.print(dLvl);
  Serial.print("mm \t\t");

  if (val < dLvl - 5){
    digitalWrite(pmp,HIGH);
    digitalWrite(fan,LOW);
    Serial.println("Low  Level, Pump On  Fan Off");

  } else if (val > dLvl + 5) {
    digitalWrite(fan,HIGH);
    digitalWrite(pmp,LOW);
    Serial.println("High Level, Pump Off Fan On");
    
  } else{
    digitalWrite(pmp,LOW);
    digitalWrite(fan,LOW);

    Serial.println("Good Level, Pump Off Fan Off");

  }

  delay(5000);
}
