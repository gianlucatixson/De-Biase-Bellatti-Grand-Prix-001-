#include <PS4Controller.h>
#include <ESP32Servo.h>
#include <analogWrite.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>

//pines de Driver L293
#define A1 19
#define A2 18
#define A3 16
#define A4 2
#define MOTOR_DC_A 25
#define MOTOR_DC_B 17

//config Servo
#define MINSG90 500
#define MAXSG90 2400
#define frecuencia 50
Servo servo;6


void setup() {
  Serial.begin(115200);
  PS4.begin("2b:3c:4d:02:02:02");
  Serial.println("Ready.");
  
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(MOTOR_DC_A, OUTPUT);
  pinMode(MOTOR_DC_B, OUTPUT);
  digitalWrite(MOTOR_DC_A, HIGH);
  digitalWrite(MOTOR_DC_B, HIGH);

  pinMode(15, OUTPUT);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  servo.setPeriodHertz(frecuencia);

  servo.attach(15, MINSG90, MAXSG90);
}

void loop() {
  if (PS4.isConnected()) {
    while (PS4.R2()) {
      drive();
    }
    while (PS4.L2()) {
      reverse();
    }
    while (PS4.LStickX()) {
      zervo();
    }
      stop();
    
  }
}

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
