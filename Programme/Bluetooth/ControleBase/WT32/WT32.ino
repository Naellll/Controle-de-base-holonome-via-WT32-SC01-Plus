#include "BLEDevice.h"  //#include "BLEScan.h"
#include <LovyanGFX.hpp>

static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b"); // The remote service we wish to connect to.
static BLEUUID charUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"); // The characteristic of the remote service we are interested in.



static boolean doConnect = false; //indique qu'on a trouvé un périphérique à se connecter
static boolean connected = false; //indique qu'on est connecté
static boolean doScan = false; //indique qu'on doit relancer un scan BLE
static BLERemoteCharacteristic *pRemoteCharacteristic; //pointeur vers la caractéristique distante
static BLEAdvertisedDevice *myDevice; //pointeur vers le périphérique BLE trouvé



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

static void notifyCallback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify) {
  Serial.print("Notify callback for characteristic ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
  Serial.print("data: ");
  Serial.write(pData, length);
  Serial.println();
}



class MyClientCallback : public BLEClientCallbacks {  //gère connexions/déconnexions
  void onConnect(BLEClient *pclient) {}

  void onDisconnect(BLEClient *pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};



bool connectToServer() {
  Serial.print("Etablir une connexion avec ");
  Serial.println(myDevice->getAddress().toString().c_str()); //Adresse MAC de l'appareil

  BLEClient *pClient = BLEDevice::createClient(); //Création du client BLE
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback()); //Attche la classe qui permet de gérer les connexions et déconnexions

  pClient->connect(myDevice);  
  Serial.println(" - Connected to server"); //Se connect
  pClient->setMTU(400);  //Passe le MTU de 23 octets (valeur de base) à 517 octets (valeur maximale)

  BLERemoteService *pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) { //Si l'appareil n'a pas de service UUID, on se déconnecte
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr) { //Si l'appareil n'a pas de caractéristique UUID, on se déconnecte
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our characteristic");


  // Read the value of the characteristic.
  if (pRemoteCharacteristic != nullptr && pRemoteCharacteristic->canRead()) {
    String value = pRemoteCharacteristic->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());
  }


  if (pRemoteCharacteristic->canNotify()) {
    pRemoteCharacteristic->registerForNotify(notifyCallback);
  }


  connected = true;
  return true;
}


class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice); //On met un pointeur sur ce périphérique pour le sauvergarder 
      doConnect = true;
      doScan = true;
    }  
  }  
}; 



void setup() {

  Serial.begin(115200);

  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);

  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init(""); //Initialise le stack BLE de l'ESP32.

  BLEScan *pBLEScan = BLEDevice::getScan(); //On initailise le scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks()); //On appelle onResult pour chaque appareil trouvé
  pBLEScan->setInterval(1349); //Définit la période entre deux scans BLE (en unités de 0.625 ms), soit ici ≈ 843 ms.
  pBLEScan->setWindow(449); //Durée pendant laquelle l’ESP32 écoute activement pendant chaque intervalle (≈ 281 ms ici).
  pBLEScan->setActiveScan(true); //Quand activé, permet d'obtnir plus d'information lors du scan (nom, ...)
  pBLEScan->start(15, false); //Scan pendant 5s 

  lcd.init();
  lcd.setRotation(1);
  lcd.setColorDepth(16);
  lcd.setSwapBytes(true);
  lcd.invertDisplay(true);
  lcd.setTextSize(3);
  lcd.fillScreen(TFT_PINK);
  lcd.fillRect(0, 0, 240, 320, TFT_PURPLE);
  lcd.setCursor(60,160);
  lcd.print("Gauche");
  lcd.setCursor(300,160);
  lcd.print("Droite");
  lcd.initTouch();
} 



void loop() {

  int16_t x, y;

  if (doConnect == true) {  //doConnect est changer par onResult dans la class MyAdvertisedDeviceCallbacks
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothing more we will do.");
    }
    doConnect = false;
  }

  if (connected) {
    if (lcd.getTouch(&x, &y)) {
      if (x <= 240){
        pRemoteCharacteristic->writeValue("Gauche");
      }else{
        pRemoteCharacteristic->writeValue("Droite");
      }
    }
  } 
  else if (doScan) {
    BLEDevice::getScan()->start(0);  
  }
  delay(50);  
}