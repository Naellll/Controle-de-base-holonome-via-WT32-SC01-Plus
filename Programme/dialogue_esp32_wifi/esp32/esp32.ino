// IMPORTATION
#include <WiFi.h>

// CONFIGURATION WIFI
const char* ssid = ""; // Nom du Wifi
const char* mdp = ""; // Mot de passe du Wifi

// CONFIGURATION SERVEUR
const char* host = ""; // Adresse IP du serveur
const uint16_t port = 1234; // Port du serveur

WiFiClient client;

// EXECUTION
void setup() {
  Serial.begin(115200);
  Serial.println("Démarrage ESP32...");
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

  int16_t i = 0;
}

void loop() {
  if (client.connected() && client.available()) {
    // Lecture du message reçu
    String msg = client.readStringUntil('\n');
    // Pour enlever les espaces
    msg.trim();

    // Change de message à envoyer une fois sur deux
    if (msg == "Hello") {
      if (i % 2 == 0) {
        client.println("Bonjour !");
      }else {
        client.println("Hola !");
      }
      i = i + 1;
    }
  }
}
