#include <Wire.h> //I2C
#include <U8g2lib.h>
#include "logo.h"
//I2C SSD1306 128x32 (search U8g2 examples for other display)
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
void setup() {
 u8g2.begin(); //Start Screen
 drawLogo();
}
void loop() {
}
void drawLogo() {
 u8g2.firstPage();
 do {
   u8g2.drawXBMP(0, 0, logo_width, logo_height, logo); 
 } while ( u8g2.nextPage() );

}