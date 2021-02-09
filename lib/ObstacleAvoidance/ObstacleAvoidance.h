#ifndef Arduino_h
#include "Arduino.h"
#endif

#ifndef ObstacleAvoidance_h
#define ObstacleAvoidance_h


class ObstacleAvoidance
{
    public :
        ObstacleAvoidance(int LedControl, int Sensor1, int Sensor2, int Sensor3);
        int read(int sensorNumber);
;
    
    private :
        const int _sensorNumber = 3;

        int _LedControl;
        int _Sensor[3];

        int _sensorValue[3];
        int _ambient[3];

};

#endif
