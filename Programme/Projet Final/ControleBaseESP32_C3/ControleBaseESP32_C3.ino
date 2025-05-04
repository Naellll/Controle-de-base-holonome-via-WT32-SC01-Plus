// IMPORTATION
#include <WiFi.h>

// CONFIGURATION WIFI
const char* ssid = "wt324life"; // Nom du Wifi
const char* mdp = "gastonbanane"; // Mot de passe du Wifi

// CONFIGURATION SERVEUR
const char* host = "192.168.43.61"; // Adresse IP du serveur
const uint16_t port = 1234; // Port du serveur
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

// EXECUTION
void setup() {
  Serial.begin(115200);
  Serial.println("Démarrage ESP32...");

  robot_serial.begin(115200, SERIAL_8N1, 20, 21);

  // Attente d'une connexion au WIFI
  WiFi.begin(ssid, mdp);
  Serial.print("Connexion au WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connecté");
  Serial.println("IP locale : " + WiFi.localIP().toString());


  // Attente de la connnexion au serveur
  Serial.printf("Connexion au serveur %s : %d...\n", host, port);
  if (client.connect(host, port)) {
    Serial.println("Connecté au serveur !");
  } else {
    Serial.println("Échec de connexion au serveur.");
  }
}

void loop() {
  if (client.connected() && client.available()>= 7) {
    // Lecture du message reçu
    client.readBytes((uint8_t*)&data, 7);

    // Envoi des 7 octets binaires sur le port série secondaire
    robot_serial.write(data.DataSerial, 7);

    Serial.print("Vitesse X : ");
    Serial.println(data.ConsigneBase.VitesseX);
    Serial.print("Vitesse Y : ");
    Serial.println(data.ConsigneBase.VitesseY);
    Serial.print("Fonction : ");
    Serial.println(data.ConsigneBase.Fct);
    Serial.println();  // Saut de ligne
    // Affichage des 7 octets envoyés dans le moniteur série
    Serial.print("DataSerial: ");
    for (int i = 0; i < 7; i++) {
      Serial.print(data.DataSerial[i]);
      Serial.print(" ");
    }
    Serial.println("\n----------------------\n");
  }
}
