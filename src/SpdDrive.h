#ifndef SPDDRIVE_H
#define SPDDRIVE_H

#include "const.h"
#include "LedcParam.h"

// 基板の各種操作をラップするクラス
class SpdDrive
{
private:
    LedcParam needle[2];                    // 針
    uint8_t shiftRegister[registerCount];   // シフトレジスタ

    // PWM初期設定
    void setPWM1(const uint8_t output_pin, uint8_t ch = 0, uint8_t bit = 16, double freq = 1220);
    void setPWM2(const uint8_t output_pin, uint8_t ch = 0, uint8_t bit = 16, double freq = 1220);

    // 指定した値でPWM出力
    double setPWMvalue(LedcParam *ledc, uint32_t value);

    // 指定したデューティ比でPWM出力
    uint32_t setPWMduty(LedcParam *ledc, double value);

    // シフトレジスタに値を出力
    void outputLeds(uint8_t array[registerCount]);

    // 指定個所の値を変更して返す
    uint8_t setBit(uint8_t in, uint8_t digit = 0, bool status = false);

    // 値を変更して出力
    void setLedsWrapper(uint8_t a, uint8_t b, bool status = false);
public:
    SpdDrive();
    ~SpdDrive();

    // setup()で動かす用のやつ(初期化)
    void begin();

    // 指定した値でPWM出力
    double setPWM1value(uint32_t value);
    double setPWM2value(uint32_t value);
    
    // 指定したデューティ比でPWM出力
    uint32_t setPWM1duty(double duty);
    uint32_t setPWM2duty(double duty);

    // シフトレジスタに値を出力
    void setLeds(uint8_t array[registerCount]);

    // 値を変更
    void setAtcIndicators(uint32_t ind);
    void setAtcG(bool status);
    void setAtcR(bool status);
    void setAtcX(bool status);
    void setAtcP(bool status);
    void setAtcNotice(bool status);
    void setBackLight(bool status);
    void setDoor(bool status);
    void setAts(bool status);
    void setAts15(bool status);
    void setAts60(bool status);
};


#endif //SPDDRIVE_H