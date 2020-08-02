// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

//1M STRIP

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
int a=0;
int timer=0;

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

int      head  = 0, tail = -15; // Index of first 'on' and 'off' pixels

uint32_t color = 100000;      // 'On' color (starts red)

void loop() {
  int ran = random(100000,500000);
  
  long duration, distance;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);          
  digitalWrite(trig, HIGH);   
  delayMicroseconds(10);       
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 17 / 1000;

  //Serial.println(distance);
  a=1;

  if(a==0){
    if(distance <= 60){
     strip.setPixelColor(head, color); // 'On' pixel at head
     strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
     strip.show(); // Refresh strip
     a = 1;
    }
    else if(distance >60){
      strip.setPixelColor(head,0);
      strip.setPixelColor(tail,0);
      strip.show();
    }
  }
  if(a==1){
    if(distance>60){
     timer+=1;
     if(timer>=500){
      strip.setPixelColor(head,0);
      strip.setPixelColor(tail,0);
      strip.show();
      
     }
     else{
      strip.setPixelColor(head, color); // 'On' pixel at head
      strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
      strip.show(); // Refresh strip
     }
    }
    else if(distance <= 60){
     strip.setPixelColor(head, color); // 'On' pixel at head
     strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
     strip.show(); // Refresh strip
     a=0;
    }
  }
 Serial.println(a);
 Serial.println(timer);
  delay(10);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
   //  Next color (R->G->B) ... past blue now?
    if(color<=15581378)
     color = color+=ran;             //   Yes, reset to red
    else
     color = 100000;
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index
}
