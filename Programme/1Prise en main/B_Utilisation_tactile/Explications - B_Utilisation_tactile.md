# Premier utilisation du tactile : 
## *B_Affichage_tactile.ino*

&nbsp;&nbsp;&nbsp;&nbsp;Ce programme est fonctionnel sur une carte WT32-SC01 Plus. Il permet d'utiliser la fonctionnalité tactile de l'écran de la carte. Pour ce faire, le paramètre "touch_cfg" a été ajouté à la classe LGFX. De plus, nous avons créé deux fonctions *initTouch()* et *getTouch(x, y)* permettant respectivement d'initialiser le tactile et de récupérer les coordonnées de l'appui.

&nbsp;&nbsp;&nbsp;&nbsp;La Fonction dessin permet d'afficher une croix rouge en haut à gauche de l'écran. Le reste du programme se déroule dans la partie *loop* où nous utilisons les coordonnées fournies par *getTouch()* pour dessiner un cercle ou pour effacer l'écran.

## Exécution

&nbsp;&nbsp;&nbsp;&nbsp;Téléversez le programme sur la carte de développement WT32-SC01 Plus. Une fois cela fait, vous devriez observer une croix rouge en haut à gauche de l'écran et l'ajout d'un cercle bleu lorsque vous appuyez sur l'écran.

## Auteur
Nathanael DEBREILLY - Github : [@Naellll](https://github.com/Naellll) - E-mail : nathanael.debreilly@gmail.com

## Projet complet : contrôle de base holonome via WT32-SC01 Plus

Lien Github : [Projet](https://github.com/Naellll/Controle-de-base-holonome-via-WT32-SC01-Plus)
