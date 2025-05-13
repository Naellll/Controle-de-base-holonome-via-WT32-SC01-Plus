# Projet Final en WiFi : 

## *ControleBaseESP32_C3.ino* :

&nbsp;&nbsp;&nbsp;&nbsp;Ce répertoire comprend le fichier Arduino à téléverser sur une carte ESP32-C3. Cette carte fait le lien entre le WT32-SC01 Plus et la carte de commande de la base holonome. L'ESP32-C3 va se connecter au réseau WiFi défini dans son code, puis cherchera à se connecter à un serveur en TCP hébergé par la carte WT32-SC01 Plus. Des donnnées seront transmises depuis cette dernière et l'ESP32 transmettra les mêmes informations par une liaison série.

&nbsp;&nbsp;&nbsp;&nbsp;Pour utiliser ce programme, il est nécessaire que vous ayez pris connaissance du tutoriel pour mettre en place votre espace de travail sous Arduino IDE.

&nbsp;&nbsp;&nbsp;&nbsp;Vous pouvez ensuite ouvrir le fichier La première étape importante pour la configuration de ce programme est la définition des paramètres du réseau auquel vous voulez vous connecter. Répérez ces lignes de codes au début du programme :

```bash
const char* ssid = "nom_wifi";
const char* mdp = "mot_de_passe";
```

&nbsp;&nbsp;&nbsp;&nbsp;Il suffit de remplacer la variable *ssid* par le nom de votre réseau Wi-Fi, et la variable *password* par son mot de passe. Faites attention aux majuscules lors de cette manipulation.

&nbsp;&nbsp;&nbsp;&nbsp;La seconde étape est tout aussi importante, elle servira à correctement se connecter au serveur TCP mis en place par la carte de développement WT32-SC01 Plus :

```bash
const char* host = "adresse_serveur";
const uint16_t port = port_serveur;
```

&nbsp;&nbsp;&nbsp;&nbsp;Remplacez la variable *host* par l'adresse IP de votre ordinateur sur le réseau auquel il est connecté et la variable *port* par le numéro du port sur lequel vous enverrez les données.

---

## Exécution

&nbsp;&nbsp;&nbsp;&nbsp;Téléversez le programme sur le contrôleur ESP32-C3. Une fois cela fait, vous pouvez le brancher à la carte de commande de la base holonome.

&nbsp;&nbsp;&nbsp;&nbsp;Ensuite connectez le WT32-SC01 Plus (après avoir suivi les instructions pour son fichier), et vous devriez être capable de piloter la base.

## Auteurs
Nathanaël DEBREILLY - Github : [@Naellll](https://github.com/Naellll) - E-mail : eliez.lehunsec.pro@gmail.com

Eliez LE HUNSEC - Github : [@EliezLH](https://github.com/EliezLH) - E-mail : nathanael.debreilly.pro@gmail.com

Ilan CHANY - Github : [@IcanChan](https://github.com/IcanChan) - E-mail : chany.e2301851@etud.univ-ubs.fr


<!-- NE PAS TOUCHER -->
## Projet complet : contrôle de base holonome via WT32-SC01 Plus

Lien Github : [Projet](https://github.com/Naellll/Controle-de-base-holonome-via-WT32-SC01-Plus)
