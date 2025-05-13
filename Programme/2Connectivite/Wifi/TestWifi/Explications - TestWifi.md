# Test connexion WiFi : 
## *TestWifi.ino*

&nbsp;&nbsp;&nbsp;&nbsp;Ce programme est fonctionnel sur une carte WT32-SC01 Plus. Il permet à la carte de développement de se connecter à un réseau WiFi. Ce qui est utile comme point de départ pour un projet basé sur une connectivité WiFi. 

&nbsp;&nbsp;&nbsp;&nbsp;Ce programme est aussi fonctionnel si vous utilisez un hotspot portable (partage de connexion depuis un smartphone).

## Installation

&nbsp;&nbsp;&nbsp;&nbsp;Pour utiliser ce programme, il est nécessaire que vous ayez pris connaissance du tutoriel pour mettre en place votre espace de travail sous Arduino IDE.

&nbsp;&nbsp;&nbsp;&nbsp;La seule étape importante pour la configuration de ce programme est la définition des paramètres du réseau auquel vous voulez vous connecter. Répérez ces lignes de codes au début du programme :

```bash
const char* ssid = "nom_wifi";
const char* password = "mot_de_passe";
```

&nbsp;&nbsp;&nbsp;&nbsp;Il suffit de remplacer la variable *ssid* par le nom de votre réseau Wi-Fi, et la variable *password* par son mot de passe. Faites attention aux majuscules lors de cette manipulation.

## Exécution

&nbsp;&nbsp;&nbsp;&nbsp;Téléversez le programme sur la carte de développement WT32-SC01 Plus. Une fois cela fait, vous pouvez activer le moniteur série (se référer au tutoriel de pris en main, à la section 2.1) pour avoir des retours du programme. 

&nbsp;&nbsp;&nbsp;&nbsp;Si rien ne s'affiche, débranchez puis rebranchez la carte. 

&nbsp;&nbsp;&nbsp;&nbsp;Si des points de suspension continue de s'afficher sans arrêt, c'est que la carte n'arrive pas à se connecter au WiFi. Cela veut dire que soit vous vous êtes trompé dans la définition des paramètres de connexion, soit vous vous situez trop loin de la source du réseau.

## Auteur
Eliez LE HUNSEC - Github : [@EliezLH](https://github.com/EliezLH) - E-mail : eliez.lehunsec@gmail.com

## Projet complet : contrôle de base holonome via WT32-SC01 Plus

Lien Github : [Projet](https://github.com/Naellll/Controle-de-base-holonome-via-WT32-SC01-Plus)
