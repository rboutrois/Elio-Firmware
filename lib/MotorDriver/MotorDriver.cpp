#ifndef Arduino_h
#include "Arduino.h"
#endif

#ifndef AnalogWrite_h
#include "AnalogWrite.h"
#endif

#include <MotorDriver.h>

MotorDriver::MotorDriver(int channel, int phase, int enable)
{
  _channel = channel;
  _phase = phase;
  _enable = enable;

  pinMode(_phase, OUTPUT);
  pinMode(_enable, OUTPUT);

  digitalWrite(_phase, LOW);
  digitalWrite(_enable, LOW);
}

void MotorDriver::isReversed()
{
  _direction = !_direction;
}

void MotorDriver::forward()
{
  digitalWrite(_phase, !_direction);
  digitalWrite(_enable, _direction);
}

void MotorDriver::backward()
{
  digitalWrite(_phase, _direction);
  digitalWrite(_enable, !_direction);
}

void MotorDriver::stop()
{
  digitalWrite(_phase, HIGH);
  digitalWrite(_enable, HIGH);
}
