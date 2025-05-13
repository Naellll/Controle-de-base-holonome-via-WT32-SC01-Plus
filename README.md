# 🕹️ Contrôle de Base Holonome via WT32-SC01 Plus

Projet pluridisciplinaire PEI-2 

Auteurs : **Ilan CHANY**, **Nathanaël DEBREILLY**, **Eliez LE HUNSEC**

Encadrants : **M. Stéphane BOCHARD**, **M. Philippe GICQUEL**

---

## 📌 Présentation du projet

Ce projet a pour but de développer une **interface homme-machine (IHM)** interactive sur la carte **WT32-SC01 Plus** afin de contrôler une **base robotique holonome**. Le système permet une transmission de commandes de mouvement via **Wi-Fi** ou **Bluetooth (BLE)** entre la carte et la base, à l'aide d'une **passerelle ESP32-C3**.

Le projet se veut **modulaire**, **intuitif**, et facilement utilisable pour des démonstrations publiques, des TP de mécatronique ou dans un contexte domotique.

---

## 🎯 Objectifs

- Concevoir une interface tactile responsive et esthétique.
- Assurer la connectivité entre la WT32-SC01 Plus et le robot via **Wi-Fi ou BLE**.
- Permettre un pilotage fluide des déplacements holonomes.
- Développer des outils réutilisables pour d'autres projets embarqués.

---

## 🧰 Matériel et outils

### 📟 Matériel utilisé

- WT32-SC01 Plus (ESP32-S3)
  - Écran tactile 480x320px
  - 16 MB Flash / 8 MB PSRAM
- ESP32-C3 (passerelle)
- Base robotique holonome à 3 roues
- Alimentation externe / batterie
- PC pour le développement

### 🧪 Bibliothèques & Logiciels

- **Arduino IDE** avec core `esp32`
- **LovyanGFX** pour l'IHM graphique
- **BLE Arduino** pour le Bluetooth
- **WiFi.h** pour la connectivité TCP
- **STM32CubeMX** (logiciel sur lequel est programmé la base holonome)
- **Tkinter** (interface Python côté PC pour les tests)

---

## 🖼️ Interfaces utilisateur (IHM)

L'IHM principale est conçue en **mode vertical** pour une meilleure prise en main :

- Un cercle central pour indiquer la direction et la vitesse du déplacement.
- Affichage des vitesses en X et Y en temps réel.
- Informations sur la connexion et mode actif (Wi-Fi / Bluetooth).
- Interface simple avec retour visuel immédiat.

---

## 🔗 Connectivité

Deux modes de communication avec la base :

### 🌐 Wi-Fi (TCP)
- Connexion via un point d’accès partagé (PC ou smartphone).
- La WT32-SC01 Plus agit comme un client TCP.
- Transmission de trames de commandes structurées.

### 📶 Bluetooth BLE
- La WT32 agit comme serveur BLE.
- Connexion directe avec smartphone via l’app nRF Connect.
- Trames envoyées selon l'interaction utilisateur.

---

## 📐 Structure des données

```cpp
typedef struct {
  int8_t vitesseX;
  int8_t vitesseY;
  uint8_t fonction; // ex : arrêt, mise en marche...
} Commande;

union {
  Commande donnees;
  uint8_t trame[sizeof(Commande)];
} TrameCommande;
```
---

## ✏️ Auteurs

Eliez LE HUNSEC - Github : [@EliezLH](https://github.com/EliezLH) - E-mail : eliez.lehunsec.pro@gmail.com

Nathanaël DEBREILLY - Github : [@Naellll](https://github.com/Naellll) - E-mail : nathanael.debreilly@gmail.com

Ilan CHANY - Github : [@IcanChan](https://github.com/IcanChan) - E-mail : chany.e2301851@etud.univ-ubs.fr
