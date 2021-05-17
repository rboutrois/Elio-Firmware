#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <SparkFun_ADS1015_Arduino_Library.h>

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

// Obstacle
int sensorValue[3];
int obstacleCount = 4;
ADS1015 obstacleSensor;

// Line
int lineCount = 4;
ADS1015 lineSensor;

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

  // Osbtacle init
  if (obstacleSensor.begin(0x48) == false)
  {
    Serial.println("Osbtacle sensor not found. Check wiring.");
    while (1)
      ;
  }
  obstacleSensor.setGain(ADS1015_CONFIG_PGA_16);
  pinMode(osbtacleCmdPin, OUTPUT);
  digitalWrite(osbtacleCmdPin, HIGH);

  // Line init
  if (lineSensor.begin(0x49) == false)
  {
    Serial.println("Line sensor not found. Check wiring.");
    while (1)
      ;
  }
  pinMode(lineCmdPin, OUTPUT);
  digitalWrite(lineCmdPin, HIGH);

  Serial.println("\nElio started !\n");
}

void loop()
{

  switch (buttonState)
  {
  case 0:
    pixels.setPixelColor(0, pixels.Color(10, 10, 10));

    motorA.stop();
    motorB.stop();

    break;

  case 1:
    if (obstacleSensor.getSingleEnded(0) < 5)
    {
      pixels.setPixelColor(0, pixels.Color(0, 10, 0));

      motorA.forward();
      motorB.forward();
    }
    else if (obstacleSensor.getSingleEnded(0) < 15)
    {
      pixels.setPixelColor(0, pixels.Color(10, 0, 10));
      pixels.show();

      motorA.forward();
      motorB.backward();
      delay(100);
    }
    else
    {
      pixels.setPixelColor(0, pixels.Color(10, 0, 10));
      pixels.show();

      motorA.backward();
      motorB.forward();
      delay(100);
    }

    break;

  case 2:
    pixels.setPixelColor(0, pixels.Color(0, 0, 10));

    motorA.backward();
    motorB.backward();

    break;

  default:
    buttonState = 0;
    break;
  }

  pixels.show();

  delay(100);
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