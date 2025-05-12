##### CONSTANTES #####
HOST = "0.0.0.0"
PORT = numero_port

##### IMPORTATIONS #####
import tkinter as tk
import socket

##### FONCTIONS #####
def deplacer(cmd):
    global x, y

    if cmd == "haut" and y > 0:
        y = y - 1
    elif cmd == "bas" and y < (10 - 1):
        y = y + 1
    elif cmd == "gauche" and x > 0:
        x = x - 1
    elif cmd == "droite" and x < (10 - 1):
        x = x + 1

    x_nouveau = x * 50 + 50 // 2
    y_nouveau = y * 50 + 50 // 2

    canva.coords(disque, x_nouveau - 25, y_nouveau - 25, x_nouveau + 25, y_nouveau + 25)

def verifier_socket():
    """
    Vérifie les messages entrants sans bloquer l'interface graphique
    """
    try:
        client.settimeout(0.01)  # Petite temporisation pour éviter de bloquer
        data = client.recv(1024).decode("utf-8").strip().lower()
        if data in ("haut", "bas", "gauche", "droite"):
            deplacer(data)
    except socket.error:
        pass  # Pas de données à lire

    fenetre.after(50, verifier_socket)  # Vérifie toutes les 50 ms

##### SOCKET #####
serveur = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serveur.bind((HOST, PORT))
serveur.listen(1)
print("En attente de connexion...")
client, adresse = serveur.accept()
print(client)
print(adresse)

###### TKINTER #####
fenetre = tk.Tk()
fenetre.title("WT32-SC01 plus en connexion Wi-Fi")
fenetre.geometry("500x500")

canva = tk.Canvas(fenetre, width=500, height=500, bg="white")
canva.pack()

for i in range(0, 501, 50):
    canva.create_line(i, 0, i, 500, fill="black")
    canva.create_line(0, i, 500, i, fill="black")

x, y = 2, 2
disque = canva.create_oval(100, 100, 150, 150, fill="red")

# Démarrer la vérification des messages
fenetre.after(50, verifier_socket)

# Lancer la boucle principale
fenetre.mainloop()

# Fermer les sockets après fermeture de la fenêtre
client.close()
serveur.close()
