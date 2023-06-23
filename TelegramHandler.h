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

#ifndef TELEGRAM_HANDLER_H
#define TELEGRAM_HANDLER_H

#include <Arduino.h>
#include <UniversalTelegramBot.h>
#include <WifiClientSecure.h>
#include "ApiRelayControl.h"
#include "RelayControl.h"
#include "UltrasonicControl.h"

class TelegramHandler
{
public:
  TelegramHandler(UniversalTelegramBot &bot, WiFiClient &client);
  void initTelegramBot();
  void setChatID(String chatID);
  void sendMessage(String text);
  void handleTelegramCommand(String command);
  void handleMessages();

private:
  void gateHandler(int index, int action);
  UniversalTelegramBot &_bot;
  WiFiClient &_client;
  String _chatID;
  ApiRelayControl *_arc;
  RelayControl *_rc;
  UltrasonicControl *_uc;
};

#endif
