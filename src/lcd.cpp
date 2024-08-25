#include <lcd.h>

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void initLCD()
{
    lcd.init();
    lcd.backlight();
}

void loopLCD()
{
    lcd.setCursor(0, 0);
    lcd.print("Hello, World!");
    delay(2000);
    lcd.clear();

    lcd.setCursor(0, 1);
    lcd.print("Hello, World!");
    delay(2000);
    lcd.clear();
}

void showReading(float temp, float hum)
{
    Serial.printf("Temperature: %.2f, Humidity: %.2f\n", temp, hum);
    lcd.setCursor(0, 0);
    lcd.print("Temp&Hum Sensor");
    lcd.setCursor(0, 1);
    lcd.printf("T:%.2f||H:%.2f%", temp, hum);
}