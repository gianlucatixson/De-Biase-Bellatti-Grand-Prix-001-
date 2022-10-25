#include <ESP32_Servo.h>
#include <PS4Controller.h>
#include <ps4.h>
#include <ps4_int.h>

#define SERVO 23
#define MOTOR_DC_A 9
#define MOTOR_DC_B 28

#define PWM_MOTOR_IN_1 0
#define PWM_MOTOR_IN_2 1
#define PWM_SERVO 3

#define FREQ 10000
#define RESOLUCION 8

void setup() {
//SETUP JOYSTICK
  Serial.begin(115200);
  PS4.begin("1a:2b:3c:01:01:01");
  Serial.println("Ready.");

//SETUP PWM
  ledcSetup(PWM_MOTOR_DC, FREQ, RESOLUCION);
  ledcSetup(PWM_SERVO, FREQ, RESOLUCION);

  ledcAttachPin(MOTOR_DC_A, PWM_MOTOR_DC);  
  ledcAttachPin(MOTOR_DC_B, PWM_MOTOR_DC);  
  ledcAttachPin(SERVO, PWM_SERVO);
}

void drive() {
  
  while (CT > 30) {
   CT = PS4.R2Value());         
      ledcWrite(PWM_MOTOR_DC, CT);
  }
}

void reverse() {
  
  while (CT > 30){
   CT = PS4.L2Value());
      ledcWrite(PWM_MOTOR_DC, CT);
  }
}

void servo() {
  
  while (CT > 30){
   CT = PS4.LStickX());
      ledcWrite(PWM_SERVO, CT);
  }
}
void loop() {
  drive();
  reverse();
  servo();
}
