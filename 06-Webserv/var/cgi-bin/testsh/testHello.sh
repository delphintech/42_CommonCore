#!/bin/bash
# Indiquer que le contenu est du HTML
echo "Content-type: text/html"
echo ""
# Afficher le contenu HTML
echo "<html>"
echo "<head><title>Hello, World!</title></head>"
echo "<body>"
echo "<h1>Hello, World!</h1>"
echo "<p>This is a simple CGI script written in Bash.</p>"
echo "</body>"
echo "</html>"
exit 0