// IMPORTATION
#include <WiFi.h>

// CONFIGURATION WIFI
const char* ssid = "nom_wifi"; // Nom du Wifi
const char* mdp = "mot_de_passe"; // Mot de passe du Wifi

// CONFIGURATION SERVEUR
const char* host = "adresse_serveur"; // Adresse IP du serveur
const uint16_t port = port_serveur; // Port du serveur

WiFiClient client;

// STRUCTURE DE DONNÉE
struct __attribute__((packed)) ConsigneBase {
  uint8_t Condition;
  int16_t VitesseX;
  int16_t VitesseY;
  uint8_t Fct;
  uint8_t sept;
};

typedef union {
  uint8_t DataSerial[7];
  struct ConsigneBase ConsigneBase;
} DataBase;

// VARIABLES GLOBALES
HardwareSerial robot_serial(1);
DataBase data;
unsigned long essaiConnexionPrecedent = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Démarrage ESP32...");

  robot_serial.begin(115200, SERIAL_8N1, 20, 21);

  // Connexion au WiFi
  WiFi.begin(ssid, mdp);
  Serial.print("Connexion au WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connecté");
  Serial.println("IP locale : " + WiFi.localIP().toString());

  // Tentative initiale de connexion au serveur
  connexionServeur();
}

void loop() {
  static unsigned long dernierTest = 0;

  // Vérifier toutes les 2 secondes
  if (millis() - dernierTest > 2000) {
    dernierTest = millis();

    // Connexion perdue (TCP cassé ou serveur débranché)
    if (!client.connected()) {
      Serial.println("Connexion perdue, tentative de reconnexion...");
      client.stop(); // Nettoie la socket
      connexionServeur(); // Re-tente une connexion
    } else {
      // Même si connecté, on teste si le serveur répond encore
      client.write((uint8_t)0x00); // Envoi d’un byte neutre (heartbeat)
      if (!client.connected()) {
        Serial.println("Serveur ne répond plus, reconnexion forcée...");
        client.stop();
        connexionServeur();
      }
    }
  }

  // Si connecté, lire les données si disponibles
  if (client.connected() && client.available() >= 7) {
    client.readBytes((uint8_t*)&data, 7);
    robot_serial.write(data.DataSerial, 7);

    // Debug
    Serial.printf("X: %d | Y: %d | Fct: %d\n",
      data.ConsigneBase.VitesseX,
      data.ConsigneBase.VitesseY,
      data.ConsigneBase.Fct
    );
  }
}

void connexionServeur() {
  Serial.printf("Connexion au serveur %s : %d...\n", host, port);
  if (client.connect(host, port)) {
    Serial.println("Connecté au serveur !");
  } else {
    Serial.println("Échec de connexion au serveur.");
  }
}
