#ifndef Pins_h
#include "Pins.h"
#endif

#ifndef Arduino_h
#include "Arduino.h"
#endif

#include <ObstacleAvoidance.h>


ObstacleAvoidance::ObstacleAvoidance(int LedControl, int Sensor1, int Sensor2, int Sensor3) 
{
    _LedControl = LedControl;
    _Sensor[0] = Sensor1;
    _Sensor[1] = Sensor2;
    _Sensor[2] = Sensor3;
    
    for(int i=0; i<_sensorNumber; i++)
    {
        pinMode(_Sensor[i], INPUT);
    }
    pinMode(_LedControl, OUTPUT);
    digitalWrite(_LedControl, LOW);

}


int ObstacleAvoidance::read(int sensorNumber)
{
    digitalWrite(_LedControl, LOW);
    delay(5);                            //To give ADC and LED transition time
    for(int i=0; i<_sensorNumber; i++)
    {
        _ambient[i] = analogRead(_Sensor[i]);
    }

    digitalWrite(_LedControl, HIGH);
    delay(5);

    // Lecture des capteurs de colision
    for(int i=0; i<_sensorNumber; i++)
    {
        _sensorValue[i] = analogRead(_Sensor[i]) - _ambient[i];
    }

    return(_sensorValue[sensorNumber]);
}