# Projet Final en WiFi : 

## *ControleBaseWT32.ino* :

&nbsp;&nbsp;&nbsp;&nbsp;Ce répertoire comprend le fichier Arduino à téléverser sur une carte de développement WT32-SC01 Plus. Il contient également d'autres fichiers qui permettent d'alléger la lecture du code du programme principal. Un de ses fichier sert à mettre en place la bibliothèque pour gérer l'interface homme-machine (IHM). Tandis qu'un seconde permet de générer cet IHM. La gestion des fichier .h et .cpp est expliquée dans le document explicatif du programme de prise en main : C_Afficahge_image.cpp.

&nbsp;&nbsp;&nbsp;&nbsp;Le WT32-SC01 Plus hébergera un serveur TCP sur lequel un ESP32 se connectera pour recevoir les différentes commandes émises. Ces commandes sont en réalité une structure de donnée *C* qui comprend les vitesses en X et Y, une fonction, et deux autres octets pour contrôler l'intégrité des trames.

&nbsp;&nbsp;&nbsp;&nbsp;Pour utiliser ce programme, il est nécessaire que vous ayez pris connaissance du tutoriel pour mettre en place votre espace de travail sous Arduino IDE.

&nbsp;&nbsp;&nbsp;&nbsp;Vous pouvez ensuite ouvrir le fichier *ControleBaseWT32.ino*. La première étape importante pour la configuration de ce programme est la définition des paramètres du réseau auquel vous voulez vous connecter. Répérez ces lignes de codes au début du programme :

```bash
const char* ssid = "nom_wifi";
const char* mdp = "mot_de_passe";
```

&nbsp;&nbsp;&nbsp;&nbsp;Il suffit de remplacer la variable *ssid* par le nom de votre réseau Wi-Fi, et la variable *password* par son mot de passe. Faites attention aux majuscules lors de cette manipulation.

&nbsp;&nbsp;&nbsp;&nbsp;La seconde étape est facultative, elle permet d'initialiser des variables du programme. Répérez les lignes suivantes :

```bash
const int VITESSE_MAX_ROBOT = 250;
const int DELAIS_ENVOI_DONNEE = 25;
```

&nbsp;&nbsp;&nbsp;&nbsp;La variable *VITESSE_MAX_ROBOTS* ne doit pas dépasser les 400 sans endommager le matériel. Le contrôle de base n'est pas très précis, si la vitesse n'est pas très élevé il y aura moins d'erreurs. La seconde variable est le délai avant l'envoi de données, il faut le multiplier par 20 pour avoir le délai en milisecondes. Il ne faut pas que cette variable ne soit trop faible pour ne pas surcharger les autres cartes à cause des délais de propagation.

---

## Exécution

&nbsp;&nbsp;&nbsp;&nbsp;Téléversez le programme sur votre WT32-SC01 Plus. Une fois cela fait, vous pouvez l'alimenter à condition que l'ESP32 le soit aussi, et branché sur la base holonome. Vous devriez maintenant être capable de contrôler la base holonome avec votre carte WT32-SC01 Plus.

## Auteurs
Eliez LE HUNSEC - Github : [@EliezLH](https://github.com/EliezLH) - E-mail : eliez.lehunsec.pro@gmail.com

Nathanaël DEBREILLY - Github : [@Naellll](https://github.com/Naellll) - E-mail : nathanael.debreilly@gmail.com

Ilan CHANY - Github : [@IcanChan](https://github.com/IcanChan) - E-mail : chany.e2301851@etud.univ-ubs.fr

## Projet complet : contrôle de base holonome via WT32-SC01 Plus

Lien Github : [Projet](https://github.com/Naellll/Controle-de-base-holonome-via-WT32-SC01-Plus)
