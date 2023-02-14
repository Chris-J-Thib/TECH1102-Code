#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

const int 
  jX = A8,
  jY = A9,
  A = 28,
  B = 26,
  X = 22,
  Y = 24,
  Mtr = 45,
  Swch = 44,
  Red = 13,
  Green = 12,
  Blue = 11,
  BZ = 7,
  CLK = 6,
  DIN = 5,
  CS = 4,
  DC = 3, 
  RST = 2,
  W = 160,
  H = 128,
  dif = 3,  
  BND = 4,
  BGC = 0x0000,
  FGC = 0xFFFF,
  MPU=0x68; 
  
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int pIn = 0;
const int RGB[] = {Red,Green,Blue};

bool joy = true;

Adafruit_ST7735 tft = Adafruit_ST7735(CS, DC, DIN, CLK, RST);

struct Paddle {
  const int
    w = 4,
    h = H/4;
  int
    pd,
    x,
    y = H/4+H/8;

  draw(int p){
    pd = p;
    if(p == 1) x = 16;
    else x = W-16-w;
    tft.fillRect(x, y , w, h, BGC);
    y = H/4+H/8;
    move(0);
  }
  
  move(int d, int c = FGC){
    tft.fillRect(x, y , w, h, BGC);
    y += d;
    tft.fillRect(x, y , w, h, c);
  }

  end(bool win){
    int c;
    draw(pd);
    if(win) {
      c = 0x07E0;
      Serial.print(pd);
      Serial.println(" win\n");      
    }
    else c = 0x001F;

    for(int i = 0; i < 3; i++){
      move(0,c);
      delay(250);
      move(0,FGC);
      delay(250);
    }
  }
};

struct Ball {
  const int
    r = 3;
  int tn = 1;
  float  
    x = W/2,
    y = H/2,
    dx,
    dy;
  draw(){
    tft.fillCircle(x, y, r, BGC);
    x = W/2;
    y = H/2;
    tft.fillCircle(x, y, r, FGC);
    randomizeHeading();
  } 
  move(){
    tft.fillCircle(x, y, r, BGC);
    y += dy;
    x += dx;
    tft.fillCircle(x, y, r, FGC);
  }
  randomizeHeading(){
    dx = random(-2, 2) * dif;
    dy = random(-2, 2) * dif;
    if(dx == 0)dx=dif;    
  }
  bounce(bool h, bool v, float ax = 1, float ay = 1){
    if(h) dx*=(-1*ax);
    if(v) dy*=(-1*ay);
    tone(BZ, 1000*tn);
    delay(25);
    noTone(BZ);
    // Serial.print(dx);
    // Serial.print("\t");
    // Serial.println(dy);
  }
};

void pong(){
  Paddle p1, p2;
  Ball b;
  tft.fillScreen(BGC);
  tft.drawFastHLine(BND, BND, W-BND*2, FGC);
  tft.drawFastVLine(BND, BND, H-BND*2, FGC);
  tft.drawFastHLine(W-BND, H-BND, BND*2-W, FGC);
  tft.drawFastVLine(W-BND, H-BND, BND*2-H, FGC);
  p1.draw(1);
  p2.draw(2);
  b.draw();

  while(true){
  if(b.x == BND + b.r + 1 ){
    b.bounce(true, false);
    b.draw();
    p2.end(true);
    p1.end(false);
  }
  if(b.x == W-BND - (b.r+1)){
    b.bounce(true, false);
    b.draw();
    p1.end(true);
    p2.end(false);
    
  }

  if(joy) pIn = map(analogRead(jX),4,997,-3,3);
  else pIn = map(gyro(),-56,54,3,-3);



  
  if(p1.y > BND + dif && pIn < 0 ) p1.move(pIn);
  if(p1.y + p1.h < (H - BND) - dif && pIn > 0) p1.move(pIn);
  
  


  //move down
  if(p2.y + p2.h/2 < b.y){
    if(p2.y + p2.h < (H - BND) - dif) p2.move(dif);
    
  //move up
  } else if(p2.y + p2.h/2 > b.y) {
    if(p2.y > BND + dif) p2.move(-dif);
  } else {
    p2.move(0);
  }
  

  //collision detection
  if(b.x + b.r + dif == p2.x){
    if (b.y < p2.y + p2.h + b.r && b.y > p2.y - b.r) {
      b.bounce(true, false);
    }


  } else if(b.x - b.r - dif == p1.x+ p1.w){
    if (b.y < p1.y + p1.h + b.r && b.y > p1.y - b.r) {
      b.bounce(true, false);
    }

  }
  if(b.y - b.r - dif - 1 < BND || b.y + b.r + dif + 1 > H-BND){
    b.bounce(false, true);
  }

  b.move();  
  }

}

int16_t gyro(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read(); 
  return AcX/300; 
}

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  randomSeed(millis());
  Serial.begin(57600);
  tft.initR(INITR_GREENTAB);
  tft.fillScreen(BGC);
  tft.setRotation(1);
  pinMode(jX,INPUT);
  pinMode(jY,INPUT);
  pinMode(A,INPUT);
  pinMode(B,INPUT);
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  pinMode(Mtr,OUTPUT);
  pinMode(Swch,OUTPUT);
  pinMode(Red,OUTPUT);
  pinMode(Green,OUTPUT);
  pinMode(Blue,OUTPUT);
  pinMode(BZ,OUTPUT);
  
  Serial.println("Initialized");
}

void debug(){
  delay(500);
  //joystick
  Serial.print("X = ");
  Serial.print(analogRead(jX));
  Serial.print("\t Y = ");
  Serial.println(analogRead(jY));
  
  //buttons
  Serial.print("A = ");
  Serial.print(digitalRead(A));
  digitalWrite(A, LOW);
  Serial.print("\t");
  Serial.print("B = ");
  Serial.print(digitalRead(B));
  digitalWrite(B, LOW);
  Serial.print("\t");
  Serial.print("X = ");
  Serial.print(digitalRead(X));
  digitalWrite(X, LOW);
  Serial.print("\t");
  Serial.print("Y = ");
  Serial.println(digitalRead(Y));
  digitalWrite(Y, LOW);
}

void clear(){
  tft.fillScreen(BGC);
  tft.setCursor(0,0);
}

int getResp(){
  int resp;
  while((!digitalRead(A) && !digitalRead(B)&&(!digitalRead(X) && !digitalRead(Y)))) debug();
  if(digitalRead(A)) resp = 1;
  if(digitalRead(B)) resp = 2; 
  if(digitalRead(X)) resp = 3;
  if(digitalRead(Y)) resp = 4;
  while((digitalRead(A) != 0 || digitalRead(B)) != 0 || (digitalRead(X) != 0 || digitalRead(Y)!= 0)) debug(); 
  return resp;
}

void loop() {
  clear();
  tft.println("SD games(A)");
  tft.println("or onboard game?(B)");
  while(!digitalRead(A) && !digitalRead(B));
  if(digitalRead(A)) SD();
  if(digitalRead(B)) onBoard();
  // debug();
}


void SD(){
 loop();
}

void onBoard(){
  clear();
  int ctrl;
  int game;
  tft.println("Game Select:");
  tft.println("(A) Pong");
  tft.println("(B) Pong");
  tft.println("(X) Pong");
  tft.println("(Y) Pong");

  game = getResp();

  tft.println("Control Select:");
  tft.println("(A) JoyStick");
  tft.println("(B) Gyro");
  
  ctrl = getResp();

  switch(ctrl){
    case 1:
      joy = true;
      break;
    case 2:
      joy = false;
      break;
    //default:
    //onBoard();
  }
  

  switch(game) {
  case 1:
    pong();
    break;
  default:
    pong();
}
  


}





 