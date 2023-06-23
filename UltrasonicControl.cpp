// Authors:
// - Palguno Wicaksono
// - Ahmad Mishbahuddin
// - Yeremi Wesly Sinaga
// =====================================
//
// This library was a final exam project
// for 02143252003
// at Sebelas Maret University
//
// The copyright holder <the authors> grant the freedom
// to copy, modify, convey, adapt, and/or redistribute this work
// under the terms of the Massachusetts Institute of Technology License.

#include "UltrasonicControl.h"

#define ECHO_ULTRASONIC_1 D1
#define TRIG_ULTRASONIC_1 D2
#define ECHO_ULTRASONIC_2 D6
#define TRIG_ULTRASONIC_2 D5

void UltrasonicControl::initUltrasonicControl()
{
  pinMode(ECHO_ULTRASONIC_1, INPUT);
  pinMode(TRIG_ULTRASONIC_1, OUTPUT);
  pinMode(ECHO_ULTRASONIC_2, INPUT);
  pinMode(TRIG_ULTRASONIC_2, OUTPUT);
}

int UltrasonicControl::getDistance(int index)
{
  int triggerPin, echoPin;
  long duration, distance;
  if (index == 0)
  {
    triggerPin = TRIG_ULTRASONIC_1;
    echoPin = ECHO_ULTRASONIC_1;
  }
  else
  {
    triggerPin = TRIG_ULTRASONIC_2;
    echoPin = ECHO_ULTRASONIC_2;
  }
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(3);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(12);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return (int)distance;
}