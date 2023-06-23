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

#include "RelayControl.h"

#define RELAY_PIN_1 D3
#define RELAY_PIN_2 D4
#define RELAY_PIN_3 D7
#define RELAY_PIN_4 D8

void RelayControl::initRelayControl()
{
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(RELAY_PIN_4, OUTPUT);
  digitalWrite(RELAY_PIN_1, LOW);
  digitalWrite(RELAY_PIN_2, LOW);
  digitalWrite(RELAY_PIN_3, LOW);
  digitalWrite(RELAY_PIN_4, LOW);
  delay(500);
  digitalWrite(RELAY_PIN_1, HIGH);
  digitalWrite(RELAY_PIN_2, HIGH);
  digitalWrite(RELAY_PIN_3, HIGH);
  digitalWrite(RELAY_PIN_4, HIGH);
  delay(500);
  digitalWrite(RELAY_PIN_1, LOW);
  digitalWrite(RELAY_PIN_2, LOW);
  digitalWrite(RELAY_PIN_3, LOW);
  digitalWrite(RELAY_PIN_4, LOW);
}

int RelayControl::controlRelay(int port, int state)
{
  int relayPin;
  if (port == 1)
  {
    relayPin = RELAY_PIN_1;
  }
  else if (port == 2)
  {
    relayPin = RELAY_PIN_2;
  }
  else if (port == 3)
  {
    relayPin = RELAY_PIN_3;
  }
  else
  {
    relayPin = RELAY_PIN_4;
  }
  // Control the relay based on the state value
  if (state == 1)
  {
    digitalWrite(relayPin, HIGH); // Activate relay
  }
  else
  {
    digitalWrite(relayPin, LOW); // Deactivate relay
  }
  return state;
}