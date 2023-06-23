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

#include "TelegramHandler.h"
#include "RelayControl.h"
#include "ApiRelayControl.h"

TelegramHandler::TelegramHandler(UniversalTelegramBot &bot, WiFiClient &client) : _bot(bot),
                                                                                  _client(client),
                                                                                  _arc(NULL),
                                                                                  _rc(NULL),
                                                                                  _uc(NULL)
{
  this->_arc = new ApiRelayControl(_client);
  this->_rc = new RelayControl();
  this->_uc = new UltrasonicControl();
}

void TelegramHandler::initTelegramBot()
{
  Serial.println("Initiating Telegram Bot");
  String connectedMessage;
  connectedMessage += "SINAGA (Sistem Informasi Navigasi Air dan Gerbang Air)\n";
  connectedMessage += "Waduk Gajahduduk Ngamartapura\n";
  connectedMessage += "===============================\n";
  connectedMessage += "Informasi Ketinggian Air\n";
  connectedMessage += "Utara: " + String(_uc->getDistance(0)) + "cm\n";
  connectedMessage += "Selatan: " + String(_uc->getDistance(1)) + "cm\n";
  connectedMessage += "===============================\n";
  connectedMessage += "Status Gerbang Air\n";
  for (int i = 0; i < 4; i++)
  {
    connectedMessage += "Nama: " + _arc->getNameFromApi(i + 1) + "\n";
    if (_arc->getStateFromApi(i + 1))
    {
      connectedMessage += "Kondisi: Terbuka\n";
    }
    else
    {
      connectedMessage += "Kondisi: Tertutup\n";
    }
    connectedMessage += "------------------\n";
  }
  connectedMessage += "Apabila bot tidak merespon, silakan buka gerbang secara manual";

  _bot.sendMessage(_chatID, connectedMessage, "");
}

void TelegramHandler::handleMessages()
{
  int numNewMessages = _bot.getUpdates(_bot.last_message_received + 1);

  while (numNewMessages)
  {
    for (int i = 0; i < numNewMessages; i++)
    {
      String chat_id = String(_bot.messages[i].chat_id);
      if (chat_id != _chatID)
      {
        _bot.sendMessage(chat_id, "User tidak terautentikasi", "");
        continue;
      }
      String text = _bot.messages[i].text;
      handleTelegramCommand(text);
      _bot.last_message_received = _bot.messages[i].update_id + 1;
    }
    numNewMessages = _bot.getUpdates(_bot.last_message_received + 1);
  }
}

void TelegramHandler::setChatID(String chatID)
{
  _chatID = chatID;
}

void TelegramHandler::sendMessage(String text)
{
  _bot.sendMessage(_chatID, text, "");
}

void TelegramHandler::gateHandler(int index, int action)
{
  String actionMsg, gateName;
  if (action != 0)
  {
    actionMsg = "ditutup";
  }
  else
  {
    actionMsg = "dibuka";
  }
  gateName = _arc->getNameFromApi(index);
  if (!_arc->updateRelayState(index, action))
  {
    _bot.sendMessage(_chatID, gateName + " gagal " + actionMsg + ", silakan cek API", "");
  }
  _bot.sendMessage(_chatID, gateName + " berhasil " + actionMsg, "");
}
void TelegramHandler::handleTelegramCommand(String command)
{
  if (command == "/start")
  {
    String welcome = "Selamat datang di Sistem Monitoring Air dan Gerbang Air (SINAGA) Waduk Gajahduduk.\n";
    welcome += "Berikan perintah untuk melaksanakan aksi.\n\n";
    welcome += "/buka_gerbang_utara_1 untuk membuka gerbang utara pertama\n";
    welcome += "/buka_gerbang_utara_2 untuk membuka gerbang utara kedua\n";
    welcome += "/buka_gerbang_selatan_1 untuk membuka gerbang selatan pertama\n";
    welcome += "/buka_gerbang_selatan_2 untuk membuka gerbang selatan kedua\n";
    welcome += "/tutup_gerbang_utara_1 untuk membuka gerbang utara pertama\n";
    welcome += "/tutup_gerbang_utara_2 untuk membuka gerbang utara kedua\n";
    welcome += "/tutup_gerbang_selatan_1 untuk membuka gerbang selatan pertama\n";
    welcome += "/tutup_gerbang_selatan_2 untuk membuka gerbang selatan kedua\n";
    welcome += "/cek_tinggi_air_utara untuk mengecek ketinggian air di gerbang utara\n";
    welcome += "/cek_tinggi_air_selatan untuk mengecek ketinggian air di gerbang selatan\n\n";
    welcome += "Apabila bot tidak merespon, silakan datang dan buka gerbang secara manual karena jika tidak merespon = sensor rusak";
    _bot.sendMessage(_chatID, welcome, "");
  }

  if (command == "/buka_gerbang_utara_1")
  {
    gateHandler(1, 0);
  }

  if (command == "/buka_gerbang_utara_1")
  {
    gateHandler(1, 0);
  }

  if (command == "/tutup_gerbang_utara_1")
  {
    gateHandler(1, 1);
  }

  if (command == "/buka_gerbang_utara_2")
  {
    gateHandler(2, 0);
  }

  if (command == "/tutup_gerbang_utara_2")
  {
    gateHandler(2, 1);
  }

  if (command == "/buka_gerbang_selatan_1")
  {
    gateHandler(3, 0);
  }

  if (command == "/tutup_gerbang_selatan_1")
  {
    gateHandler(3, 1);
  }

  if (command == "/buka_gerbang_selatan_2")
  {
    gateHandler(4, 0);
  }

  if (command == "/tutup_gerbang_selatan_2")
  {
    gateHandler(4, 1);
  }

  if (command == "/cek_tinggi_air_utara")
  {
    _bot.sendMessage(_chatID, "Utara: " + String(670 - _uc->getDistance(0)) + "cm\n", "");
  }

  if (command == "/cek_tinggi_air_selatan")
  {
    _bot.sendMessage(_chatID, "Selatan: " + String(670 - _uc->getDistance(1)) + "cm\n", "");
  }
}
