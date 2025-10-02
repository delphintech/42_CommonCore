#!/bin/bash

# Indiquer que le contenu est du HTML
echo "Content-type: text/html"
echo ""

# Lire la longueur du contenu
CONTENT_LENGTH=${CONTENT_LENGTH:-0}

# Lire les données POST
if [ "$CONTENT_LENGTH" -gt 0 ]; then
    while IFS= read -r -n1 char; do
        POST_DATA+="$char"
        if [ ${#POST_DATA} -ge "$CONTENT_LENGTH" ]; then
            break
        fi
    done
fi
# Afficher le contenu HTML
echo "<html>"
echo "<head><title>POST Handler</title></head>"
echo "<body>"
echo "<h1>POST Handler</h1>"
echo "<p>Received POST:</p>"
echo "<p>CONTENT_LENGTH $CONTENT_LENGTH</p>"
echo "<p>CONTENT_TYPE $CONTENT_TYPE</p>"
echo "<p>Received POST data:</p>"
echo "<pre>$POST_DATA</pre>"
echo "</body>"
echo "</html>"

exit 0