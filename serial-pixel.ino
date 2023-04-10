
#include "pixels.h"

#define PIXEL_PIN 5



void setup()
{
  Pixels pixels(PIXEL_PIN);
  pixels.setup(24);
  for (int i = 0; i < 24; i++)
  {
    pixels.setHSV(i, 10*i, 100, 100);
  }
  pixels.show();
 
}

void loop()
{
  delay(100);
}
