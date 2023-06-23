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

#ifndef ULTRASONIC_CONTROL_H
#define ULTRASONIC_CONTROL_H

#include <Arduino.h>

class UltrasonicControl {
public:
  void initUltrasonicControl();
  int getDistance(int index);
};

#endif