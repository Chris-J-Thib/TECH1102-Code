
using namespace std;

int
    G = 2,
    Y = 3,
    R = 4,
    del = 1,
    mul = 2;

void setup()
{
  pinMode(G, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(R, OUTPUT);
}

void loop()
{

  int LEDs[] = {G, Y, R};
  int brightness = 0;

  // up-down fade with for loop
  for (brightness = 0; brightness <= 255; brightness++)
  {
    analogWrite(R, brightness);
  }
  for (brightness = 255; brightness <= 255; brightness++)
  {
    analogWrite(R, brightness);
  }

  // up-down for 30s
  while ()
  {
  }

  for (int led : LEDs)
  {
    while (brightness <= 255)
    {
      analogWrite(led, brightness);
      delay(del);
      brightness += mul;
    }

    brightness = 255;
    while (brightness >= 0)
    {
      analogWrite(led, brightness);
      delay(del);
      brightness -= mul;
    }
    digitalWrite(led, LOW);
  }
}
