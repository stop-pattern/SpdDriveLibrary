#include <Arduino.h>
#include <cmath>
#include <cstdint>
#include <array>
#include <bitset>

#include "const.h"
#include "LedcParam.h"
#include "SpdDrive.h"


SpdDrive::SpdDrive() {
}

SpdDrive::~SpdDrive() {
    /*
    delete needle[0];
    delete needle[1];
    */
}

void SpdDrive::begin() {
    setPWM1(PWM0, 0, 16);
    setPWM2(PWM1, 1, 16);
}

void SpdDrive::setPWM1(const uint8_t output_pin, uint8_t ch, uint8_t bit, double freq) {
    needle[0] = LedcParam(output_pin, ch, bit, freq);
}

void SpdDrive::setPWM2(const uint8_t output_pin, uint8_t ch, uint8_t bit, double freq) {
    needle[0] = LedcParam(output_pin, ch, bit, freq);
}


double SpdDrive::setPWMvalue(LedcParam *ledc, uint32_t value) {
    uint32_t max = pow(2, ledc->getLedcBit());
    ledc->writeLedc(value);
    return value / max;
}

double SpdDrive::setPWM1value(uint32_t value) {
    return setPWMvalue(&needle[0], value);
}

double SpdDrive::setPWM2value(uint32_t value) {
    return setPWMvalue(&needle[1], value);
}


uint32_t SpdDrive::setPWMduty(LedcParam *ledc, double duty) {
    if(abs(duty) > 1.00) duty = 1.00;
    uint32_t max = pow(2, ledc->getLedcBit());
    uint32_t value = max * abs(duty);
    ledc->writeLedc(value);
    return value;
}

uint32_t SpdDrive::setPWM1duty(double duty) {
    return setPWMduty(&needle[0], duty);
}

uint32_t SpdDrive::setPWM2duty(double duty) {
    return setPWMduty(&needle[1], duty);
}

void SpdDrive::outputLeds(uint8_t array[registerCount]) {
    for (size_t i = 0; i < registerCount; i++)
    {
        shiftOut(SER_DIO, SER_SCK, MSBFIRST, array[i]);
    }
    digitalWrite(SER_RCK, LOW);
    digitalWrite(SER_RCK, HIGH);
    
    for (size_t i = 0; i < registerCount; i++) {
        shiftRegister[i] = array[i];
    }
}

void SpdDrive::setLeds(uint8_t array[registerCount]) {
    if (array == shiftRegister) return;
    outputLeds(array);
}

void SpdDrive::setAtcIndicators(uint32_t ind) {
    uint8_t array[registerCount] = {};
    for (size_t i = 0; i < registerCount; i++) {
        array[i] = shiftRegister[i];
    }

    uint8_t temp = 0;
    for (size_t i = 0; i < 4; i++) {
        temp |= ind & 0b11111111;
        array[i] = temp;
        ind = ind >> 8;
    }
    /*
    temp |= ind & 0b11111111;
    array[0] = temp;
    ind = ind >> 8;
    temp |= ind & 0b11111111;
    array[1] = temp;
    ind = ind >> 8;
    temp |= ind & 0b11111111;
    array[2] = temp;
    */

    setLeds(array);
}

uint8_t SpdDrive::setBit(uint8_t in, uint8_t digit, bool status) {
    if(digit >= 8) digit = 8;
    uint8_t ret = in & ~(1 << digit);
    return ret | (status << digit);
}

void SpdDrive::setLedsWrapper(uint8_t a, uint8_t b, bool status) {
    uint8_t array[registerCount] = {};
    for (size_t i = 0; i < registerCount; i++) {
        array[i] = shiftRegister[i];
    }
    array[a] = setBit(array[a], b, status);
    setLeds(array);
}

void SpdDrive::setAtcG(bool status) {
    setLedsWrapper(4, 0, status);
}
void SpdDrive::setAtcR(bool status) {
    setLedsWrapper(4, 1, status);
}
void SpdDrive::setAtcX(bool status) {
    setLedsWrapper(4, 2, status);
}
void SpdDrive::setAtcP(bool status) {
    setLedsWrapper(4, 3, status);
}
void SpdDrive::setAtcNotice(bool status) {
    setLedsWrapper(4, 4, status);
}
void SpdDrive::setBackLight(bool status) {
    setLedsWrapper(4, 5, status);
}
void SpdDrive::setDoor(bool status) {
    setLedsWrapper(4, 6, status);
}
void SpdDrive::setAts(bool status) {
    setLedsWrapper(5, 0, status);
}
void SpdDrive::setAts15(bool status) {
    setLedsWrapper(5, 1, status);
}
void SpdDrive::setAts60(bool status) {
    setLedsWrapper(5, 2, status);
}
