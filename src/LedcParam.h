#ifndef LEDCPARAM_H
#define LEDCPARAM_H

// ledcのPWMをラップするクラス
class LedcParam
{
private:
    const uint8_t pin;          // 割り当てるピン
    uint8_t channel = 0;        // 利用するチャンネル
    double frequency = 1220;    // PWMの基本周波数
    uint8_t duty_bit = 16;      // デューティ比を表すビット数
    uint32_t previous = 0;      // 前回の設定値

    // 現在保持する条件でledcを設定
    void setupLedc();

public:
    LedcParam(const uint8_t output_pin, uint8_t ch = 0, uint8_t bit = 16, double freq = 1220);
    ~LedcParam();

    // 0-2^nの範囲でPWM出力
    void writeLedc(uint32_t duty = 0);

    // デューティ比を表すビット数を取得
    uint8_t getLedcBit();
};

#endif //LEDCPARAM_H