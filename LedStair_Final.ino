#include <Adafruit_DotStar.h>
#include <SPI.h> 
//#include <avr/power.h>

#define NUMPIXELS 150

#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

int trig = 3;
int echo = 2;
int a=0;

int red = 0;
int green = 0;
int blue = 0;

void setup() {
red = 255;
  green = 255;
  blue = 255;

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); 
#endif
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  strip.begin(); 
  strip.show();  
}

int      head  = 0, tail = -10;
uint32_t color = 0xFF0000;

int count = 0;

  int distance2;
  
void loop() {
  long duration, distance;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);          
  digitalWrite(trig, HIGH);   
  delayMicroseconds(10);       
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 17 / 1000;

  Serial.println(distance);
  
  if(distance<80){
   //for(int i=1;i<=NUMPIXELS;i++){
   // randcolor();
   //   strip.setPixelColor(i,strip.Color(red,green,blue));
   //  strip.show();
   //   delay(80);
   //}
   //rainbow(20);
    rainbowCycle(20);
  }
  else{
    if(distance2<80){
     for(int i=NUMPIXELS;i>=1;i--){
       strip.setPixelColor(i,0);
       strip.show();
       delay(10);
     }
    }
  }
  
  distance2 = distance;
}

void randcolor()
{
  red = random(256);
  green = random(256);
  blue = random(256);
}


uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*3; j++) { 
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
