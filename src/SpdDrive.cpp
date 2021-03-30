#include <Arduino.h>
#include <cmath>
#include <cstdint>
#include <array>

#include "const.h"
#include "LedcParam.h"
#include "SpdDrive.h"

SpdDrive::SpdDrive(/* args */) {
    setPWM1(PWM0, 0, 16);
    setPWM2(PWM1, 1, 16);
}

SpdDrive::~SpdDrive() {
    delete needle[0];
    delete needle[1];
}


void SpdDrive::setPWM1(const uint8_t output_pin, uint8_t ch, uint8_t bit, double freq) {
    needle[0] = new LedcParam(output_pin, ch, bit, freq);
}

void SpdDrive::setPWM2(const uint8_t output_pin, uint8_t ch, uint8_t bit, double freq) {
    needle[0] = new LedcParam(output_pin, ch, bit, freq);
}


double SpdDrive::setPWMvalue(LedcParam *ledc, uint32_t value) {
    uint32_t max = pow(2, ledc->getLedcBit());
    ledc->writeLedc(value);
    return value / max;
}

double SpdDrive::setPWM1value(uint32_t value) {
    return setPWMvalue(needle[0], value);
}

double SpdDrive::setPWM2value(uint32_t value) {
    return setPWMvalue(needle[1], value);
}


uint32_t SpdDrive::setPWMduty(LedcParam *ledc, double duty) {
    if(abs(duty) > 1.00) duty = 1.00;
    uint32_t max = pow(2, ledc->getLedcBit());
    uint32_t value = max * abs(duty);
    ledc->writeLedc(value);
    return value;
}

uint32_t SpdDrive::setPWM1duty(double duty) {
    return setPWMduty(needle[0], duty);
}

uint32_t SpdDrive::setPWM2duty(double duty) {
    return setPWMduty(needle[1], duty);
}
