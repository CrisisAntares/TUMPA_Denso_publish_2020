#include<Servo.h>

Servo servoel;
Servo servola;

#define la_servo_pin 6
#define el_servo_pin 3
#define la_adjust_pin A2
#define el_adjust_pin A3

float lajoy;
float la_trim;
float el_trim;

const int inPin1 = A1;
const int inpin2 = A0;
float p,p1;

int val = 0;

const int statepin = 9;
float state,state1;

unsigned long duration1,duration2;
String str_send_data;
float str1,str;
double prev_la,prev_el,la_error,el_error;

void setup() {                
  Serial.begin(115200);
  sTime = millis();
  pinMode(la_adjust_pin,INPUT);
  pinMode(el_adjust_pin,INPUT);
  pinMode(inPin1, INPUT);
  pinMode(inpin2,INPUT);
  pinMode(statepin,OUTPUT);
  servola.attach(la_servo_pin);
  servoel.attach(el_servo_pin);
}
 
void loop() {
  state = analogRead(la_adjust_pin);
  state1 = analogRead(el_adjust_pin);
  duration1 = analogRead(inPin1);
  duration2 = analogRead(inpin2);
  str = map(state,0,1023,-60,60);
  str1 = map(state1,0,1023,-60,60);
  p = map(state,0,1023,30,150);
  p1 = map(state1,0,1023,30,150);
  la_trim = map(duration1,0,1023,30,150);
  el_trim = map(duration2,0,1023,30,150);

  la_trim = la_trim - str;
  el_trim = el_trim - str1;
  //N
  if (la_trim >= (p - 10) && la_trim <= (p + 10)) {
    la_trim = p;
  }
  if (el_trim >= (p1 - 10) && el_trim <= (p1 + 10) ) {
    el_trim = p1;
  }
 
  servola.write(la_trim);
  servoel.write(el_trim);
  Serial.print(la_trim);
  Serial.println(el_trim);
  delay(100); 
}
