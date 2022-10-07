#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014


#define DATA_PIN_TOP 3//Top of wheel
#define DATA_PIN_BOTTOM 4//Bottom of wheel
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 61

CRGB leds[NUM_LEDS];
CRGB ledsTop[NUM_LEDS];
CRGB ledsBottom[NUM_LEDS];

#define BRIGHTNESS 250
#define FRAMES_PER_SECOND 120

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN_TOP,COLOR_ORDER>(ledsTop, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,DATA_PIN_BOTTOM,COLOR_ORDER>(ledsBottom, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(9600);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
//void loop()
//{
//  // Call the current pattern function once, updating the 'leds' array
//  gPatterns[gCurrentPatternNumber]();
//
//  // send the 'leds' array out to the actual LED strip
//  FastLED.show();  
//  // insert a delay to keep the framerate modest
//  FastLED.delay(1000/FRAMES_PER_SECOND); 
//
//  // do some periodic updates
//  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
//  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
//}

void loop()
{
//  blinkLeft();
//  blinkRight();
//  blinkTop();
  blinkBottom();
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void blinkLeft() {
  blinkSectionAll(50, NUM_LEDS, CRGB::Red, 300);
}

void blinkRight() {
  blinkSectionAll(0, 11, CRGB::Red, 300);
}

void blinkTop() {
  blinkSectionTop(13, 48, CRGB::Red, 300);
}

void blinkBottom() {
  for(int i = 300; i > 0; i-=10) {
    blinkSectionBottom(11, 47, CRGB::Red, i); 
  }
  solidSectionBottom(11, 47, CRGB::Red); 
  delay(5000);
}

void rainbowLeft() {
  rainbowMinusSection(NUM_LEDS - 1, 49, CRGB::Red, 100);
}

void blinkSectionAll(int startIndex, int stopIndex, CRGB::HTMLColorCode color, int blinkDelay) {
  for(int dot = startIndex; dot < stopIndex; dot++) { 
    ledsTop[dot] = color;
    ledsBottom[dot] = color;
  }
  FastLED.show();
  delay(blinkDelay);
  for(int dot = startIndex; dot < stopIndex; dot++) {
    ledsTop[dot] = CRGB::Black;
    ledsBottom[dot] = CRGB::Black;
  }
  FastLED.show();
  delay(blinkDelay);
}

void blinkSectionTop(int startIndex, int stopIndex, CRGB::HTMLColorCode color, int blinkDelay) {
  for(int dot = startIndex; dot < stopIndex; dot++) { 
    ledsTop[dot] = color;
  }
  FastLED.show();
  delay(blinkDelay);
  for(int dot = startIndex; dot < stopIndex; dot++) {
    ledsTop[dot] = CRGB::Black;
  }
  FastLED.show();
  delay(blinkDelay);
}

void blinkSectionBottom(int startIndex, int stopIndex, CRGB::HTMLColorCode color, int blinkDelay) {
  for(int dot = startIndex; dot < stopIndex; dot++) { 
    ledsBottom[dot] = color;
  }
  FastLED.show();
  delay(blinkDelay);
  for(int dot = startIndex; dot < stopIndex; dot++) {
    ledsBottom[dot] = CRGB::Black;
  }
  FastLED.show();
  delay(blinkDelay);
}

void solidSectionBottom(int startIndex, int stopIndex, CRGB::HTMLColorCode color) {
  for(int dot = startIndex; dot < stopIndex; dot++) { 
    ledsBottom[dot] = color;
  }
  FastLED.show();
}

//void blinkSectionNew(int startIndex, int stopIndex, CRGB::HTMLColorCode color, int blinkDelay, const CRGB firstLed, ...) {
//  va_list restOfLeds;
//  CRGB nextLed = firstLed;
//  va_start(restOfLeds, firstLed);
//  for(int dot = startIndex; dot < stopIndex; dot++) { 
//    Serial.print("dot = ");
//    Serial.println(dot);
//    while(nextLed) {
//      Serial.print("nextLed = ");
//      Serial.println(nextLed);
//      nextLed[dot] = color;
//      Serial.println("color");
//      nextLed = va_arg(restOfLeds, CRGB);
//      Serial.println("nextLed");
//    }
//  }
//  Serial.println("done");
//  FastLED.show();
//  delay(blinkDelay);
//  nextLed = firstLed;
//  va_start(restOfLeds, firstLed);
//  for(int dot = startIndex; dot < stopIndex; dot++) { 
//    while(nextLed) {
//      Serial.println("black");
//      nextLed[dot] = CRGB::Black;
//      nextLed = va_arg(restOfLeds, CRGB);
//    }
//  }
//  va_end(restOfLeds);
//  FastLED.show();
//  delay(blinkDelay);
//}

//void blinkSectionNew(int startIndex, int stopIndex, CRGB::HTMLColorCode color, int blinkDelay, CRGB ledInput[], int ledsSize) {
//  for(int dot = startIndex; dot < stopIndex; dot++) { 
//    Serial.print("dot = ");
//    Serial.println(dot);
//    for(int i = 0; i < ledsSize; i++) { 
//      Serial.print("i = ");
//      Serial.println(i);
//      CRGB led = ledInput[i];
//      Serial.print("led size: ");
//      Serial.println(sizeof(led));
//      led[dot] = color;
//      Serial.print("ledInput size: ");
//      Serial.println(sizeof(ledInput));
//    }
//  }
//  Serial.println("done");
//  FastLED.show();
//  delay(blinkDelay);
//  for(int dot = startIndex; dot < stopIndex; dot++) { 
//    for(int i = 0; i < ledsSize; i++) { 
//      CRGB led = leds[i];
//      led[dot] = CRGB::Black;
//    }
//  }
//  FastLED.show();
//  delay(blinkDelay);
//}

void rainbowMinusSection(int startIndex, int stopIndex, CRGB::HTMLColorCode color, int blinkDelay) {
  for(int dot = startIndex; dot >= stopIndex; dot--) { 
    ledsTop[dot] = color;
    ledsBottom[dot] = color;
    FastLED.show();
    delay(blinkDelay);
  }
  for(int dot = startIndex; dot >= stopIndex; dot--) { 
    ledsTop[dot] = CRGB::Black;
    ledsBottom[dot] = CRGB::Black;
  }
  FastLED.show();
  delay(blinkDelay);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
