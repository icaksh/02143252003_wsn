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

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

#include <WifiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "ApiRelayControl.h"
#include "RelayControl.h"
#include "TelegramHandler.h"
#include "UltrasonicControl.h"

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

// Wi-Fi credentials
const char* WIFI_SSID = "SSID";
const char* WIFI_PASSWORD = "PASSWORD";

// Telegram bot token and chat ID
#define BOT_TOKEN "BOT_TOKEN"
#define CHAT_ID "CHAT_ID"

WiFiClientSecure client;

WiFiClient iClient;
UniversalTelegramBot bot(BOT_TOKEN, client);
TelegramHandler telegramHandler(bot, iClient);
RelayControl rc;
ApiRelayControl arc(iClient);
UltrasonicControl uc;

void setup() {
  Serial.begin(115200);
  client.setInsecure();
  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  #endif
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to Wi-Fi!");
  Serial.println(WiFi.localIP());
  rc.initRelayControl();
  uc.initUltrasonicControl();
  telegramHandler.setChatID(CHAT_ID);
  telegramHandler.initTelegramBot();
}

void loop() {
  telegramHandler.handleMessages();
  int state[4];
  for (int i = 1; i < 5; i++)
  {
    state[i-1] = arc.getStateFromApi(i);
    Serial.println("Relay " + String(i) + ": "+String(rc.controlRelay(i, state[i-1])));
    // Serial.println("Nama: "+ arc.getNameFromApi(i));
  }
  int depth = 670;
  int waterHeightNorth = depth-uc.getDistance(0);
  int waterHeightSouth = depth-uc.getDistance(1);
  if(!arc.updateStatus(1,waterHeightNorth)){
    Serial.println("Tidak dapat mengupdate status Gerbang Utara");
  }
  if(!arc.updateStatus(3,waterHeightSouth)){
    Serial.println("Tidak dapat mengupdate status Gerbang Selatan");
  }

  // Serial.print("Sensor Reading N: "+ String(uc.getDistance(0)));
  // Serial.println("   Sensor Reading S: "+ String(uc.getDistance(1)));
  // Serial.println("North Water Height: " + String(waterHeightNorth));
  // Serial.println("South Water Height: " + String(waterHeightSouth));
  if(waterHeightNorth > 600){
      arc.updateRelayState(1,0);
      arc.updateRelayState(2,0);
  }
  if(waterHeightSouth > 600){
      arc.updateRelayState(3,0);
      arc.updateRelayState(4,0);
  }
}
