#!/bin/bash

# Ouvre la première fenêtre et exécute une commande
gnome-terminal -- bash -c "echo 'ls'; sleep 10"

# Ouvre la deuxième fenêtre et exécute une autre commande
gnome-terminal -- bash -c "echo 'pwd'; sleep 10"

# Ouvre la troisième fenêtre et exécute encore une autre commande
gnome-terminal -- bash -c "echo 'Commande 3'; sleep 10"

#fenetre persistante
gnome-terminal -- bash -c "echo 'Commande 1'; bash"
gnome-terminal -- bash -c "echo 'Commande 2'; bash"
gnome-terminal -- bash -c "echo 'Commande 3'; bash"

#plusieur onglet
gnome-terminal --tab -- bash -c "echo 'Onglet 1'; bash" \
               --tab -- bash -c "echo 'Onglet 2'; bash" \
               --tab -- bash -c "echo 'Onglet 3'; bash"

#definir la position de la fenetre
#--geometry=COLSxROWS+X+Y
#COLSxROWS : taille de la fenetre en colonnes et lignes le séparateur est un x, la taille est en caractères
#X+Y : position de la fenetre en pixels par rapport au coin supérieur gauche de l'écran
#X : position en pixels sur l'axe horizontal (0 est à gauche)
#Y : position en pixels sur l'axe vertical (0 est en haut)
gnome-terminal --geometry=80x24+100+200 -- bash -c "echo 'Position 1'; bash"

# Récupérer la résolution de l'écran
SCREEN_WIDTH=$(xrandr | grep '*' | awk '{print $1}' | cut -d 'x' -f 1)
SCREEN_HEIGHT=$(xrandr | grep '*' | awk '{print $1}' | cut -d 'x' -f 2)

# Définir les tailles des fenêtres (en caractères)
COLS=80
ROWS=24

# Calculer les positions
X1=0
Y1=0
X2=$((SCREEN_WIDTH / 2))
Y2=0
X3=0
Y3=$((SCREEN_HEIGHT / 2))
X4=$((SCREEN_WIDTH / 2))
Y4=$((SCREEN_HEIGHT / 2))
# Ouvrir la première fenêtre pour lancer le serveur
gnome-terminal --geometry=${COLS}x${ROWS}+$X1+$Y1 -- bash -c "./webserv; exec bash"

# Attendre que le serveur démarre pour récupérer son PID
sleep 2
PID_WEBSERV=$(pgrep -x webserv)

# Ouvrir la deuxième fenêtre pour afficher `top`
gnome-terminal --geometry=${COLS}x${ROWS}+$X2+$Y2 -- bash -c "top -H -p $PID_WEBSERV; exec bash"

# Ouvrir la troisième fenêtre pour suivre les logs
gnome-terminal --geometry=${COLS}x${ROWS}+$X3+$Y3 -- bash -c "tail -f log.txt; exec bash"

# Ouvrir la quatrième fenêtre pour le testeur
gnome-terminal --geometry=${COLS}x${ROWS}+$X4+$Y4 -- bash -c "time ./ubuntu_tester http://127.0.0.1:8080; exec bash"