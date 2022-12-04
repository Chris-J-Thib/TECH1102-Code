using namespace std;
String input;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  Serial.println("red, green or blue?");
}

void loop() {
  while (Serial.available() == 0);
  input = Serial.readStringUntil("\n");
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
  digitalWrite(8, LOW);
  if(input == "red"){
    digitalWrite(12, HIGH);
  }
  if(input == "green"){
    digitalWrite(10, HIGH);
  }
  if(input == "blue"){
    digitalWrite(8, HIGH);
  }
}