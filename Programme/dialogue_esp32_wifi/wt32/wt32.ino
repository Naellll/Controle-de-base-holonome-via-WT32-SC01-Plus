// IMPORTATIONS
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <LovyanGFX.hpp>

// LOVYAN GFX
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7796 _panel;
  lgfx::Bus_Parallel8 _bus;
  lgfx::Touch_FT5x06 _touch;

public:
  LGFX() {
    auto cfg = _bus.config();
    cfg.freq_write = 20000000;
    cfg.pin_wr = 47;
    cfg.pin_rs = 0;
    cfg.pin_d0 = 9; cfg.pin_d1 = 46; cfg.pin_d2 = 3; cfg.pin_d3 = 8; cfg.pin_d4 = 18; cfg.pin_d5 = 17; cfg.pin_d6 = 16; cfg.pin_d7 = 15;
    _bus.config(cfg);
    _panel.setBus(&_bus);

    auto panel_cfg = _panel.config();
    panel_cfg.pin_rst = 4;
    panel_cfg.panel_width = 320;
    panel_cfg.panel_height = 480;
    _panel.config(panel_cfg);
    setPanel(&_panel);

    auto touch_cfg = _touch.config();
    touch_cfg.i2c_port = 1;
    touch_cfg.pin_sda = 6;  
    touch_cfg.pin_scl = 5;  
    touch_cfg.pin_int = 7;  
    _touch.config(touch_cfg);
  }

  void initTouch() {_touch.init();}

  bool getTouch(int16_t* x, int16_t* y) {
    lgfx::v1::touch_point_t tp;
    bool touch = false;

    if (_touch.getTouchRaw(&tp, 1)){
      *x = tp.y;
      *y = 320-tp.x;
      touch = true;
    }
    return touch;
  }
};

LGFX lcd;

// CONFIGURATION WIFI
const char* ssid = ""; // Nom du Wifi
const char* mdp = ""; // Mot de passe du Wifi

// CONFIGURATION SERVEUR TCP
const int port = 1234; // Port du serveur
WiFiServer serveur(port);
WiFiClient client;

// EXECUTION
void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.initTouch();

  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);

  lcd.setRotation(1);
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  lcd.setTextSize(2);
  lcd.drawString("En attente du WiFi...", 10, 10);

  WiFi.begin(ssid, mdp);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connecté");
  lcd.drawString("WiFi connecte        ", 10, 10);
  lcd.drawString("Adresse IP du serveur : " + WiFi.localIP().toString(), 10, 40);
  Serial.println("Adresse IP du serveur : " + WiFi.localIP().toString());
  lcd.drawString("Port du serveur : " + String(port), 10, 70);
  Serial.println("Port du serveur : " + String(port));


  serveur.begin();
  serveur.setNoDelay(true);
  Serial.println("Serveur TCP démarré");
}

void loop() {
  // Accepter nouveau client
  if (serveur.hasClient()) {
    if (!client || !client.connected()) {
      if (client) {
        client.stop();
      }
      client = serveur.available();
      Serial.println("Client connecté");
      lcd.drawString("Client connecte    ", 10, 100);
    }
  }

  // Lire le toucher
  int16_t x, y;
  if (lcd.getTouch(&x, &y)) {
    Serial.printf("Touché detecté à %d, %d\n", x, y);
    if (client && client.connected()) {
      client.println("Hello");
    }

    delay(300);
    String msg = client.readStringUntil('\n');
    if (msg != "") {
      msg.trim();
      Serial.println("Message reçu : " + msg);
      lcd.drawString("Message recu : " + msg + "   ", 10, 130);
    }else {
      lcd.drawString("Client deconnecte", 10, 100);
      lcd.drawString("                                       ", 10, 130);
    }
    delay(300);
  }
}