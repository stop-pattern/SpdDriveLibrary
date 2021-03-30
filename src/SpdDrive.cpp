#include <Arduino.h>
#include <cmath>
#include <cstdint>
#include <array>
#include <bitset>

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

void SpdDrive::outputLeds(std::array<std::bitset<8>, registerCount> array) {
    std::array<uint8_t, registerCount> out = {};
    for (size_t i = 0; i < registerCount; i++) {
        // std::bitset<8> to uint8_t
        out[i] = array[i].to_ulong();   // この実装気持ち悪いから何とかしたい
    }
    
    for (size_t i = 0; i < array.size(); i++)
    {
        shiftOut(SER, SCK, MSBFIRST, out[i]);
    }
    digitalWrite(RCK, LOW);
    digitalWrite(RCK, HIGH);
    shiftRegister = array;
}

void SpdDrive::setLeds(std::array<std::bitset<8>, registerCount> array) {
    if (array == shiftRegister) return;
    outputLeds(array);
}

void SpdDrive::setAtcIndicators(uint32_t ind) {
    std::array<std::bitset<8>, registerCount> array = shiftRegister;

    for (size_t i = 0; i < 4; i++) {
        array[i] = ind;
        ind >> 8;
    }
    /*
    temp |= ind & 0b11111111;
    array[0] = temp;
    ind >> 8;
    temp |= ind & 0b11111111;
    array[1] = temp;
    ind >> 8;
    temp |= ind & 0b11111111;
    array[2] = temp;
    */
    
    setLeds(array);
}

void SpdDrive::setAtcG(bool status) {
    std::array<std::bitset<8>, registerCount> temp = shiftRegister;
    temp[4].set(0,status);
    setLeds(temp);
}
void SpdDrive::setAtcR(bool status) {
    std::array<std::bitset<8>, registerCount> temp = shiftRegister;
    temp[4].set(1,status);
    setLeds(temp);
}
void SpdDrive::setAtcX(bool status) {
    std::array<std::bitset<8>, registerCount> temp = shiftRegister;
    temp[4].set(2,status);
    setLeds(temp);
}
void SpdDrive::setAtcP(bool status) {
    std::array<std::bitset<8>, registerCount> temp = shiftRegister;
    temp[4].set(3,status);
    setLeds(temp);
}
void SpdDrive::setAtcNotice(bool status) {
    std::array<std::bitset<8>, registerCount> temp = shiftRegister;
    temp[4].set(4,status);
    setLeds(temp);
}
void SpdDrive::setBackLight(bool status) {
    std::array<std::bitset<8>, registerCount> temp = shiftRegister;
    temp[4].set(5,status);
    setLeds(temp);
}
void SpdDrive::setAts(bool status) {
    std::array<std::bitset<8>, registerCount> temp = shiftRegister;
    temp[5].set(0,status);
    setLeds(temp);
}
void SpdDrive::setAts15(bool status) {
    std::array<std::bitset<8>, registerCount> temp = shiftRegister;
    temp[5].set(1,status);
    setLeds(temp);
}
void SpdDrive::setAts60(bool status) {
    std::array<std::bitset<8>, registerCount> temp = shiftRegister;
    temp[5].set(2,status);
    setLeds(temp);
}
