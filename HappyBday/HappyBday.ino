int pin = 5;
bool o = true;
bool c = false;

void setup() {
  pinMode(pin, OUTPUT);

}

void note(int, int, bool);

void loop() {

  delay(500);

  note(1,50, c);
  note(1,50, c);
  note(2,100, c);
  note(1,100, c);
  note(4,100, c);
  note(3,100, o);

  note(1,50, c);
  note(1,50, c);
  note(2,100, c);
  note(1,100, c);
  note(5,100, c);
  note(4,100, o);

  note(1,50, c);
  note(1,50, c);
  note(8,100,c);
  note(6,100,c);
  note(4,100,c);
  note(3,100,o);
  note(2,100,c);

  note(7,50,c);
  note(7,50,c);
  note(6, 100, c);
  note(4,100,c);
  note(5, 100,c);
  note(4,100,o);

  delay(1000);

}

void note(int note, int del, bool hold){
  analogWrite(pin, note*50);
  if (!hold){
    delay(100);
    analogWrite(pin, 0);
  }
  delay(del*5);
}