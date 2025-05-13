#include <LovyanGFX.hpp>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "12345678-1234-5678-1234-56789abcdef0"  // UUID unique du service
#define CHARACTERISTIC_UUID "87654321-4321-6789-4321-fedcba987654"  // UUID unique de la caractéristique

BLEServer* pServer = nullptr;
BLECharacteristic* pCharacteristic = nullptr;
bool deviceConnected = false;

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
    cfg.pin_d0 = 9; cfg.pin_d1 = 46; cfg.pin_d2 = 3; cfg.pin_d3 = 8; 
    cfg.pin_d4 = 18; cfg.pin_d5 = 17; cfg.pin_d6 = 16; cfg.pin_d7 = 15;
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

void Button(){
  lcd.fillScreen(TFT_PINK);
  lcd.fillRect(0, 0, 240, 320, TFT_PURPLE);
  lcd.setCursor(60,160);
  lcd.print("Gauche");
  lcd.setCursor(300,160);
  lcd.print("Droite");
}

void deconnecte(){
  lcd.fillScreen(TFT_RED);
  lcd.setCursor(50, 50);
  lcd.print("BLE Disconnected");
}

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) override {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) override {
    deviceConnected = false;
    pServer->getAdvertising()->start();  // Redémarrer la recherche de connection BLE
  }
};

void setup() {
  Serial.begin(115200);
  
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);

  //Interface pendant le démarage  
  lcd.init();
  lcd.setRotation(1);
  lcd.setColorDepth(16);
  lcd.setSwapBytes(true);
  lcd.invertDisplay(true);
  lcd.fillScreen(TFT_WHITE);
  lcd.setTextColor(TFT_BLACK, TFT_YELLOW);
  lcd.setTextSize(3);
  lcd.setCursor(100, 140);
  lcd.print("Setup BLE...");

  // Initialisation de BLE
  BLEDevice::init("WT32-SC01 plus");

  // Création du serveur BLE
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Création du service BLE
  BLEService* pService = pServer->createService(SERVICE_UUID);

  // Création de la caractéristique BLE (Lecture/Écriture)
  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->addDescriptor(new BLE2902());  // Permet la notification

  pService->start();
  pServer->getAdvertising()->start();  // Commence à annoncer le service BLE

  //Interface quand c'est prêt
  lcd.fillScreen(TFT_BLUE);
  lcd.setCursor(100, 140);
  lcd.print("BLE Ready");
  lcd.initTouch();
}

void loop() {
  int16_t x, y;

  if (deviceConnected) {
    Button();
  }

  while (deviceConnected) {
    if (lcd.getTouch(&x, &y)) {

      if (x <= 240){
        pCharacteristic->setValue("Va à gauche");
        pCharacteristic->notify();  // Notifier le client BLE
      }else{
        pCharacteristic->setValue("Va à droite");
        pCharacteristic->notify();  // Notifier le client BLE
      }
    }
    delay(50);
  }
  deconnecte();
}


