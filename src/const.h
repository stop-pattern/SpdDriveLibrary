#ifndef CONST_H
#define CONST_H


// pin number define
#ifdef SAHA
// for rev.2(additionally modificated)
#define PIN_PWM0 19
#define PIN_PWM1 18
#endif //SAHA


// default pin number define
#ifndef PIN_PWM0
#define PIN_PWM0 0
#endif //PIN_PWM0

#ifndef PIN_PWM1
#define PIN_PWM1 0
#endif //PIN_PWM1


// pin number settings
constexpr uint8_t PWM0 = PIN_PWM0;
constexpr uint8_t PWM1 = PIN_PWM1;
constexpr uint8_t SCL = 32; // shift register clear
constexpr uint8_t SER = 12; // serial data
constexpr uint8_t SCK = 33; // shift register clock
constexpr uint8_t RCK = 27; // storage register clock
constexpr uint8_t G = 14;   // output enable


#undef PIN_PWM0
#undef PIN_PWM1


#endif //CONST_H