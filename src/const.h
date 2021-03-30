#ifndef CONST_H
#define CONST_H


// pin num define
#ifdef SAHA
#define PIN_PWM0 19
#define PIN_PWM1 18
#endif //SAHA


#ifndef PIN_PWM0
#define PIN_PWM0 0
#endif //PIN_PWM0

#ifndef PIN_PWM1
#define PIN_PWM1 0
#endif //PIN_PWM1


// pin num settings
constexpr uint8_t PWM0 = PIN_PWM0;
constexpr uint8_t PWM1 = PIN_PWM1;


#undef PIN_PWM0
#undef PIN_PWM1


#endif //CONST_H