#include <SparkFun_TB6612.h>

#define AIN1 26   // 控制輸入A1
#define AIN2 24  // 控制輸入A2
#define BIN1 30  // 控制輸入B1
#define BIN2 32  // 控制輸入B2
#define PWMA 22
#define PWMB 34
#define STBY 28  // 「待機」控制接Arduino的11腳

const int offsetA = 1;  // 正反轉設定A，可能值為1或-1。
const int offsetB = 1;  // 正反轉設定B，可能值為1或-1。

Motor motor2 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor1 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
 // 這裡沒有程式碼
}

void loop() {
   motor1.drive(255);
   motor2.drive(255);
}