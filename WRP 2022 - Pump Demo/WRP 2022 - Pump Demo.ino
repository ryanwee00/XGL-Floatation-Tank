// Monash University Winter Research Project 2022
// Hardcoded demonstration of pumps
// Written by Ryan Wee

// Libraries
#include <SparkFun_TB6612.h>

// Pin numbers
// Pump types - air/water
// Number - corresponding to pump
// A/B - controls direction (swap for forward/reverse)
#define air1A 22
#define air1B 23
#define air2A 24               
#define air2B 25
#define air3A 26
#define air3B 27
#define air4A 30
#define air4B 31
#define airPWM1 2
#define airPWM2 3
#define airPWM3 4
#define airPWM4 5
#define water1A 28  // Temp - Ori 30
#define water1B 29  // Temp - Ori 31
#define water2A 32
#define water2B 33
#define waterPWM1 5 // Temp - Ori 6
#define waterPWM2 7
#define bilge 34
#define stby 8

// Set demo delays (s)
int globalOnSet = 5;
int globalOffSet = 1;
int mod1Set = 0.1;
int mod2Set = 0.3;
int mod3Set = 0.5;
int mod4Set = 1;

// Set PWM steps (%)
int pwm1Set = 0.3;
int pwm2Set = 0.5;
int pwm3Set = 0.7;
int pwm4Set = 0.9;
const int maxPwm = 254;

// Calculate delays (ms)
const int delay1sec = 1000;
int globalOn = globalOnSet * delay1sec;
int globalOff = globalOffSet * delay1sec;
int mod1 = mod1Set * delay1sec;
int mod2 = mod2Set * delay1sec;
int mod3 = mod3Set * delay1sec;
int mod4 = mod4Set * delay1sec;

// Calculate PWM steps (8-bits)
int pwm1 = map(pwm1Set, 1, 100, 0, maxPwm);
int pwm2 = map(pwm2Set, 1, 100, 0, maxPwm);
int pwm3 = map(pwm3Set, 1, 100, 0, maxPwm);
int pwm4 = map(pwm4Set, 1, 100, 0, maxPwm);

void setup() {
  // Set port pinmodes
  pinMode(air1A, OUTPUT);
  pinMode(air1B, OUTPUT);
  pinMode(air2A, OUTPUT);
  pinMode(air2B, OUTPUT);
  pinMode(air3A, OUTPUT);
  pinMode(air3B, OUTPUT);
  pinMode(air4A, OUTPUT);
  pinMode(air4B, OUTPUT);
  pinMode(airPWM1, OUTPUT);
  pinMode(airPWM2, OUTPUT);
  pinMode(airPWM3, OUTPUT);
  pinMode(airPWM4, OUTPUT);
  pinMode(water1A, OUTPUT);
  pinMode(water1B, OUTPUT);
  pinMode(water2A, OUTPUT);
  pinMode(water2B, OUTPUT);
  pinMode(waterPWM1, OUTPUT);
  pinMode(waterPWM1, OUTPUT);
  pinMode(bilge, OUTPUT);
  pinMode(stby, OUTPUT);

  // Set serial monitor at baud rate
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println(" ");

  // Pull up standby
  digitalWrite(stby, HIGH);
}

void loop() {
  // Sequence design
  // Cycle through each pump at 100% power
  // Cycle through each pump at varying modulation patterns
  // All pumps at 100% power
  // All pumps at varying modulation patterns
  // All pumps at ramping PWM duty cycle

  // Cycle through each pump at 100% power
  Serial.println("1: Cycling through each pump at max power");
  toggle(air1A, air1B, airPWM1, globalOn, globalOff, maxPwm);
  Serial.println("   Air1 complete");
  toggle(air2A, air2B, airPWM2, globalOn, globalOff, maxPwm);
  Serial.println("   Air2 complete");
  toggle(air3A, air3B, airPWM3, globalOn, globalOff, maxPwm);
  Serial.println("   Air3 complete");
  toggle(water1A, water1B, waterPWM1, globalOn, globalOff, maxPwm);
  Serial.println("   Water1 complete");

  // Cycle through each pump at varying modulation patterns
  Serial.println("2: Cycling through each pump at varying modulation patterns");
  modulate(air1A, air1B, airPWM1, mod1, globalOn, globalOff, maxPwm);
  Serial.println("   Air1 complete");
  modulate(air2A, air2B, airPWM2, mod2, globalOn, globalOff, maxPwm);
  Serial.println("   Air2 complete");
  modulate(air3A, air3B, airPWM3, mod3, globalOn, globalOff, maxPwm);
  Serial.println("   Air3 complete");
  modulate(water1A, water1B, waterPWM1, mod4, globalOn, globalOff, maxPwm);
  Serial.println("   Water1 complete");
  
  // All pumps at 100% power
  Serial.println("3: All pumps at max power");
  for (int i = 0; i < 3; i++) {
    toggleAll(air1A, air1B, air2A, air2B, air3A, air3B, water1A, water1B, airPWM1, airPWM2, airPWM3, waterPWM1, globalOn, globalOff, maxPwm);
    Serial.println("   Iteration ");
    Serial.print(i+1);
    Serial.print(" complete");
  }

  // All pumps at varying modulation patterns
  Serial.println("4: All pumps at varying modulation patterns");
  modulateAll(air1A, air1B, air2A, air2B, air3A, air3B, water1A, water1B, airPWM1, airPWM2, airPWM3, waterPWM1, mod1, globalOn, globalOff, maxPwm);
  Serial.println("   Mod1 complete");
  modulateAll(air1A, air1B, air2A, air2B, air3A, air3B, water1A, water1B, airPWM1, airPWM2, airPWM3, waterPWM1, mod2, globalOn, globalOff, maxPwm);
  Serial.println("   Mod2 complete");
  modulateAll(air1A, air1B, air2A, air2B, air3A, air3B, water1A, water1B, airPWM1, airPWM2, airPWM3, waterPWM1, mod3, globalOn, globalOff, maxPwm);
  Serial.println("   Mod3 complete");
  modulateAll(air1A, air1B, air2A, air2B, air3A, air3B, water1A, water1B, airPWM1, airPWM2, airPWM3, waterPWM1, mod4, globalOn, globalOff, maxPwm);
  Serial.println("   Mod4 complete");

  // All pumps at ramping PWM duty cycle
  Serial.println("5: All pumps at ramping PWM duty cycle");
  toggleAll(air1A, air1B, air2A, air2B, air3A, air3B, water1A, water1B, airPWM1, airPWM2, airPWM3, waterPWM1, globalOn, 5, pwm1);
  Serial.println("   PWM1 complete");
  toggleAll(air1A, air1B, air2A, air2B, air3A, air3B, water1A, water1B, airPWM1, airPWM2, airPWM3, waterPWM1, globalOn, 5, pwm2);
  Serial.println("   PWM2 complete");
  toggleAll(air1A, air1B, air2A, air2B, air3A, air3B, water1A, water1B, airPWM1, airPWM2, airPWM3, waterPWM1, globalOn, 5, pwm3);
  Serial.println("   PWM3 complete");
  toggleAll(air1A, air1B, air2A, air2B, air3A, air3B, water1A, water1B, airPWM1, airPWM2, airPWM3, waterPWM1, globalOn, 5, pwm4);
  Serial.println("   PWM4 complete");

  delay(globalOff);
  Serial.println("0: Demonstration completed, restarting...");
  delay(globalOn);
}

void toggle(int outA, int outB, int outPwm, int delayOn, int delayOff, int pwm) {
  digitalWrite(outPwm, pwm);
  digitalWrite(outA, HIGH);
  digitalWrite(outB, LOW);
  delay(delayOn);
  digitalWrite(outA, LOW);
  digitalWrite(outB, LOW);
  delay(delayOff);
}

void modulate(int outA, int outB, int outPwm, int delayMod, int delayOn, int delayOff, int pwm) {
  int targetIter = round(delayOn/delayMod);
  digitalWrite(outPwm, pwm);
  for (int i = 0; i < targetIter; i++) {
    digitalWrite(outA, HIGH);
    digitalWrite(outB, LOW);
    delay(delayMod);
    digitalWrite(outA, LOW);
    digitalWrite(outB, LOW);
    delay(delayMod);
  }
  delay(delayOff);
}

void toggleAll(int out1A, int out1B, int out2A, int out2B, int out3A, int out3B, int out4A, int out4B, int outPwm1, int outPwm2, int outPwm3, int outPwm4, int delayOn, int delayOff, int pwm) {
  digitalWrite(outPwm1, pwm);
  digitalWrite(outPwm2, pwm);
  digitalWrite(outPwm3, pwm);
  digitalWrite(outPwm4, pwm);
  digitalWrite(out1A, HIGH);
  digitalWrite(out1B, LOW);
  digitalWrite(out2A, HIGH);
  digitalWrite(out2B, LOW);
  digitalWrite(out3A, HIGH);
  digitalWrite(out3B, LOW);
  digitalWrite(out4A, HIGH);
  digitalWrite(out4B, LOW);
  delay(delayOn);
  digitalWrite(out1A, LOW);
  digitalWrite(out1B, LOW);
  digitalWrite(out2A, LOW);
  digitalWrite(out2B, LOW);
  digitalWrite(out3A, LOW);
  digitalWrite(out3B, LOW);
  digitalWrite(out4A, LOW);
  digitalWrite(out4B, LOW);
  delay(delayOff);
}

void modulateAll(int out1A, int out1B, int out2A, int out2B, int out3A, int out3B, int out4A, int out4B, int outPwm1, int outPwm2, int outPwm3, int outPwm4, int delayMod, int delayOn, int delayOff, int pwm) {
  int targetIter = round(delayOn/delayMod);

  for (int i = 0; i < targetIter; i++) {
    digitalWrite(outPwm1, pwm);
    digitalWrite(outPwm2, pwm);
    digitalWrite(outPwm3, pwm);
    digitalWrite(outPwm4, pwm);
    digitalWrite(out1A, HIGH);
    digitalWrite(out1B, LOW);
    digitalWrite(out2A, HIGH);
    digitalWrite(out2B, LOW);
    digitalWrite(out3A, HIGH);
    digitalWrite(out3B, LOW);
    digitalWrite(out4A, HIGH);
    digitalWrite(out4B, LOW);
    delay(delayMod);
    digitalWrite(out1A, LOW);
    digitalWrite(out1B, LOW);
    digitalWrite(out2A, LOW);
    digitalWrite(out2B, LOW);
    digitalWrite(out3A, LOW);
    digitalWrite(out3B, LOW);
    digitalWrite(out4A, LOW);
    digitalWrite(out4B, LOW);
    delay(delayMod);
  }
  delay(delayOff);
}
