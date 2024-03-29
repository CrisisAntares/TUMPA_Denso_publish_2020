/*このコードを何かに役立てようとしている人へ
このコードは人力飛行機という飛行機を動かすために作った試作品です。
基本的な関数、map、analogReadなどの関数を使用しておりサーボモータの動作内容もわかりやすくしています。
初心者向けのコードがたくさんあるのでうまく使ってください。
しかし一部コードを書き替えているので何か実践的に使用する場合は使用するモータや可変抵抗に合わせてコードを
書き直したり試行錯誤して使ってみてください。すべてのモータ、可変抵抗に合わせて作ったものでないのでこのコード
を使用して危険が生じても作者および共同開発者は責任を持ちませんので注意してください。
ではよい電子工作ライフを！！
CrisisAntares
*/
/*To those who are trying to make use of this code for something!
This code is a prototype that I made to run an airplane called a human-powered plane.
It uses basic functions, map, analogRead, and other functions to make it easy to understand what the servo motors do.
There is a lot of code for beginners, so please use it well.
However, some of the code has been rewritten, so if you want to use it in a practical way, please rewrite the code to fit the motor and variable resistor you are using, or use trial and error. Please note that the author and co-developers are not responsible for any danger caused by using this code, as it is not designed for all motors and variable resistors.
Have a good electronics building life!

Translated with www.DeepL.com/Translator (free version)
CrisisAntares*/
#include <Servo.h>

Servo servoel;
Servo servola;

#define la_servo_pin 6
#define el_servo_pin 3
#define la_adjust_pin A2
#define el_adjust_pin A3

float ru_trim; // sonomama
float el_trim; // sonomama

const int ru_pin = A1;        // inpin1
const int el_pin = A0;        // inpin2
float ru_operate, el_operate; // p,p1

float ru_adjust, el_adjust; // state,state1

float ru_trim_data, el_trim_data; // duration,duration1

float ru_data, el_data; // str1,str
double prev_ru, prev_el, ru_error, el_error;

void setup()
{
  Serial.begin(115200);
  pinMode(la_adjust_pin, INPUT);
  pinMode(el_adjust_pin, INPUT);
  pinMode(ru_data, INPUT);
  pinMode(el_data, INPUT);
  servola.attach(la_servo_pin);
  servoel.attach(el_servo_pin);
}

void loop()
{
  ru_adjust = analogRead(la_adjust_pin);
  el_adjust = analogRead(el_adjust_pin);
  ru_trim_data = analogRead(ru_pin);
  el_trim_data = analogRead(el_pin);
  ru_data = map(ru_adjust, 0, 1023, -60, 60);
  el_data = map(el_adjust, 0, 1023, -60, 60);
  ru_operate = map(ru_adjust, 0, 1023, 30, 150);
  el_operate = map(el_adjust, 0, 1023, 30, 150);
  ru_trim = map(ru_trim_data, 0, 1023, 30, 150);
  el_trim = map(el_trim_data, 0, 1023, 30, 150);

  ru_trim = ru_trim - ru_data;
  el_trim = el_trim - el_data;
  // N
  if (ru_trim >= (ru_operate - 10) && ru_trim <= (ru_operate + 10))
  {
    ru_trim = ru_operate;
  }
  if (el_trim >= (el_operate - 10) && el_trim <= (el_operate + 10))
  {
    el_trim = el_operate;
  }

  servola.write(ru_trim);
  servoel.write(el_trim);
  Serial.print(ru_trim);
  Serial.println(el_trim);
  delay(100);
}
