/*
LCD documentation: https://wiki.52pi.com/index.php?title=Z-0234
Arduino C library: https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

 // Since the display I have uses the PCF8574T chip
 
LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Tyler's the Best!");
}

void loop() {
  delay(500);
  lcd.noDisplay();
  delay(500);
  lcd.display();

}
