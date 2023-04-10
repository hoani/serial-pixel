
#include "pixels.h"
#include "comms.h"

#define PIXEL_PIN 5

void setup()
{
  Pixels pixels(PIXEL_PIN);

  Serial.begin(115200);

  Comms c(&pixels);
  while (true)
  {
    delay(10);
    c.update();
  }
}

void loop()
{
  delay(100);
}
