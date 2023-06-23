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

#ifndef API_RELAY_CONTROL_H
#define API_RELAY_CONTROL_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WifiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

class ApiRelayControl
{
public:
  ApiRelayControl(WiFiClient &client);
  bool updateRelayState(int relayId, int state);
  bool updateStatus(int index, int height);
  int getStateFromApi(int relayNumber);
  String getNameFromApi(int relayNumber);

private:
  String apiURL;
  WiFiClient &_client;
};

#endif
