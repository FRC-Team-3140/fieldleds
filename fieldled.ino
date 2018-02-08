#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN A1

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(15, PIN, NEO_GRB + NEO_KHZ800);
bool queued[3] = { false, false, false };
bool stripOn = true;
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

    // rainbowCycle(10);
    setCubeCount(0,0);
    setCubeCount(1,0);
    setCubeCount(2,0);
    delay(1000);
    setCubeCount(0,1);
    setCubeCount(1,1);
    setCubeCount(2,1);
    delay(1000);
    setCubeCount(0,2);
    setCubeCount(1,2);
    setCubeCount(2,2);
    delay(1000);
    setCubeCount(0,3);
    setCubeCount(1,3);
    setCubeCount(2,3);
    delay(1000);
    activatePowerUp(0);
    // queued[0]=true;
    queued[1]=true;
    toggleColors();
    delay(200);
    toggleColors();
    delay(200);
    toggleColors();
    delay(200);
    toggleColors();
    delay(200);
    toggleColors();
    delay(200);
    toggleColors();
    delay(200);
    toggleColors();
   
    
    // rainbowCycle(10);
//   // Some example procedures showing how to display to the pixels:
//   colorWipe(strip.Color(255, 0, 0), 50); // Red
//   colorWipe(strip.Color(0, 255, 0), 50); // Green
//   colorWipe(strip.Color(0, 0, 255), 50); // Blue
// //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
//   // Send a theater pixel chase in...
//   theaterChase(strip.Color(127, 127, 127), 50); // White
//   theaterChase(strip.Color(127, 0, 0), 50); // Red
//   theaterChase(strip.Color(0, 0, 127), 50); // Blue

//   rainbow(20);
//   rainbowCycle(20);
//   theaterChaseRainbow(50);
}

void setCubeCount(uint8_t powerUpIndex, uint8_t numberOfCubes) {
  for (int i=powerUpIndex*5; i<(powerUpIndex+1)*5; i++)
  {
    if (i>powerUpIndex*5+(3-numberOfCubes) and i<(powerUpIndex+1)*5-1) {
      strip.setPixelColor(i,strip.Color(227,210,0));
    }
    else
      strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
}

void activatePowerUp(uint8_t powerUpIndex) {
  for (int i=powerUpIndex*5; i<(powerUpIndex+1)*5; i++)
  {
    strip.setPixelColor(i,strip.Color(255,0,0));
  }
  strip.show();
}

void deactivatePowerUp(uint8_t powerUpIndex) {
  for (int i=powerUpIndex*5; i<(powerUpIndex+1)*5; i++)
  {
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
}

void toggleColors(){
  for (int powerUpIndex=0; powerUpIndex<3; powerUpIndex++)
  {
    if (queued[powerUpIndex]==true)
      for (int i=powerUpIndex*5; i<(powerUpIndex+1)*5; i++)
      {
        if (stripOn==true)
          strip.setPixelColor(i,strip.Color(255,0,0));
        else
          strip.setPixelColor(i,strip.Color(0,0,0));
      }
      strip.show();
  }
  stripOn=(!stripOn);
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
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

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
