#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  // put your setup code here, to run once:
lcd.init();
lcd.begin(16,2);
lcd.backlight();
lcd.print("Hello World");
lcd.setCursor(0,1);
lcd.print("Hahaha");
}

void loop() {
  // put your main code here, to run repeatedly:

}
