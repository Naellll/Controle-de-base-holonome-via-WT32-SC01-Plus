#include <WiFi.h>

const char* ssid = "eliez";     // Remplacez par le nom de votre réseau Wi-Fi
const char* password = "123456789";   // Remplacez par votre mot de passe Wi-Fi

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connexion au réseau Wi-Fi
  Serial.println();
  Serial.print("Connexion au réseau Wi-Fi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Attente de la connexion au réseau Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Connecté au réseau Wi-Fi!");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Vous pouvez ajouter des fonctionnalités ici.
}