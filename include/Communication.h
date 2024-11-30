#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class Communication
{
private:
    const int speed = 115200;

public:
    Communication(){
        Serial.begin(this->speed);
    }
    void Log(){
        // Serial.println(message);
    }
    ~Communication(){

    }
};