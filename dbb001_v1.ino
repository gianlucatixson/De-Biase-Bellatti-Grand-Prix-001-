#include <ESP32_Servo.h>
#include <PS4Controller.h>
#include <ps4.h>
#include <ps4_int.h>

#define SERVO //*pin*
#define MOTOR_DC_A //*pin*
#define MOTOR_DC_B //*pin*

int throttle_trig = 0;
int reverse_trig = 0;
int direccion = 0;

void setup() {
  Serial.begin(115200);
  PS4.begin("1a:2b:3c:01:01:01");
  Serial.println("Ready.");
}

void drive() {
 

  
}

void reverse() {

}

void Servo() {

}

void loop() {

}