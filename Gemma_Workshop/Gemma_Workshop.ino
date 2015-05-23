// MAKERTJEJ.se
// Workshop 1: Gemma + NeopPixel Ring
//
// Low power program for GEMMA with a NeoPixel ring. 
// A nice blinky display that can be personalized by 
// choosing different colors, speeds & patterns.

#include <Adafruit_NeoPixel.h>

#define PIN 0 // assign constant PIN to the pin D0~ on the Gemma

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, PIN);


//**********************************************************************************************
// MODIFIABLE PARAMETERS -- PERSONALIZE YOUR GEMMA NEOPIXELS HERE
//**********************************************************************************************
//
// CHOOSE BLINKING PATTERN
// 
// 0: RANDOM BLINKING
// 1: COLOR FLUSH
// 2: SPINNING

uint8_t  myPattern = 0; // ← Change this value to your desired pattern

// CHOOSE COLOR PALETTE HERE
// 
// 0: REDS-ORANGE
// 1: BLUE-LILAC
// 2: GREEN-YELLOW
// 3: PINK-PURPLE
// 4: TURQUOISE
// 5: RAINBOW

uint8_t myColorChart = 5; // ← Change this value to your desired color palette

// CHOOSE A SPEED SETTING HERE
//
// 0: FAST
// 1: MEDIUM
// 2: SLOW 

uint8_t mySpeed = 0; // ← Change this value to your desired speed

//**********************************************************************************************
// YOU’RE DONE!! YOU CAN LOOK AT THE REST OF THE CODE LATER
//**********************************************************************************************

// UTILITY VARIABLES
uint32_t prevTime; // Utility variable for timing
uint32_t delayTime; // Utility variable for timing
uint32_t color = 0xffffff; //default white
uint8_t offset = 0; // Current position of moving pattern
uint8_t c_offset = 0; // Current position within colour chart

// Colors, hexadecimal code:
uint32_t myColors[][6] = {{0xff0000, 0xff3300, 0xff6600, 0xffcc00, 0xffff00}, // reds-orange
{0x0000ff, 0x3300ff, 0x6600ff, 0x9900ff, 0xcc00ff, 0xff00ff}, // blue-lilac
{0x00ff00, 0x66ff00, 0xccff00, 0xffff00, 0xffee00, 0xffdd00}, // green-yellow
{0x9900ff, 0xcc00ff, 0xff00ff, 0xff00cc, 0xff0099, 0xff0066}, // pink-purple
{0x0066ff, 0x0099ff, 0x00ccff, 0x00ffff, 0x00ffcc, 0x00ff99}, // turqoise
{0x9900ff, 0x0033ff, 0x00ff33, 0xffff00, 0xff9900, 0xff0000} // rainbow(ish)
};


void setup() { // setup() runs once
  pixels.begin();
  pixels.setBrightness(60); // 1/3 brightness to save battery
  prevTime = millis();

    switch (mySpeed) { // where the speed timings are set
      case 0: // speed 0
          delayTime = 50;
      break;

      case 1: // speed 1
          delayTime = 150;
      break;

      default: // speed 2 (or any integer other than 0 or 1)
          delayTime = 300;
      break;
  }
}

void loop() { // after setup() runs, loop() will run over and over as long as the GEMMA has power
  uint8_t  i, j;
  uint32_t t;

  switch(myPattern) {

    case 0: // Random sparks - just one-three LED(s) on at a time!
    
  	i = random(16);
  	for(uint8_t i=0; i<4; i++) {
      	  color = myColors[myColorChart][random(6)];
      	  j = random(16);
      	  pixels.setPixelColor(j, color);
  	}
  	pixels.show();
  	delay(delayTime+50);
  	for(uint16_t i=0; i<16; i++) {
    	  pixels.setPixelColor(i, 0);
  	}
  	break;
 
    case 1: // Flushes the ring with one color at a time

  	for(uint16_t i=0; i<16; i++) {
  	  color = myColors[myColorChart][c_offset];
    	  pixels.setPixelColor(i, color);
      	  pixels.show();
      	  delay(delayTime);
  	}
    
  	c_offset++;
  	if (c_offset>=6) {
    	  c_offset=0;
  	}
  	for (uint16_t i=0; i<116; i++) {
    	  pixels.setPixelColor(i, 0);
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
