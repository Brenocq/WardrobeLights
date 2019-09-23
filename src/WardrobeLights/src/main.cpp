#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN_UP        5
#define LED_PIN_MIDDLE    4
#define LED_PIN_DOWN      3
#define NUM_LEDS    60
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void FillLEDsFromPaletteColors( uint8_t colorIndex);
void SetupWhiteStripedPalette();
void SetupBlackStripedPalette();

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN_UP, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    FastLED.addLeds<LED_TYPE, LED_PIN_MIDDLE, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    FastLED.addLeds<LED_TYPE, LED_PIN_DOWN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    //currentPalette = RainbowColors_p;
    SetupWhiteStripedPalette();
    //currentBlending = LINEARBLEND;
    currentBlending = NOBLEND; 
}


void loop()
{
    if(digitalRead(2)==HIGH){
      SetupBlackStripedPalette();
    }else{
      SetupWhiteStripedPalette();
    }
    
  
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void SetupWhiteStripedPalette()
{
    fill_solid( currentPalette, 16, CRGB::White);
    /*for(int i=0;i<16;i++){
      currentPalette[i] = CRGB::White;
    } */ 
}


void SetupBlackStripedPalette()
{
    fill_solid( currentPalette, 16, CRGB::Black);
}