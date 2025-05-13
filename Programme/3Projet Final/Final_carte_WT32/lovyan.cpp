// DEPENDANCE
#include <lovyan.h>


// Parametrisation de LovyanGFX
LGFX::LGFX() {
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


// Initialisation du tactile
void LGFX::initTouch() {
  _touch.init();
  }


// Fonction renvoyant les coordonnees de l'appui
bool LGFX::getTouch(int16_t* x, int16_t* y) {
  lgfx::v1::touch_point_t tp;
  bool touch = false;

  if (_touch.getTouchRaw(&tp, 1)){
    *x = 320-tp.x;
    *y = 480-tp.y;
    touch = true;
  }
  return touch;
}


// Initialisation globale de l'ecran
void LGFX::initialiser() {

  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);

  init();
  setRotation(2);
  setColorDepth(16);
  setSwapBytes(true);
  invertDisplay(true);
  initTouch();
}


// Variable correspondant a l'ecran
LGFX lcd;