// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!


// 5M STRIP


#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 30 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

int trig = 3;
int echo = 2;

unsigned long time1 = 0;

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

bool a=0;

int      head  = 0, tail = -30; // Index of first 'on' and 'off' pixels
int head2 = -40, tail2 = -70;
int head3 = -80, tail3 = -110;

uint32_t color = 100000;      // 'On' color (starts red)



void loop() {
  
  int ran = random(100000,500000);

  unsigned long time2 = millis();
  
  long duration, distance;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);          
  digitalWrite(trig, HIGH);   
  delayMicroseconds(10);       
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 17 / 1000;
  
  Serial.println(distance);
  
    if(distance <=30){
      while(time2 - time1 <= 5000){
       strip.setPixelColor(head,color);
       strip.setPixelColor(head2,color);
       strip.setPixelColor(head3,color);
       strip.setPixelColor(tail,0);
       strip.setPixelColor(tail2,0);
       strip.setPixelColor(tail3,0);
       strip.show();
       time1 = time2;
      }
    }
  
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

/*  
  //사람이 들어왔을 때
  if(distance <= 30){
      a = 1;
  } 

  if(a == 1){
      strip.setPixelColor(head,color);
      strip.setPixelColor(head2,color);
      strip.setPixelColor(head3,color);
      strip.setPixelColor(tail,0);
      strip.setPixelColor(tail2,0);
      strip.setPixelColor(tail3,0);
      strip.show();
  }
  */
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





