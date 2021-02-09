#include <Pins.h>
#include <Arduino.h>
#include <Battery.h>

float batteryRaw = 0;
float batteryValue = 0;

void BatteryRead()
{
    // Mesure de la tension de battery
    batteryRaw = analogRead(batteryPin);

    batteryValue = map(batteryRaw, 0, 4095, 0, 355);

    Serial.print("Battery : ");
    Serial.print(batteryValue/50);
    Serial.println("V");
}