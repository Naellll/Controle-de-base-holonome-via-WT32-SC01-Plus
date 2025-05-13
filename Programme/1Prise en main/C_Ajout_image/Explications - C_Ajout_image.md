# Premier utilisation du tactile : 
## *B_Affichage_tactile.ino*

&nbsp;&nbsp;&nbsp;&nbsp;Ce programme est fonctionnel sur une carte WT32-SC01 Plus. Il permet d'utiliser la fonction *pushImage()* de la bibliothèque **LovyanGFX**. Ce programme est divisé en plusieurs fichiers .h et .cpp regroupés dans le .ino (main) ce qui permet une meilleure lecture du programme. Il s'agit notamment du procédé utilisé dans le programme final. Je vous renvoie vers ce blog qui explique très bien le principe de cette organisation : [Organiser votre code en fichiers](https://eskimon.fr/tuto-arduino-905-organisez-votre-code-en-fichiers)

&nbsp;&nbsp;&nbsp;&nbsp;Mise à part cette séparation, le programme est assez simple, une image (dans notre cas le logo de l'ENSIBS) à été transformée en C-array qui a ensuite été copié dans le .cpp avec ses dimensions. Il suffit alors de l'afficher à l'aide du *pushImage()*.

&nbsp;&nbsp;&nbsp;&nbsp;Pour le passage en C-array, j'ai utilisé le site [FileToCArray](https://notisrac.github.io/FileToCArray/) dans lequel j'ai ajouté mon image avant de sélectionner dans le *Palette mod* le format **16bit RRRRRGGGGGBBBBB (2byte/pixel)**.

## Exécution

&nbsp;&nbsp;&nbsp;&nbsp;Téléversez le programme sur la carte de développement WT32-SC01 Plus. Une fois cela fait, vous devriez observer au centre de l'écran le logo de l'ENSIBS en dimension 300x162. S'il y a un problème avec les couleurs de l'image cela peut venir du choix du *Palette mod* ou de l'instruction *lcd.setSwapBytes(true);*.

## Auteur
Nathanael DEBREILLY - Github : [@Naellll](https://github.com/Naellll) - E-mail : nathanael.debreilly@gmail.com

## Projet complet : contrôle de base holonome via WT32-SC01 Plus

Lien Github : [Projet](https://github.com/Naellll/Controle-de-base-holonome-via-WT32-SC01-Plus)