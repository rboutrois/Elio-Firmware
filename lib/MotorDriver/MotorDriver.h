#ifndef MotorDriver_h
#define MotorDriver_h


class MotorDriver
{
public:
    MotorDriver(int channel, int phase, int enable);
    void isReversed();
    void forward();
    void backward();
    void stop();

private:
    int _channel;
    int _phase;
    int _enable;
    int _mode;
    int _freq = 20000;
    int _resolution = 8;
    bool _direction = HIGH;
};

#endif
