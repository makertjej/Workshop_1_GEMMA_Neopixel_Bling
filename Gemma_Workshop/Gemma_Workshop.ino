// FULL THING
// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

#include <Adafruit_NeoPixel.h>

#define PIN 0 // assign constant PIN to the pin D0~ on the Gemma

// User-defined parameters
#define myPattern 0
#define myColorChart 3
#define mySpeed 2


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, PIN);


// MODIFYING VARIABLES
//
// BLINKING PATTERNS
// CHOOSE BLINKING PATTERN HERE: 0-3 - default blinking pattern is random
//

// uint8_t myPattern = 0; // Current animation effect

// COLOR CHOICES
// CHOOSE COLOR PALETTE HERE: 0-5 - default color chart is rainbow
// 0: REDS-ORANGE; 1: BLUE-LILAC; 2: GREEN-YELLOW; 3: PINK-PURPLE; 4: TURQOISE; 5: RAINBOW

// uint8_t myColorChart = 3;

// TIMING CHOICES
// CHOOSE A SPEED SETTING HERE
// 0: SLOW; 1: MEDIUM; 2: FAST -- DEFAULT SETTING IS FAST

// uint8_t mySpeed = 2;

// UTILITY VARIABLES
uint32_t prevTime; // Utility variable for timing
uint32_t delayTime; // Utility variable for timing
uint32_t color = 0xffffff; //default white
uint8_t offset = 0; // Current position of moving pattern
uint8_t c_offset = 0; // Current position within colour chart

uint32_t myColors[][6] = {{0xff0000, 0xff3300, 0xff6600, 0xffcc00, 0xffff00}, // reds-orange
{0x0000ff, 0x3300ff, 0x6600ff, 0x9900ff, 0xcc00ff, 0xff00ff}, // blue-lilac
{0x00ff00, 0x66ff00, 0xccff00, 0xffff00, 0xffee00, 0xffdd00}, // green-yellow
{0x9900ff, 0xcc00ff, 0xff00ff, 0xff00cc, 0xff0099, 0xff0066}, // pink-purple
{0x0066ff, 0x0099ff, 0x00ccff, 0x00ffff, 0x00ffcc, 0x00ff99}, // turqoise
{0x9900ff, 0x0033ff, 0x00ff33, 0xffff00, 0xff9900, 0xff0000} // rainbow(ish)
};


void setup() {
  pixels.begin();
  pixels.setBrightness(60); // 1/3 brightness to save battery
  prevTime = millis();

    switch (mySpeed) {
      case 0:
          delayTime = 500;
      break;

      case 1:
          delayTime = 300;
      break;

      default:
          delayTime = 100;
      break;
  }
}

void loop() {
  uint8_t  i;
  uint32_t t;


  switch(myPattern) {

    case 0: // Random sparks - just one LED on at a time!
      i = random(16);
      color = myColors[myColorChart][random(6)];
      pixels.setPixelColor(i, color);
      pixels.show();
      delay(delayTime);
      pixels.setPixelColor(i, 0);
      break;
 
    case 1: // Flushes the ring with one color at a time

      for(uint16_t i=0; i<16; i++) {
        color = 0;
        if(i>=offset) color=myColors[myColorChart][c_offset];
    
        pixels.setPixelColor(i, color);
        pixels.show();
        delay(delayTime);

      }
    
      offset++;
      if (offset>=16) {
        offset=0;
        c_offset++;
        if (c_offset>5) c_offset=0;
        for (uint16_t i=0; i<16; i++) {
          pixels.setPixelColor(i, 0);
        }
      }
      break;

    case 2: // Spinny wheels (8 LEDs on at a time)
       for(i=0; i<16; i++) {
         uint32_t c = 0;
         if(((offset + i) & 7) < 2) c = myColors[myColorChart][random(6)]; // 4 pixels on...
           pixels.setPixelColor(i, c); // First eye
         }
         pixels.show();
         offset++;
         delay(delayTime);
         break;
  }

}
