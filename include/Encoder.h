#include <ESP32RotaryEncoder.h>

class Encoder
{
private:
    const uint8_t DI_ENCODER_A = 36; // Might be labeled CLK
    const uint8_t DI_ENCODER_B = 39; // Might be labeled DT

public:
    Encoder()
    {
        RotaryEncoder rotaryEncoder(DI_ENCODER_A, DI_ENCODER_B);
        // This tells the library that the encoder has its own pull-up resistors
        rotaryEncoder.setEncoderType(EncoderType::HAS_PULLUP);

        // Range of values to be returned by the encoder: minimum is 1, maximum is 10
        // The third argument specifies whether turning past the minimum/maximum will
        // wrap around to the other side:
        //  - true  = turn past 10, wrap to 1; turn past 1, wrap to 10
        //  - false = turn past 10, stay on 10; turn past 1, stay on 1
        rotaryEncoder.setBoundaries(1, 10, true);

        // The function specified here will be called every time the knob is turned
        // and the current value will be passed to it
        rotaryEncoder.onTurned(&knobCallback);

        // This is where the inputs are configured and the interrupts get attached
        rotaryEncoder.begin();
    }
    ~Encoder() {}
    void knobCallback(long value)
    {
        // This gets executed every time the knob is turned
        Serial.printf("Value: %i\n", value);
    }
};