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
    Serial.print(dx);
    Serial.print("\t");
    Serial.println(dy);
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

  if(joy) pIn = map(analogRead(jY),4,997,3,-3);
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