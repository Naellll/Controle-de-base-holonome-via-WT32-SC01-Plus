#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>


#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"  // UUID unique du service
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"  // UUID unique de la caractéristique



BLEServer* pServer = nullptr;
BLECharacteristic* pCharacteristic = nullptr;
bool deviceConnected = false;



class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) override {
    deviceConnected = true;
    Serial.println("Connecté");
  }

  void onDisconnect(BLEServer* pServer) override {
    deviceConnected = false;
    delay(500);
    Serial.println("Déconnecté. Attente avant redémarrage pub...");
    pServer->getAdvertising()->start();  // Redémarrer la recherche de connection BLE
  }
};


void setup() {
  Serial.begin(115200);
  
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);

  // Initialisation de BLE
  BLEDevice::init("XIAO ESP32C3");

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

  pCharacteristic->setValue("Pas encore d'information");

  pService->start();
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  delay(100);
  pAdvertising->start(); // Commence à annoncer le service BLE

}


void loop() {

  String Value = pCharacteristic->getValue();
  
  if (Value == "Droite"){
    Serial.println("Tu dois aller à droite");
  }
  else if (Value == "Gauche"){
    Serial.println("Tu dois aller à gauche");
  }
  else{
    Serial.println("Tu ne dois rien faire");
  }

  Serial.println(Value);
  delay(100);
}
