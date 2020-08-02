// 5M STRIP

#include <Adafruit_DotStar.h>

#include <SPI.h>
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 150 // Number of LEDs in strip

#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

int trig = 3;
int echo = 2;

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); 
#endif
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  strip.begin(); 
  strip.show(); 
}

int head  = 0, tail = -30;
int head2 = -40, tail2 = -70;
int head3 = -80, tail3 = -110;

uint32_t color = 100000;    

void loop() {
  int a=3;
  int b;
  int ran = random(100000,500000);
  
  long duration, distance;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);          
  digitalWrite(trig, HIGH);   
  delayMicroseconds(10);       
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 17 / 1000;
  
  Serial.println(distance);
  
//넣지 말아 보자
/*
  //사람이 안들어왔을 때
  if(distance > 30){
      strip.setPixelColor(head,0);
      strip.setPixelColor(head2,0);
      strip.setPixelColor(head3,0);
      strip.setPixelColor(tail,0);
      strip.setPixelColor(tail2,0);
      strip.setPixelColor(tail3,0);
      strip.show();
      
  } 
*/
  //사람이 들어왔을 때
  if(distance <= 30){
      b = a;
      while(b>0){
        strip.setPixelColor(head,color);
        strip.setPixelColor(head2,color);
        strip.setPixelColor(head3,color);
        strip.setPixelColor(tail,0);
        strip.setPixelColor(tail2,0);
        strip.setPixelColor(tail3,0);
        strip.show();
        b--;
      }
  }
  
  delay(10);        
  
  if(++head >= NUMPIXELS) {
    head = 0;
    if(color<=15581378)
     color = color+=ran;
    else
     color = 100000;
  }
  if(++head2 >= NUMPIXELS){
    head2 = -30;
    if(color<=15581378)
     color = color+=ran;          
    else
     color = 100000;
  }
  if(++head3 >= NUMPIXELS){
    head3 = -60;
    if(color<=15581378)
     color = color+=ran;          
    else
     color = 100000;
  }
  if(++tail >= NUMPIXELS) 
    tail = 0;
   if(++tail2 >= NUMPIXELS) 
    tail2 = -30;
   if(++tail3 >= NUMPIXELS) 
    tail3 = -60;


}





