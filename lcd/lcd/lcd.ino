#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>


#include <Adafruit_ST7735.h>
#include <SPI.h>

int CLK = 13;
int DIN = 11;
int CS = 10;
int DC = 9;
int RST = 8;

int W = 16;
int H = 2;

Adafruit_ST7735 tft = Adafruit_ST7735(CS, DC, DIN, CLK, RST);

void setup() {
  Serial.begin(9600);
  Serial.println("Hello! ST7735 TFT Test");
  tft.initR(INITR_GREENTAB);
  //tft.initB();

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLUE);
  time = millis() - time;


  Serial.println(time, DEC);
  delay(500);

  tft.println("Hello World!");
  

}

void loop() {
  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
}
