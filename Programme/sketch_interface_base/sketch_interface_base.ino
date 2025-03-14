#include <LovyanGFX.hpp>

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

/////////////////////////////////////////////////////////////

LGFX lcd;

void ecran1(){
  lcd.fillRect(0, 0, 480, 320, TFT_WHITE);

  // Partie gauche : boutons de choix d'ecran, informations et credits
  lcd.drawLine(80, 0, 80, 80, TFT_BLACK);
  lcd.drawLine(0, 80, 160, 80, TFT_BLACK);
  lcd.drawLine(160, 0, 160, 320, TFT_BLACK);
  lcd.drawLine(0, 280, 160, 280, TFT_BLACK);

  // Rectangle vert du premier ecran
  lcd.fillRect(1, 1, 79, 79, TFT_GREEN);

  // Partie droite : axe directionnels
  lcd.drawLine(280, 10, 360, 10, TFT_BLACK);
  lcd.drawLine(430, 80, 430, 160, TFT_BLACK);
  lcd.drawLine(210, 80, 210, 160, TFT_BLACK);
  lcd.drawLine(280, 230, 360, 230, TFT_BLACK);
  lcd.drawLine(320, 10, 320, 230, TFT_BLACK);
  lcd.drawLine(210, 120, 430, 120, TFT_BLACK);

  // Partie droite : bouton directionnel gauche
  lcd.drawLine(190, 250, 290, 250, TFT_BLACK);
  lcd.drawLine(290, 250, 290, 310, TFT_BLACK);
  lcd.drawLine(290, 310, 190, 310, TFT_BLACK);
  lcd.drawLine(190, 310, 190, 250, TFT_BLACK);

  // Partie droite : bouton directionnel droite
  lcd.drawLine(350, 250, 450, 250, TFT_BLACK);
  lcd.drawLine(450, 250, 450, 310, TFT_BLACK);
  lcd.drawLine(450, 310, 350, 310, TFT_BLACK);
  lcd.drawLine(350, 310, 350, 250, TFT_BLACK);
}

void ecran2(){
  lcd.fillRect(0, 0, 480, 320, TFT_WHITE);

  // Partie gauche : boutons de choix d'ecran, informations et credits
  lcd.drawLine(80, 0, 80, 80, TFT_BLACK);
  lcd.drawLine(0, 80, 160, 80, TFT_BLACK);
  lcd.drawLine(160, 0, 160, 320, TFT_BLACK);
  lcd.drawLine(0, 280, 160, 280, TFT_BLACK);

  // Rectangle vert du premier ecran
  lcd.fillRect(81, 1, 79, 79, TFT_GREEN);

  // Partie droite : axe directionnels
  lcd.drawLine(280, 10, 360, 10, TFT_BLACK);
  lcd.drawLine(430, 80, 430, 160, TFT_BLACK);
  lcd.drawLine(210, 80, 210, 160, TFT_BLACK);
  lcd.drawLine(280, 230, 360, 230, TFT_BLACK);
  lcd.drawLine(320, 10, 320, 230, TFT_BLACK);
  lcd.drawLine(210, 120, 430, 120, TFT_BLACK);

  // Partie droite : bouton directionnel gauche
  lcd.drawLine(190, 250, 290, 250, TFT_BLACK);
  lcd.drawLine(290, 250, 290, 310, TFT_BLACK);
  lcd.drawLine(290, 310, 190, 310, TFT_BLACK);
  lcd.drawLine(190, 310, 190, 250, TFT_BLACK);

  // Partie droite : bouton directionnel droite
  lcd.drawLine(350, 250, 450, 250, TFT_BLACK);
  lcd.drawLine(450, 250, 450, 310, TFT_BLACK);
  lcd.drawLine(450, 310, 350, 310, TFT_BLACK);
  lcd.drawLine(350, 310, 350, 250, TFT_BLACK);
}

void setup() {

  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);

  lcd.init();
  lcd.setRotation(1);
  lcd.setColorDepth(16);
  lcd.setSwapBytes(true);
  lcd.invertDisplay(true);
  ecran1();
  lcd.initTouch();
}

void loop() {

  int16_t x, y;

  if (lcd.getTouch(&x, &y)) {
    if (x <= 80 && y <= 80) ecran1();
    else if (80 <= x <= 160 && y <= 80) ecran2();
  }
  delay(10);
}