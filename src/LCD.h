/*

include <util/delay.h>
include <avr/io.h>
include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_i2c(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup() {
  lcd_i2c.init(); // initialize the lcd
  //lcd_i2c.backlight();

  lcd_i2c.setCursor(0, 0);      // move cursor to   (0, 0)
  lcd_i2c.print("Hola Mundo");       // print message at (0, 0)
  lcd_i2c.setCursor(0, 1);      // move cursor to   (0, 1)
  lcd_i2c.print("Proyecto"); // print message at (0, 1)
}

void loop() {
}
*/