#include <LPD8806.h>
#include "SPI.h"

/*****************************************************************************/

// Number of RGB LEDs in stripe:
int nLEDs = 44;
int dataPin  = 11;
int clockPin = 13;

int roundPos = 0;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

void setup() {
  strip.begin();
  strip.show();
  allDark();
}

void loop() {
  headcolor(50);

  strip.show();
  delay(50);
}

void allDark()
{
  int i;
  for(i=0; i<strip.numPixels(); i++) 
    strip.setPixelColor(i, 0);
  for(i=0; i<strip.numPixels(); i++) 
    strip.setPixelColor(i, strip.Color(1,   0,   0));
  strip.show();
}


// running color on head
void headcolor(uint8_t wait) {

  double i,j;
  double hb = 10.0;
  double hg = 25.0;
  double v = -1 * nLEDs / 2.0;
  double z = -0.10;

  double maxlight = 20.0;
  double defaultlight = 7.0;

  for (i=0.0; i < strip.numPixels(); i++) {

    double red = defaultlight;
    double blue = (hb + ( v + i ) * ( v + i ) * z);
    double green = (hg + ( v + i ) * ( v + i ) * z);

    int k = roundPos;
    if (k > (strip.numPixels() - v) )
      k = k - strip.numPixels();

    double light = (hb + ( v + i + k) * ( v + i + k) * z);           

    if (red < 0)
      red = 0;
    if (red > defaultlight)
      red = defaultlight; 

    if (blue < 0)
      blue = 0;
    if (blue > defaultlight)
      blue = defaultlight; 

    if (green < 0)
      green = 0;
    if (green > defaultlight)
      green = defaultlight; 


    int maxDiff = 7;
    double diff = (roundPos - i); 


    if(i < strip.numPixels() - maxDiff )
      diff = (roundPos - i);

    if(roundPos > strip.numPixels() - maxDiff && i < maxDiff)
      diff = diff - strip.numPixels();
   
    if(i >= strip.numPixels() - maxDiff && roundPos >= 0 && roundPos < strip.numPixels() - maxDiff*2)
      diff = strip.numPixels() + roundPos - i ;

    diff = diff * diff;
    diff = sqrt(diff);

    double percent = (10.0 + 5.0 *(maxDiff - diff)) / 10.0;

    if(diff < maxDiff)
    {
      red = red * percent;
      blue = blue * percent;
      green = green * percent;
    }      

    // red blue green
    strip.setPixelColor(i, strip.Color(red,   blue,   green));
  }
 
  roundPos++;
  if(roundPos > strip.numPixels())
    roundPos = 0;
}


