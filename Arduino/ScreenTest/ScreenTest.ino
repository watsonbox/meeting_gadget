#include <Wire.h>
#include "SSD1306.h" 
 
SSD1306  display(0x3c, 26, 27);
 
void setup() {
  display.init();
  display.flipScreenVertically();
  display.drawString(0, 0, "Hello World");
  display.display();
}
 
void loop() {}
