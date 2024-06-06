#include <Servo.h>   //載入函式庫，這是內建的，不用安裝

Servo myservo;  // 建立SERVO物件

int pos=0;

void setup() {
  myservo.attach(2);  // 設定要將伺服馬達接到哪一個PIN腳
  myservo.write(0);
  delay(5000);
}

void loop() {   
  /*
  for(pos = 0; pos < 180; pos += 1)
  { 
    myservo.write(pos); delay(15);
  } 
      // 180到0旋轉舵機，每次延時15毫秒 
  for(pos = 180; pos>=1; pos-=1)
  {                               
    myservo.write(pos);
    delay(15);
  }
  */
  myservo.write(100);

}