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
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
int buttonState = 0;
int x = 0;
#define CLK A1
#define DT A2
#define SW A3
boolean Button_Stage = false;
int counter = 0;
int counter_menu = 1;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
boolean f1 = false;
boolean f2 = false;
unsigned long lastButtonPress = 0;
#define buz 2

//MENU LABLE       ^0        ^1             ^2          ^3        ^4         ^5         ^6          ^7
char *arr[8] = { "MENU", "SETTING", "MANULE CONTROL", "AUTONOMOUS", "ALARM", "PAYLOAD", "SYSTEM", "INTERFACE" };
void drawLogo() {
  u8g2.firstPage();
  do {
    u8g2.drawXBMP(0, 0, logo_width, logo_height, logo);
  } while (u8g2.nextPage());
}
void home() {
}
void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  Serial.begin(9600);
  // Reads the initial state of the outputA

  tone(buz, 5);
  delay(200);
  tone(buz, 15);
  delay(200);
  tone(buz, 30);
  delay(200);
  noTone(buz);
  u8g2.begin();  //Start Screen
  drawLogo();
  delay(2000);
  u8g2.clearDisplay();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
  u8g2.setCursor(0, 14);
  u8g2.drawStr(10, 29, ">");
  u8g2.drawLine(0, 17, 128, 17);
  u8g2.drawStr(50, 15, arr[0]);
  u8g2.drawStr(20, 29, arr[1]);
  u8g2.drawStr(20, 39, arr[2]);
  u8g2.drawStr(20, 49, arr[3]);
  u8g2.drawStr(20, 59, arr[4]);
  u8g2.sendBuffer();
}


void DrawgaugeDisc(byte x = 62, byte y = 64, byte r = 20, byte p = 10, int v = 90, int minVal = 0, int maxVal = 200, float gs_rad = 135, float ge_rad = 0) {
  int n = (r / 100.00) * p;  // calculate needle percent lenght
  for (int a = minVal; a <= v; a++) {
    float i = ((a - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
    int xp = x + (sin(i) * n);
    int yp = y - (cos(i) * n);
    u8g2.drawLine(x, y, xp, yp);
  }
}
void beep() {  //LOWTONEBEEP
  tone(buz, 5);
  delay(200);
  noTone(buz);
}
void check_home1() {

  if ((digitalRead(SW) == LOW) && (counter_menu == 1)) {
    delay(100);
    if ((digitalRead(SW) == HIGH) && (counter_menu == 1)) {
      f1 = true;
      while (f1 == true) {

        int pgb = map(x, 0, 200, 0, 70);
        u8g2.clearBuffer();
        u8g2.drawStr(0, 60, "ABORT");
        u8g2.drawBox(40, 55, pgb, 1);  // ゲージを表示
        u8g2.drawBox(40, 60, pgb, 3);  // ゲージを表示
        u8g2.drawStr(0, 15, arr[1]);   // a, r - średnica, p - długość
        u8g2.sendBuffer();
        if ((digitalRead(SW) == LOW) && (counter_menu == 1)) {
          x += 10;

          Serial.println(x);
        }
        if ((digitalRead(SW) == HIGH) && (x <= 200)) {

          x = 0;
        }
        if ((digitalRead(SW) == HIGH) && (x > 200)) {
          f1 = false;
          x = 0;

          u8g2.clearBuffer();
          u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
          u8g2.setCursor(0, 14);
          u8g2.drawStr(50, 15, arr[0]);
          u8g2.drawLine(0, 17, 128, 17);
          u8g2.drawStr(20, 29, arr[1]);
          u8g2.drawStr(10, 29, ">");
          u8g2.drawStr(20, 39, arr[2]);
          u8g2.drawStr(20, 49, arr[3]);
          u8g2.drawStr(20, 59, arr[4]);
          u8g2.sendBuffer();
          beep();
        }
      }
    }
  }

  if ((digitalRead(SW) == LOW) && (counter_menu == 2)) {
    delay(100);
    if ((digitalRead(SW) == HIGH) && (counter_menu == 2)) {
      f1 = true;
      while (f1 == true) {

        int pgb = map(x, 0, 200, 0, 70);
        u8g2.clearBuffer();
        u8g2.drawStr(0, 60, "ABORT");
        u8g2.drawBox(40, 60, pgb, 3);  // ゲージを表示
        u8g2.drawStr(0, 15, arr[2]);   // a, r - średnica, p - długość
        u8g2.sendBuffer();
        if ((digitalRead(SW) == LOW) && (counter_menu == 2)) {
          x += 10;

          Serial.println(x);
        }
        if ((digitalRead(SW) == HIGH) && (x <= 200)) {

          x = 0;
        }
        if ((digitalRead(SW) == HIGH) && (x > 200)) {
          f1 = false;
          x = 0;

          u8g2.clearBuffer();
          u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
          u8g2.setCursor(0, 14);
          u8g2.drawStr(50, 15, arr[0]);
          u8g2.drawLine(0, 17, 128, 17);
          u8g2.drawStr(20, 29, arr[2]);
          u8g2.drawStr(10, 39, ">");
          u8g2.drawStr(20, 39, arr[3]);
          u8g2.drawStr(20, 49, arr[4]);
          u8g2.drawStr(20, 59, arr[5]);
          u8g2.sendBuffer();
          beep();
        }
      }
    }
  }


  if ((digitalRead(SW) == LOW) && (counter_menu == 3)) {
    delay(100);
    if ((digitalRead(SW) == HIGH) && (counter_menu == 3)) {
      f1 = true;
      while (f1 == true) {

        int pgb = map(x, 0, 200, 0, 70);
        u8g2.clearBuffer();
        u8g2.drawStr(0, 60, "ABORT");
        u8g2.drawBox(40, 60, pgb, 3);  // ゲージを表示
        u8g2.drawStr(0, 15, arr[3]);   // a, r - średnica, p - długość
        u8g2.sendBuffer();
        if ((digitalRead(SW) == LOW) && (counter_menu == 3)) {
          x += 10;

          Serial.println(x);
        }
        if ((digitalRead(SW) == HIGH) && (x <= 200)) {

          x = 0;
        }
        if ((digitalRead(SW) == HIGH) && (x > 200)) {
          f1 = false;
          x = 0;

          u8g2.clearBuffer();
          u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
          u8g2.setCursor(0, 14);
          u8g2.drawStr(50, 15, arr[0]);
          u8g2.drawLine(0, 17, 128, 17);
          u8g2.drawStr(20, 29, arr[1]);
          u8g2.drawStr(10, 49, ">");
          u8g2.drawStr(20, 39, arr[2]);
          u8g2.drawStr(20, 49, arr[3]);
          u8g2.drawStr(20, 59, arr[4]);
          u8g2.sendBuffer();
          beep();
        }
      }
    }
  }


  if ((digitalRead(SW) == LOW) && (counter_menu == 4)) {
    delay(100);
    if ((digitalRead(SW) == HIGH) && (counter_menu == 4)) {
      f1 = true;
      while (f1 == true) {

        int pgb = map(x, 0, 200, 0, 70);
        u8g2.clearBuffer();
        u8g2.drawStr(0, 60, "ABORT");
        u8g2.drawBox(40, 60, pgb, 3);  // ゲージを表示
        u8g2.drawStr(0, 15, arr[4]);   // a, r - średnica, p - długość
        u8g2.sendBuffer();
        if ((digitalRead(SW) == LOW) && (counter_menu == 4)) {
          x += 10;

          Serial.println(x);
        }
        if ((digitalRead(SW) == HIGH) && (x <= 200)) {

          x = 0;
        }
        if ((digitalRead(SW) == HIGH) && (x > 200)) {
          f1 = false;
          x = 0;

          u8g2.clearBuffer();
          u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
          u8g2.setCursor(0, 14);
          u8g2.drawStr(50, 15, arr[0]);
          u8g2.drawLine(0, 17, 128, 17);
          u8g2.drawStr(20, 29, arr[1]);
          u8g2.drawStr(10, 59, ">");
          u8g2.drawStr(20, 39, arr[2]);
          u8g2.drawStr(20, 49, arr[3]);
          u8g2.drawStr(20, 59, arr[4]);
          u8g2.sendBuffer();
          beep();
        }
      }
    }
  }



  if ((digitalRead(SW) == LOW) && (counter_menu == 5)) {
    delay(100);
    if ((digitalRead(SW) == HIGH) && (counter_menu == 5)) {
      f1 = true;
      while (f1 == true) {

        int pgb = map(x, 0, 200, 0, 70);
        u8g2.clearBuffer();
        u8g2.drawStr(0, 60, "ABORT");
        u8g2.drawBox(40, 60, pgb, 3);  // ゲージを表示
        u8g2.drawStr(0, 15, arr[5]);   // a, r - średnica, p - długość
        u8g2.sendBuffer();
        if ((digitalRead(SW) == LOW) && (counter_menu == 5)) {
          x += 10;

          Serial.println(x);
        }
        if ((digitalRead(SW) == HIGH) && (x <= 200)) {

          x = 0;
        }
        if ((digitalRead(SW) == HIGH) && (x > 200)) {
          f1 = false;
          x = 0;


          u8g2.clearBuffer();
          u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
          u8g2.setCursor(0, 4);
          u8g2.drawStr(50, 5, arr[0]);
          u8g2.drawLine(0, 7, 128, 7);
          u8g2.drawStr(10, 59, ">");
          u8g2.drawStr(20, 19, arr[1]);
          u8g2.drawStr(20, 29, arr[2]);
          u8g2.drawStr(20, 39, arr[3]);
          u8g2.drawStr(20, 49, arr[4]);
          u8g2.drawStr(20, 59, arr[5]);
          u8g2.sendBuffer();
          beep();
        }
      }
    }
  }



  if ((digitalRead(SW) == LOW) && (counter_menu == 6)) {
    delay(100);
    if ((digitalRead(SW) == HIGH) && (counter_menu == 6)) {
      f1 = true;
      while (f1 == true) {

        int pgb = map(x, 0, 200, 0, 70);
        u8g2.clearBuffer();
        u8g2.drawStr(0, 60, "ABORT");
        u8g2.drawBox(40, 60, pgb, 3);  // ゲージを表示
        u8g2.drawStr(0, 15, arr[6]);   // a, r - średnica, p - długość
        u8g2.sendBuffer();
        if ((digitalRead(SW) == LOW) && (counter_menu == 6)) {
          x += 10;

          Serial.println(x);
        }
        if ((digitalRead(SW) == HIGH) && (x <= 200)) {

          x = 0;
        }
        if ((digitalRead(SW) == HIGH) && (x > 200)) {
          f1 = false;
          x = 0;

          u8g2.clearBuffer();
          u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
          u8g2.drawStr(10, 59, ">");
          u8g2.drawStr(20, 9, arr[1]);
          u8g2.drawStr(20, 19, arr[2]);
          u8g2.drawStr(20, 29, arr[3]);
          u8g2.drawStr(20, 39, arr[4]);
          u8g2.drawStr(20, 49, arr[5]);
          u8g2.drawStr(20, 59, arr[6]);
          u8g2.sendBuffer();
          beep();
        }
      }
    }
  }



  if ((digitalRead(SW) == LOW) && (counter_menu == 7)) {
    delay(100);
    if ((digitalRead(SW) == HIGH) && (counter_menu == 7)) {
      f1 = true;
      while (f1 == true) {

        int pgb = map(x, 0, 200, 0, 70);
        u8g2.clearBuffer();
        u8g2.drawStr(0, 60, "ABORT");
        u8g2.drawBox(40, 60, pgb, 3);  // ゲージを表示
        u8g2.drawStr(0, 15, arr[7]);   // a, r - średnica, p - długość
        u8g2.sendBuffer();
        if ((digitalRead(SW) == LOW) && (counter_menu == 7)) {
          x += 10;

          Serial.println(x);
        }
        if ((digitalRead(SW) == HIGH) && (x <= 200)) {

          x = 0;
        }
        if ((digitalRead(SW) == HIGH) && (x > 200)) {
          f1 = false;
          x = 0;

          u8g2.clearBuffer();
          u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
          u8g2.drawStr(10, 59, ">");
          u8g2.drawStr(20, 9, arr[2]);
          u8g2.drawStr(20, 19, arr[3]);
          u8g2.drawStr(20, 29, arr[4]);
          u8g2.drawStr(20, 39, arr[5]);
          u8g2.drawStr(20, 49, arr[6]);
          u8g2.drawStr(20, 59, arr[7]);
          u8g2.sendBuffer();
          beep();
        }
      }
    }
  }
}
void menu_part1() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
  u8g2.setCursor(0, 14);
  u8g2.drawStr(50, 15, "MENU");
  u8g2.drawLine(0, 17, 128, 17);
  u8g2.drawStr(20, 29, "SETTING");
  u8g2.drawStr(10, 29, ">");
  u8g2.drawStr(20, 39, "MANULE CONTROL");
  u8g2.drawStr(20, 49, "AUTONOMOUS");
  u8g2.drawStr(20, 59, "ALARM");
  u8g2.sendBuffer();
}
void menu_part2() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
  u8g2.drawStr(10, 9, ">");
  u8g2.drawStr(20, 9, "MANULE CONTROL");
  u8g2.drawStr(20, 19, "AUTONOMOUS");
  u8g2.drawStr(20, 29, "ALARM");
  u8g2.drawStr(20, 39, "PAYLOAD");
  u8g2.drawStr(20, 49, "SYSTEM");
  u8g2.drawStr(20, 59, "INTERFACE");
  u8g2.sendBuffer();
}
void home1() {
  buttonState = digitalRead(SW);
  switch (counter_menu) {
    case 1:


      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
      u8g2.setCursor(0, 14);
      u8g2.drawStr(50, 15, "MENU");
      u8g2.drawLine(0, 17, 128, 17);
      u8g2.drawStr(20, 29, "SETTING");
      u8g2.drawStr(10, 29, ">");
      u8g2.drawStr(20, 39, "MANULE CONTROL");
      u8g2.drawStr(20, 49, "AUTONOMOUS");
      u8g2.drawStr(20, 59, "ALARM");
      u8g2.sendBuffer();




      break;

    case 2:


      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
      u8g2.setCursor(0, 14);
      u8g2.drawStr(50, 15, "MENU");
      u8g2.drawLine(0, 17, 128, 17);
      u8g2.drawStr(10, 39, ">");
      u8g2.drawStr(20, 29, "SETTING");
      u8g2.drawStr(20, 39, "MANULE CONTROL");
      u8g2.drawStr(20, 49, "AUTONOMOUS");
      u8g2.drawStr(20, 59, "ALARM");
      u8g2.sendBuffer();
      break;


    case 3:


      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
      u8g2.setCursor(0, 14);
      u8g2.drawStr(50, 15, "MENU");
      u8g2.drawLine(0, 17, 128, 17);
      u8g2.drawStr(10, 49, ">");
      u8g2.drawStr(20, 29, "SETTING");
      u8g2.drawStr(20, 39, "MANULE CONTROL");
      u8g2.drawStr(20, 49, "AUTONOMOUS");
      u8g2.drawStr(20, 59, "ALARM");
      u8g2.sendBuffer();
      break;


    case 4:


      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
      u8g2.setCursor(0, 14);
      u8g2.drawStr(50, 15, "MENU");
      u8g2.drawLine(0, 17, 128, 17);
      u8g2.drawStr(10, 59, ">");
      u8g2.drawStr(20, 29, "SETTING");
      u8g2.drawStr(20, 39, "MANULE CONTROL");
      u8g2.drawStr(20, 49, "AUTONOMOUS");
      u8g2.drawStr(20, 59, "ALARM");
      u8g2.sendBuffer();
      break;


    case 5:


      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
      u8g2.setCursor(0, 4);
      u8g2.drawStr(50, 5, "MENU");
      u8g2.drawLine(0, 7, 128, 7);
      u8g2.drawStr(10, 59, ">");
      u8g2.drawStr(20, 19, "SETTING");
      u8g2.drawStr(20, 29, "MANULE CONTROL");
      u8g2.drawStr(20, 39, "AUTONOMOUS");
      u8g2.drawStr(20, 49, "ALARM");
      u8g2.drawStr(20, 59, "PAYLOAD");
      u8g2.sendBuffer();
      break;

    case 6:


      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font

      u8g2.drawStr(10, 59, ">");
      u8g2.drawStr(20, 9, "SETTING");
      u8g2.drawStr(20, 19, "MANULE CONTROL");
      u8g2.drawStr(20, 29, "AUTONOMOUS");
      u8g2.drawStr(20, 39, "ALARM");
      u8g2.drawStr(20, 49, "PAYLOAD");
      u8g2.drawStr(20, 59, "SYSTEM");
      u8g2.sendBuffer();
      break;

    case 7:


      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
      u8g2.drawStr(10, 59, ">");
      u8g2.drawStr(20, 9, "MANULE CONTROL");
      u8g2.drawStr(20, 19, "AUTONOMOUS");
      u8g2.drawStr(20, 29, "ALARM");
      u8g2.drawStr(20, 39, "PAYLOAD");
      u8g2.drawStr(20, 49, "SYSTEM");
      u8g2.drawStr(20, 59, "INTERFACE");
      u8g2.sendBuffer();
      break;
  }
}

void loop() {
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  //If we detect LOW signal, button is press
  check_home1();
  int btnState = digitalRead(SW);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter--;
      counter_menu--;
      currentDir = "CCW";

    } else {
      // Encoder is rotating CW so increment
      counter++;
      counter_menu++;
      currentDir = "CW";
    }
    /*
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
    Serial.print("Position: ");
    Serial.println(counter);
    u8g2.clearBuffer();
    u8g2.drawStr(0, 40, "Position");  // write something to the internal memory
    u8g2.setCursor(0, 60);
    u8g2.print(currentDir);              // write something to the internal memory
    u8g2.setFont(u8g2_font_helvR08_tr);  // choose a suitable font
    u8g2.drawStr(0, 15, "COUNTER");      // write something to the internal memory
    u8g2.setCursor(0, 30);
    u8g2.print(counter);  // write something to the internal memory
    u8g2.sendBuffer();
    */
    home1();
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Put in a slight delay to help debounce the reading



  // Read the button state


  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");
    }

    // Remember last button press event
    lastButtonPress = millis();
  }

  // Put in a slight delay to help debounce the reading
  delay(1);
  if (counter_menu > 7) {
    counter_menu = 7;
  }
  if (counter_menu < 1) {
    counter_menu = 1;
  }
}