// Monash University Winter Research Project 2022
// Peristaltic Motor Driver Program
// Written by Ryan Wee

#include <SparkFun_TB6612.h>

// Define uC port numbers
#define AIN1 9
#define AIN2 10
#define BIN1 7
#define BIN2 6
#define PWMA 11
#define PWMB 5
#define STBY 8
#define POT 0

// Init global vars
int pot, pwm;

// Define pumps
Motor pump1 = Motor(AIN1, AIN2, PWMA, 1, STBY);
Motor pump2 = Motor(BIN1, BIN2, PWMB, 1, STBY);

void setup() {
  // Set port pinmodes
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Modulate PWM by reading pot
  //pot = analogRead(POT)/4;

  // Map 0-1024 range of pot to 0-255 for PWM
  // pwm = map(pot, 0,1023, 0,254);
  pwm = 254;
  Serial.println(pwm);

  // PWM control
  pump1.drive(pwm);
  //forward(pump1, pump2, pwm);

  // Pull up standby
  digitalWrite(STBY, HIGH);

  // Delay
  delay(100);
}
