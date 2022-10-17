#include <Wire.h>  //I2C
#include <U8g2lib.h>
#include "logo.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
//I2C SSD1306 128x32 (search U8g2 examples for other display)
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);




void drawLogo() {
  u8g2.firstPage();
  do {
    u8g2.drawXBMP(0, 0, logo_width, logo_height, logo);
  } while (u8g2.nextPage());
}
void setup() {
  u8g2.begin();  //Start Screen
  drawLogo();
}
void loop() {
}
