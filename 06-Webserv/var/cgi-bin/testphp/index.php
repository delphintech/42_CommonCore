<?php
// Capture la sortie avant de l'envoyer
ob_start();

phpinfo();
// Récupérer la taille du contenu
$content_length = ob_get_length();
// Envoyer les en-têtes HTTP
header('Content-Length: ' . $content_length);

// Sinon, afficher normalement le contenu
ob_end_flush();
?>