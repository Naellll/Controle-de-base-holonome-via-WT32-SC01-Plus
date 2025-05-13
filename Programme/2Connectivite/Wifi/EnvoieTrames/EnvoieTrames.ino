// CONSTANTES
const char* ssid = "nom_wifi";
const char* password = "mot_de_passe";

const char* host = "adresse_ip";
const uint16_t port = numero_port;

// IMPORTATIONS
#include <LovyanGFX.hpp>
#include <WiFi.h>

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

///////////////////////////////////////////////////////////////////////////////

LGFX lcd;

WiFiClient serveur;

void dessin(){
  lcd.fillScreen(TFT_WHITE);                   // Fond d'écran en blanc
  lcd.fillRect(190, 10, 100, 100, TFT_RED);    // Carre Haut
  lcd.fillRect(290, 110, 100, 100, TFT_BLUE);  // Carre Droite
  lcd.fillRect(190, 210, 100, 100, TFT_GREEN); // Carre Bas
  lcd.fillRect(90, 110, 100, 100, TFT_BLACK);  // Carre Gauche
  //lcd.drawLine(10, 10, 40, 40, TFT_WHITE);
  //lcd.drawLine(10, 40, 40, 10, TFT_WHITE);
}

void setup() {
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);
  Serial.begin(115200);

  // Connexion Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connexion au Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Affiche les informations de la connexion dans le moniteur série
  Serial.println("\nWi-Fi connecté !");
  Serial.print("Adresse IP ESP32 : ");
  Serial.println(WiFi.localIP());

  // Connexion au serveur Python
  Serial.printf("Connexion au serveur %s : %d ...\n", host, port);
  if (serveur.connect(host, port)) {
    Serial.println("Connecté au serveur !");
    serveur.println("connexion"); // Envoi de données
  } else {
    Serial.println("Échec de connexion.");
  }

  //// Affichage ///////
  lcd.setRotation(1);
  lcd.init();
  lcd.setColorDepth(16);
  lcd.setSwapBytes(true);
  lcd.invertDisplay(true);
  dessin();
  lcd.initTouch();
}

void loop() {

  int16_t x, y;

  if (serveur.connected() && lcd.getTouch(&x, &y)) {
    if (190 <= x && x <= 290 && 10 <= y && y <= 110){          // Carre Haut
      // Retour dans le moniteur série
      Serial.printf("Touch: x=%d, y=%d\n", x, y);
      // Envoi la chaîne de caractère au serveur
      serveur.println("haut");
    }else if (290 <= x && x <= 390 && 110 <= y && y <= 210){   // Carre Droite
      Serial.printf("Touch: x=%d, y=%d\n", x, y);
      serveur.println("droite");
    }else if (190 <= x && x <= 290 && 210 <= y && y <= 310){   // Carre Bas
      Serial.printf("Touch: x=%d, y=%d\n", x, y);
      serveur.println("bas");
    }else if (90 <= x && x <= 190 && 110 <= y && y <= 210){    // Carre Gauche
      Serial.printf("Touch: x=%d, y=%d\n", x, y);
      serveur.println("gauche");
    }
  }
  // Délai pour ne pas surcharger le serveur
  delay(100);
}
