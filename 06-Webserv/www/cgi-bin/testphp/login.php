<?php
include 'session_config.php';
//session.gc_maxlifetime = 1400;soit 24 minutes
//au dela les session sont detruites
//peut etre modifié dans le fichier php.ini
// Générer une réponse HTML

//ou en php avec la fonction ini_set('session.gc_maxlifetime', 1400); 
echo "<!DOCTYPE html>";
echo "<html lang='en'>";
echo "<head>";
echo "<meta charset='UTF-8'>";
echo "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
echo "<title>Login</title>";
echo "</head>";
echo "<body>";

$allowed = false;
// Lire les données de la requête POST
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Lire les données de la requête POST
    if (isset($_POST['login'])) {
        $login = htmlspecialchars($_POST['login']);
        echo "Login: $login<br>";
        echo"Session: <pre>";
        print_r($_SESSION);
        echo "</pre>";
    }
    // lire les informations utilisateur dans un sous-tableau de session
    $key =  $login;
    if (isset( $_SESSION[$key]))
    {
        $allowed = true;
        setcookie("name", $_SESSION[$key]['username'], time() + 3600, "/");
        setcookie("email", $_SESSION[$key]['email'], time() + 3600, "/");
        setcookie("avatar", $_SESSION[$key]['avatar'], time() + 3600, "/");
    }
}

if ($allowed) {
    echo "Login réussi !<br>";
    echo "Nom d'utilisateur : " . $_COOKIE['name'] . "<br>";
    echo "Email : " . $_COOKIE['email'] . "<br>";
    echo "Avatar : " . $_COOKIE['avatar'] . "<br>";
} else {
    echo "Login échoué !<br>";
}
//echo "<p><strong>Avatar :</strong> <img src='./cgi-script/$target_file' alt='Avatar'></p>";
echo "<p><a href='index.html'>Retour au formulaire</a></p>";

echo "</body>";
echo "</html>";
?>