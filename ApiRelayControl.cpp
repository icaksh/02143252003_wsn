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

#include "ApiRelayControl.h"

HTTPClient http;

ApiRelayControl::ApiRelayControl(WiFiClient &client) : apiURL("http://hanaemi.my.id"),
                                                       _client(client)
{
}

bool ApiRelayControl::updateRelayState(int relayNumber, int state)
{
  http.begin(_client, apiURL + "/state.php");
  String payload = "{\"gate\":\"" + String(relayNumber) + "\",\"state\":\"" + String(state) + "\"}";
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(payload);
  if (httpCode == HTTP_CODE_OK)
  {
    return 1;
  }
  else
  {
    return 0;
  }
  http.end();
}

bool ApiRelayControl::updateStatus(int index, int height)
{
  http.begin(_client, apiURL + "/status.php");
  String payload = "{\"gate\":\"" + String(index) + "\",\"height\":\"" + String(height) + "\"}";
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(payload);
  if (httpCode == HTTP_CODE_OK)
  {
    return 1;
  }
  else
  {
    Serial.println(httpCode);
    return 0;
  }
  http.end();
}

String ApiRelayControl::getNameFromApi(int relayNumber)
{
  http.begin(_client, apiURL + "/state.php?id=" + relayNumber);
  int httpCode = http.GET();

  String state;

  if (httpCode == HTTP_CODE_OK)
  {
    // Parse JSON response
    DynamicJsonDocument doc(1024);
    String payload = http.getString();
    deserializeJson(doc, payload);

    // Retrieve the state value from JSON
    state = doc["data"][0]["gate_name"].as<String>();
  }
  else
  {
    return "Error";
  }

  // Close the connection
  http.end();

  // Return the state value
  return state;
}

int ApiRelayControl::getStateFromApi(int relayNumber)
{
  http.begin(_client, apiURL + "/state.php?id=" + relayNumber);
  int httpCode = http.GET();

  int state = 0; // Default state value

  if (httpCode == HTTP_CODE_OK)
  {
    // Parse JSON response
    DynamicJsonDocument doc(1024);
    String payload = http.getString();
    deserializeJson(doc, payload);

    // Retrieve the state value from JSON
    state = doc["data"][0]["state"].as<int>();
  }
  else
  {
    return 0;
  }

  // Close the connection
  http.end();

  // Return the state value
  return state;
}
