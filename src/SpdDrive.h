#ifndef SPDDRIVE_H
#define SPDDRIVE_H

// 基板の各種操作をラップするクラス
class SpdDrive
{
private:
    std::array<LedcParam*, 2> needle;    // 針
    
    // 
    void setPWM1(const uint8_t output_pin, uint8_t ch = 0, uint8_t bit = 16, double freq = 1220);
    void setPWM2(const uint8_t output_pin, uint8_t ch = 0, uint8_t bit = 16, double freq = 1220);

    // 指定した値でPWM出力
    double setPWMvalue(LedcParam *ledc, uint32_t value);

    // 指定したデューティ比でPWM出力
    uint32_t setPWMduty(LedcParam *ledc, double value);
public:
    SpdDrive(/* args */);
    ~SpdDrive();


    // 指定した値でPWM出力
    double setPWM1value(uint32_t value);
    double setPWM2value(uint32_t value);
    
    // 指定したデューティ比でPWM出力
    uint32_t setPWM1duty(double duty);
    uint32_t setPWM2duty(double duty);
};

#endif //SPDDRIVE_H