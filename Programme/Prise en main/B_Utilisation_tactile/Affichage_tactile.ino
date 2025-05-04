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

LGFX lcd;

void dessin(){
  lcd.fillScreen(TFT_WHITE);
  lcd.fillRect(0, 0, 50, 50, TFT_RED);
  lcd.drawLine(10, 10, 40, 40, TFT_WHITE);
  lcd.drawLine(10, 40, 40, 10, TFT_WHITE);
}

void setup() {

  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);

  lcd.init();
  lcd.setRotation(1);
  lcd.setColorDepth(16);
  lcd.setSwapBytes(true);
  lcd.invertDisplay(true);
  dessin();
  lcd.initTouch();
}

void loop() {

  int16_t x, y;

  if (lcd.getTouch(&x, &y)) {
    if (x <= 50 && y <= 50) dessin();
    else lcd.fillCircle(x, y, 8, TFT_BLUE);
  }
  delay(10);
}