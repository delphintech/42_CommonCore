<?php
// Générer une réponse HTML
echo "<!DOCTYPE html>";
echo "<html lang='en'>";
echo "<head>";
echo "<meta charset='UTF-8'>";
echo "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
echo "<title>Formulaire Reçu</title>";
echo "</head>";
echo "<body>";


// Activer les erreurs pour le débogage
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

// Lire les données de la requête POST
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $data = json_decode(file_get_contents('php://input'), true);
    $name = isset($data['name']) ? htmlspecialchars($data['name']) : "inconnu";
    $email = isset($data['email']) ? htmlspecialchars($data['email']) : "inconnu";
    $message = isset($data['message']) ? htmlspecialchars($data['message']) : "Aucun message";

    echo "Name: $name, Email: $email, Message: $message";
}

$post_body = file_get_contents('php://input');
echo "<br>POST BODY:<br>";
echo "<pre>";
print_r($post_body);
echo "</pre>";

echo "<br>REQUEST:<br>";
echo "<pre>";
print_r($_REQUEST);
echo "</pre>";
// Afficher les données POST pour le débogage
echo "<br>_COOKIE:<br>";
echo "<pre>";
print_r($_COOKIE);
echo "</pre>";



// Afficher les variables d'environnement pour le débogage
echo "\r\n\r\n";
echo "<br>_SERVER:<br>";
echo "<pre>";
print_r($_SERVER);
echo "</pre>";

// Générer une réponse HTML
//echo "<html>";
//echo "<head><title>Formulaire Reçu</title></head>";
//echo "<body>";
echo "<h1>Données du formulaire</h1>";
echo "<p><strong>Nom :</strong> $name</p>";
echo "<p><strong>Email :</strong> $email</p>";
echo "<p><strong>Message :</strong> $message</p>";
//echo "<p><strong>Avatar :</strong> <img src='./cgi-script/$target_file' alt='Avatar'></p>";
echo "<p><a href='index.html'>Retour au formulaire</a></p>";

echo "</body>";
echo "</html>";
//set cookie
setcookie("name", $name, time() + 3600, "/");
setcookie("email", $email, time() + 3600, "/");
setcookie("message", $message, time() + 3600, "/");

?>