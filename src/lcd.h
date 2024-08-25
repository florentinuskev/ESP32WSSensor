#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>
#include <sensor.h>

void initLCD();
void loopLCD();
void showReading(float temp, float hum);

#endif