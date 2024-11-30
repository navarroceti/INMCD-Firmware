#include <Arduino.h>

class Led
{
private:
    bool estado;
    const int ledPin = LED_BUILTIN;
public:
    Led(){
        pinMode(this->ledPin, OUTPUT);
    }
    ~Led(){}
};
