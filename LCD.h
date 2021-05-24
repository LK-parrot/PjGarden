#ifndef LCD_H
#define LCD_H
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void printLcd(String text, byte line, byte column) {
  lcd.clear();
  lcd.setCursor(column, line);
  lcd.print(text);
}

#endif
