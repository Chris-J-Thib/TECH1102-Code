int
  R = 2,
  G = 3,
  B = 4,
  del = 5,
  brightness = 0;

int LEDs[] = {R, G, B};

bool up = true;

void fadeFor();
void fadeWhileTime(int);
void loop3For();
void loop3While();


void setup()
{
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop()
{
fadeFor();
delay(1000);
fadeWhileTime(30); //arg is total time in secs
delay(1000);
loop3For();
delay(1000);
loop3While();
delay(1000);
}

void fadeFor(){
  // up-down fade with for loop
  brightness = 0;
  up = true;
  for (; brightness >= 0; brightness++)
  {
    if(up){
    analogWrite(R, brightness);
    delay(del);
    }
    if(brightness == 255){
      up = false;
    }
    if(!up){
      brightness--;
      brightness--;
      if(brightness < 0) break;
    analogWrite(R, brightness);
    delay(del);
    }
  }
}

void fadeWhileTime(int sec){
  // up-down for sec(total) with while loop
  int delExact = (sec*1000)/(255+255);
  brightness = 0;
  up = true;
  while (true)
  {
    if(up){
    analogWrite(B, brightness);
    delay(delExact);
    brightness++;
    }
    if(brightness == 255){
      up = false;
    }
    if(!up){
    analogWrite(B, brightness);
    delay(delExact);
    brightness--;
    }
    if(brightness < 0)break;
  }
}

void loop3For(){
  //3 LEDs one-by-one with for loop
  for(int LED : LEDs){
    digitalWrite(LED,HIGH);
    delay(del*100);
    digitalWrite(LED,LOW);
    delay(del*50);
  }
}

void loop3While(){
  //3 LEDs one-by-one with while loop
  int ind = 0;
  while(ind < sizeof(LEDs) / sizeof(int)){
    digitalWrite(LEDs[((ind - 2)*-1%3)],HIGH);
    delay(del*100);
    digitalWrite(LEDs[((ind - 2)*-1%3)],LOW);
    delay(del*50);
    ind++;
  }
}
