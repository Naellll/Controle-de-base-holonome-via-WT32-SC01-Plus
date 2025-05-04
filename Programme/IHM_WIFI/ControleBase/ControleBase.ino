// DEPENDANCES
#include "ihm.h"      // Fichier gerant la partie IHM
#include "lovyan.h"   // Fichier gerant la parametrisation de LovyanGFX (gestion de l'ecran et du tactile)

// BIBLIOTHEQUES
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

// PARAMETRES (A ADAPTER)
const char* ssid = "wt324life";       // Nom du Wifi
const char* mdp = "gastonbanane";     // Mot de passe du Wifi
const int VITESSE_MAX_ROBOT = 400;    // Vitesse maximale du robot (ne pas depasser 450)
const int DELAIS_ENVOI_DONNEE = 25;   // Le delais d'envoi sera de DELAIS_ENVOI_DONNEE * 20 (en ms)


// STRUCTURES DE DONNEES
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
int16_t x, y, x_fleche = 0, y_fleche = 0, cmpt = 0;
float distance;
DataBase commande;


// CONFIGURATION DU SERVEUR TCP
const int port = 1234;
WiFiServer serveur(port);
WiFiClient client;


// PROGRAMME PRINCIPAL
void setup() {

  lcd.initialiser();

  commande.ConsigneBase.Condition = 1;
  commande.ConsigneBase.sept = 1;
  commande.ConsigneBase.Fct = 1;

  // Connexion au Wifi
  WiFi.begin(ssid, mdp);
  while (WiFi.status() != WL_CONNECTED) {
    afficherChargement(cmpt++);
    delay(150);
    Serial.print(". ");
  }

  // Creation du serveur TCP
  serveur.begin();
  serveur.setNoDelay(true);

  // Affichage de l'IHM
  transitionVersIHM();
  affichageIHM();
}


void loop() {

  // Accepter nouveau client
  if (serveur.hasClient()) {
    if (!client || !client.connected()) {
      if (client) {
        client.stop();
      }
      client = serveur.available();
    }
  }

  // Gestion du tactile
  if (lcd.getTouch(&x, &y)) {
    gestionTactile(x, y);
    actualiserIHM();
  }

  // Envoie des informations a la base toute les 500ms (cmpt >= 25 et delay(20) )
  if (cmpt >= DELAIS_ENVOI_DONNEE && client && client.connected()) {
    cmpt = 0;
    if (distance <= 22){
      commande.ConsigneBase.VitesseX = x_fleche;
      commande.ConsigneBase.VitesseY = y_fleche;
    }
    else{
      commande.ConsigneBase.VitesseX = int((VITESSE_MAX_ROBOT*(x_fleche-160))/160);
      commande.ConsigneBase.VitesseY = int((VITESSE_MAX_ROBOT*(160-y_fleche))/160);
    }
    client.write((uint8_t*)&commande, 7);
  }

  delay(20);
  cmpt += 1;
}