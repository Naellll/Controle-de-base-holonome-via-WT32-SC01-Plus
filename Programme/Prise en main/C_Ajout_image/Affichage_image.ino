#include <LovyanGFX.hpp>
#include "image.h"


class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7796 _panel;
  lgfx::Bus_Parallel8 _bus;


public:
  LGFX() {
    // Configuration du bus parallèle 8 bits (mode 8080)
    auto cfg = _bus.config();
    cfg.freq_write = 20000000;
    cfg.pin_wr = 47;
    cfg.pin_rs = 0;
    cfg.pin_d0 = 9; cfg.pin_d1 = 46; cfg.pin_d2 = 3; cfg.pin_d3 = 8; cfg.pin_d4 = 18; cfg.pin_d5 = 17; cfg.pin_d6 = 16; cfg.pin_d7 = 15;
    _bus.config(cfg);
    _panel.setBus(&_bus);

    // Configuration du panneau LCD ST7796
    auto panel_cfg = _panel.config();
    panel_cfg.pin_rst = 4;
    panel_cfg.panel_width = 320;
    panel_cfg.panel_height = 480;
    _panel.config(panel_cfg);
    setPanel(&_panel);
  }
};


void setup() {
  LGFX lcd;
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);

  lcd.init();
  lcd.setRotation(1);
  lcd.setColorDepth(16);
  lcd.setSwapBytes(true);
  lcd.invertDisplay(true);

  lcd.fillScreen(TFT_WHITE);
  lcd.pushImage(10, 10, imageWidth, imageHeight, image_data);
}


void loop(){

}