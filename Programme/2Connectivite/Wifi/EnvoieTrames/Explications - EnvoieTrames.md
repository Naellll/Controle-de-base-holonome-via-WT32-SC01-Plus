# Envoi de trames en WiFi par un serveur TCP : 

## *EnvoieTrames.ino*

> &nbsp;&nbsp;&nbsp;&nbsp;Ce fichier permet de gérer le côté de la carte de développement WT32-SC01 Plus. La carte doit se connecter au réseau WiFi, puis se connecter au serveur TCP mis en place dans le second fichier. Ce programme de la carte affiche quatre carré de différentes couleurs sur l'écran, selon lequel on clique, une certaine trame sous forme de chaîne de caractère sera envoyer au serveur TCP. Ces chaînes de caractères indiquent un mouvement : haut, bas, gauche ou droite.

&nbsp;&nbsp;&nbsp;&nbsp;Pour utiliser ce programme, il est nécessaire que vous ayez pris connaissance du tutoriel pour mettre en place votre espace de travail sous Arduino IDE.

&nbsp;&nbsp;&nbsp;&nbsp;La première étape importante pour la configuration de ce programme est la définition des paramètres du réseau auquel vous voulez vous connecter. Répérez ces lignes de codes au début du programme :

<!-- Syntaxe pour un affichage de type : éditeur de code -->
```bash
const char* ssid = "nom_wifi";
const char* password = "mot_de_passe";
```

&nbsp;&nbsp;&nbsp;&nbsp;Il suffit de remplacer la variable *ssid* par le nom de votre réseau Wi-Fi, et la variable *password* par son mot de passe. Faites attention aux majuscules lors de cette manipulation.

&nbsp;&nbsp;&nbsp;&nbsp;La seconde étape est tout aussi importante, elle servira à correctement se connecter au serveur TCP mis en place dans le fichier *serveur_tcp.py*. Répérez ces lignes de codes à la suite des récédentes :

```bash
const char* host = "adresse_ip";
const uint16_t port = numero_port;
```

&nbsp;&nbsp;&nbsp;&nbsp;Remplacez la variable *host* par l'adresse IP de votre ordinateur sur le réseau auquel il est connecté et la variable *port* par le numéro du port sur lequel vous enverrez les données.

&nbsp;&nbsp;&nbsp;&nbsp;Pour trouver l'adresse IP de l'ordinateur sur le réseau WiFi, exécutez le raccourci *Windows + R*. Tapez *cmd* dans la zone de texte puis cliquez sur *OK* pour ouvrir l'invite de commande. Entrez la commande *ipconfig* et cherchez la ligne *Adresse IPv4* pour trouver l'adresse IP de votre ordinateur.

---
## *serveur_tcp.py*

> &nbsp;&nbsp;&nbsp;&nbsp;Ce fichier permet de créer un serveur TCP avec la bibliothèque *socket* de Python. Il créé aussi un interface graphique avec la bibliothèque *TKinter*. Ce interface est composé d'une grille, et d'un disque rouge qui se déplacera sur cette dernière, en suivant les instructions reçu sur le serveur.

&nbsp;&nbsp;&nbsp;&nbsp;Pour utiliser ce programme, il est nécessaire vous ayez installé Python sur votre ordinateur. Si vous ne l'avez pas, vous pouver télécharger la dernière version [ici](https://www.python.org/downloads/).

&nbsp;&nbsp;&nbsp;&nbsp;De plus, puisque vous allez héberger le serveur TCP sur votre ordinateur, il est nécessaire qu'il soit connecté au même réseau WiFi que la carte de développement. L'adresse IP du serveur sera donc l'adresse de votre ordinateur sur le réseau WiFi.

&nbsp;&nbsp;&nbsp;&nbsp;La seule étape nécessaire pour ce fichier est la définition des paramètres du serveur. Répérez ces lignes de codes au début du programme :

```bash
HOST = "0.0.0.0"
PORT = numero_port
```

&nbsp;&nbsp;&nbsp;&nbsp;Ne touchez pas à la variable *HOST*, car le serveur est hébergé sur l'ordinateur. En revanche définissez la variable *PORT*, il faut qu'elle soit impérativement en adéquation avec la variable *port* sur fichier Arduino.

---

## Exécution

&nbsp;&nbsp;&nbsp;&nbsp;Téléversez le programme sur la carte de développement WT32-SC01 Plus. Une fois cela fait, vous pouvez activer le moniteur série (se référer au tutoriel de pris en main, à la section 2.1) pour avoir des retours du programme.

&nbsp;&nbsp;&nbsp;&nbsp;Débranchez la carte et exécutez le programme Python. Rebranchez la carte pour qu'elle puisse se connecter au serveur. Si la carte est bien connectée au serveur, vous devriez voir des informations sur la connexion dans le terminal Python. Si la connexion est réussie, cliquez sur les différents boutons de la carte, et le disque devrait se déplacer sur l'interface grpahique de votre ordinateur.

<!-- À adapter selon le/les auteur/auteurs -->
## Auteur
Eliez LE HUNSEC - Github : [@EliezLH](https://github.com/EliezLH) - E-mail : eliez.lehunsec.pro@gmail.com


<!-- NE PAS TOUCHER -->
## Projet complet : contrôle de base holonome via WT32-SC01 Plus

Lien Github : [Projet](https://github.com/Naellll/Controle-de-base-holonome-via-WT32-SC01-Plus)
