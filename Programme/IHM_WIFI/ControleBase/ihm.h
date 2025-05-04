#ifndef IHM_H
#define IHM_H

// BIBLIOTHEQUES
#include "lovyan.h"
#include <WiFi.h>


// CONSTANTES EXTERIEURES
extern const char* ssid;
extern const char* mdp;
extern const int VITESSE_MAX_ROBOT;
extern WiFiServer serveur;
extern const int port;
extern int16_t x_fleche;
extern int16_t y_fleche;
extern float distance;


// FONCTIONS
void gestionTactile(int xp, int yp);

void afficherChargement(int etape);

void transitionVersIHM();

void affichageIHM();

void actualiserIHM();

#endif