#include <PS4Controller.h>
#include <ESP32Servo.h>
#include <analogWrite.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>
#define A1 19
#define A2 18
#define A3 16
#define A4 2
#define MOTOR_DC_A 25
#define MOTOR_DC_B 17
#define MINSG90 500
#define MAXSG90 2400
#define frecuencia 50
Servo servo;

void zervo() {
  int CT3;
  CT3 = PS4.LStickX();
  int grados = map(CT3, -128, 128, 45, 135);
  Serial.printf("Left Stick x at %d\n", CT3);
  Serial.printf("servo grados:  %d\n", grados);
  servo.write(grados);
}

void drive() {
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, LOW);
}

void reverse() {
  digitalWrite(A2, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A4, HIGH);
  digitalWrite(A3, LOW);
}

void stop() {
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
}

void setup() {
  Serial.begin(115200);
  PS4.begin("1a:2b:3c:01:01:01");
  Serial.println("Ready.");
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(MOTOR_DC_A, OUTPUT);
  pinMode(MOTOR_DC_B, OUTPUT);
  digitalWrite(MOTOR_DC_A, HIGH);
  digitalWrite(MOTOR_DC_B, HIGH);
  //pines();
  pinMode(15, OUTPUT);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  //ServosHz();
  servo.setPeriodHertz(frecuencia);
  //ServosAttach();
  servo.attach(15, MINSG90, MAXSG90);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (PS4.isConnected()) {
    if (PS4.R2()) {
      drive();
    }
    if (PS4.L2()) {
      reverse();
    }
    if (PS4.LStickX()) {
      zervo();
    }
      stop();
    
  }
}
