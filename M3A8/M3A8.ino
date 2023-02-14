#include <Servo.h>

Servo servo;

int
  in = A0,
  out = 7;

void setup() {
  pinMode(in,INPUT);
  servo.attach(out);
}

void loop() {
  servo.write(map(analogRead(in),0,1023,0,180));
}
