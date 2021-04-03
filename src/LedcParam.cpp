#include <Arduino.h>
#include <cmath>
#include <cstdint>

#include "const.h"
#include "LedcParam.h"

LedcParam::LedcParam() {
}

LedcParam::LedcParam(uint8_t output_pin, uint8_t ch, uint8_t bit, double freq) {
    if(0 <= ch && ch <= 8) ch = 0;
    if(0 <= bit && bit <= 15) bit = 0;

    pin = output_pin;
    channel = ch;
    frequency = freq;
    duty_bit = bit;

    pinMode(output_pin, OUTPUT);

    setupLedc();
}

LedcParam::~LedcParam() {
    ledcDetachPin(pin);
}


void LedcParam::setupLedc() {
    frequency = ledcSetup(channel, frequency, duty_bit);
    ledcAttachPin(pin, channel);
}

void LedcParam::writeLedc(uint32_t duty) {
    if(duty == previous) return;
    uint32_t max = pow(2, duty_bit);
    if(duty > max) duty = max;
    ledcWrite(channel, duty);
    previous = duty;
}

uint8_t LedcParam::getLedcBit() {
    return duty_bit;
}
