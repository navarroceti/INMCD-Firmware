#include <Arduino.h>
#define ENCODER_A 36
#define ENCODER_B 39

volatile int encoder_value = 0; // Global variable for storing the encoder position
void encoder_isr()
{
    // Reading the current state of encoder A and B
    int A = digitalRead(ENCODER_A);
    int B = digitalRead(ENCODER_B);
    // If the state of A changed, it means the encoder has been rotated
    if ((A == HIGH) != (B == LOW))
    {
        encoder_value--;
    }
    else
    {
        encoder_value++;
    }
}
void encoder_setup()
{
    pinMode(ENCODER_A, INPUT_PULLUP);
    pinMode(ENCODER_B, INPUT_PULLUP);
    // Attaching the ISR to encoder A
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoder_isr, CHANGE);
}
void encoder_loop()
{
    Serial.println(">encoder: " + String(encoder_value));
}
