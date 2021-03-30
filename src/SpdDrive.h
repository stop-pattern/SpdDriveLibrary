#ifndef SPDDRIVE_H
#define SPDDRIVE_H


// 基板の各種操作をラップするクラス
class SpdDrive
{
private:
    std::array<LedcParam*, 2> needle;                           // 針
    std::array<std::bitset<8>, registerCount> shiftRegister;    // シフトレジスタ

    // PWM初期設定
    void setPWM1(const uint8_t output_pin, uint8_t ch = 0, uint8_t bit = 16, double freq = 1220);
    void setPWM2(const uint8_t output_pin, uint8_t ch = 0, uint8_t bit = 16, double freq = 1220);

    // 指定した値でPWM出力
    double setPWMvalue(LedcParam *ledc, uint32_t value);

    // 指定したデューティ比でPWM出力
    uint32_t setPWMduty(LedcParam *ledc, double value);

    // シフトレジスタに値を出力
    void outputLeds(std::array<std::bitset<8>, registerCount>);
public:
    SpdDrive(/* args */);
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
    void setLeds(std::array<std::bitset<8>, registerCount> array);

    // 値を変更
    void setAtcIndicators(uint32_t ind);
    void setAtcG(bool status);
    void setAtcR(bool status);
    void setAtcX(bool status);
    void setAtcP(bool status);
    void setAtcNotice(bool status);
    void setBackLight(bool status);
    void setAts(bool status);
    void setAts15(bool status);
    void setAts60(bool status);
};


#endif //SPDDRIVE_H