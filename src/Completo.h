/*
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define ADC_VREF_mV    3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       39 // ESP32 pin GIOP36 (ADC0) connected to LM35

LiquidCrystal_I2C lcd_i2c(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup() {
  Serial.begin(9600);

  lcd_i2c.init(); // initialize the lcd
  lcd_i2c.backlight();

  lcd_i2c.setCursor(0, 0);      // move cursor to   (0, 0)
  lcd_i2c.print("Hola Mundo");       // print message at (0, 0)
  lcd_i2c.setCursor(0, 1);      // move cursor to   (0, 1)
  lcd_i2c.print("Proyecto"); // print message at (0, 1)
}

void loop() {
  // read the ADC value from the temperature sensor
  int adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in °C
  float tempC = milliVolt / 10;
  // convert the °C to °F
  float tempF = tempC * 9 / 5 + 32;

  // print the temperature in the Serial Monitor:
  Serial.print("Temperatura: ");
  Serial.print(tempC);   // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  "); // separator between °C and °F
  Serial.print(tempF);   // print the temperature in °F
  Serial.println("°F");

  lcd_i2c.clear();
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print("Temperatura:");
  lcd_i2c.setCursor(5,1);
  lcd_i2c.print(tempC);
  delay(1500);
  
}
*/