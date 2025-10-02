#!/bin/bash

# URL du serveur à tester
URL="http://127.0.0.1:8080/"

# Nombre de requêtes simultanées
#128*50 = 6400
NUM_REQUESTS=6400

# Fichier de réponse temporaire
RESPONSE_FILE=$(mktemp)
# Fonction pour envoyer une requête
send_request() {
    local response_code=$(curl -s -o /dev/null -w "%{http_code}" "$URL")
    echo "$response_code" >> "$RESPONSE_FILE"
}

# Lancer les requêtes simultanées
for ((i=1; i<=NUM_REQUESTS; i++))
do
    send_request &
    echo "Requête $i envoyée."
done

# Attendre que toutes les requêtes soient terminées
wait

echo "Test de charge terminé avec $NUM_REQUESTS requêtes simultanées."

# Analyser les codes de réponse
SUCCESS_COUNT=$(grep -c "200" "$RESPONSE_FILE")
NOT_FOUND_COUNT=$(grep -c "404" "$RESPONSE_FILE")
TIMEOUT_COUNT=$(grep -c "408" "$RESPONSE_FILE")
TOTAL_COUNT=$(wc -l < "$RESPONSE_FILE")

echo "Nombre de requêtes réussies : $SUCCESS_COUNT"
echo "Nombre de requêtes non trouvées : $NOT_FOUND_COUNT"
echo "Nombre de requêtes en timeout : $TIMEOUT_COUNT"
echo "Nombre total de requêtes : $TOTAL_COUNT"

# Vérifier si toutes les requêtes ont été traitées correctement
if [ "$SUCCESS_COUNT" -eq "$NUM_REQUESTS" ]; then
    echo "Toutes les requêtes ont été traitées correctement."
else
    echo "Certaines requêtes n'ont pas été traitées correctement."
fi

# Supprimer le fichier temporaire
rm "$RESPONSE_FILE"