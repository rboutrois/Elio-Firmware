#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#include "Pins.h"
#include "MotorDriver.h"

// Motors declaration
MotorDriver motorA = MotorDriver(1, pinINA1, pinINA2);
MotorDriver motorB = MotorDriver(2, pinINB1, pinINB2);

// WS2812B declaration
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, ledPin, NEO_GRB + NEO_KHZ800);

// Filtre anti-rebond (debouncer)
#define DEBOUNCE_TIME 250
volatile uint32_t DebounceTimer = 0;
int buttonState = 0;

// Interrupt du bouton placée dans la RAM
void IRAM_ATTR buttonpressed();

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  // LED init
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); //LED eteinte
  pixels.show();

  // Bouton init
  pinMode(buttonPin, INPUT);
  attachInterrupt(buttonPin, buttonpressed, FALLING);
}

void loop()
{

  switch (buttonState)
  {
  case 0:
    pixels.setPixelColor(0, pixels.Color(100, 0, 0));

    motorA.stop();
    motorB.stop();

    break;

  case 1:
    pixels.setPixelColor(0, pixels.Color(0, 100, 0));

    motorA.forward();
    motorB.forward();

    break;

  case 2:
    pixels.setPixelColor(0, pixels.Color(0, 0, 100));

    motorA.backward();
    motorB.backward();

    break;

  default:
    buttonState = 0;
    break;
  }

  pixels.show();

  delay(10);
}

void IRAM_ATTR buttonpressed()
{
  if (millis() - DEBOUNCE_TIME >= DebounceTimer)
  {
    DebounceTimer = millis();
    buttonState += 1;
    Serial.println(buttonState);
  }
}