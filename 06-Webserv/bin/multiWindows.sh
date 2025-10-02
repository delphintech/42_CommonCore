#!/bin/bash

# creer un fichier log.txt
touch logs/access.log
# Récupérer la résolution de l'écran (prendre seulement la première ligne avec `head -n 1`)
SCREEN_RESOLUTION=$(xrandr | grep '*' | head -n 1 | awk '{print $1}')
SCREEN_WIDTH=$(echo $SCREEN_RESOLUTION | cut -d 'x' -f 1)
SCREEN_HEIGHT=$(echo $SCREEN_RESOLUTION | cut -d 'x' -f 2)

# Affichage des valeurs pour vérifier
echo "Résolution détectée : ${SCREEN_WIDTH}x${SCREEN_HEIGHT}"

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
gnome-terminal --geometry=${COLS}x${ROWS}+$X1+$Y1 -- bash -c "./webserv ./YoupiBanane/youpi.conf; exec bash"

# Attendre que le serveur démarre pour récupérer son PID
sleep 2
PID_WEBSERV=$(pgrep -x webserv)

# Vérifier si le serveur tourne
if [[ -z "$PID_WEBSERV" ]]; then
    echo "Erreur : Impossible de récupérer le PID du serveur webserv."
    exit 1
fi

echo "Serveur webserv lancé avec le PID : $PID_WEBSERV"

# Ouvrir la deuxième fenêtre pour afficher `top`
#gnome-terminal --geometry=${COLS}x${ROWS}+$X2+$Y2 -- bash -c "top -H -p $PID_WEBSERV; exec bash"
#gnome-terminal --geometry=${COLS}x${ROWS}+$X2+$Y2 -- bash -c "htop --pid $PID_WEBSERV; exec bash"


# Ouvrir la troisième fenêtre pour suivre les logs
gnome-terminal --geometry=${COLS}x${ROWS}+$X3+$Y3 -- bash -c "tail -f logs/access.log; exec bash"

# Ouvrir la quatrième fenêtre pour le testeur
gnome-terminal --geometry=${COLS}x${ROWS}+$X4+$Y4 -- bash -c "time ./ubuntu_tester http://127.0.0.1:8080; exec bash"
