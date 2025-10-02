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
$name = isset($_POST['name']) ? htmlspecialchars($_POST['name']) : "inconnu";
$email = isset($_POST['email']) ? htmlspecialchars($_POST['email']) : "inconnu";
$message = isset($_POST['message']) ? htmlspecialchars($_POST['message']) : "Aucun message";

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
echo "<br>_POST:<br>";
echo "<pre>";
print_r($_POST);
echo "</pre>";

// Afficher les fichiers téléchargés pour le débogage
echo "<br>_FILES:<br>";
echo "<pre>";
print_r($_FILES);
echo "</pre>";
//save the image
// Vérifier si un fichier a été téléchargé
if (isset($_FILES["avatar"]) && $_FILES["avatar"]["error"] == 0) {
	$upload_dir = getenv('UPLOAD_DIR');
	if (!$upload_dir) {
		$upload_dir = 'uploads';
	}
	//creer le dossier uploads
	if (!file_exists($upload_dir)) {
		mkdir($upload_dir, 0777, true);
	}
   // $target_dir = "uploads/";
    $target_file = $upload_dir . "/" . basename($_FILES["avatar"]["name"]);
    $uploadOk = 1;
    $imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));

    // Vérifier si le fichier est une image réelle ou une fausse image
    $check = getimagesize($_FILES["avatar"]["tmp_name"]);
    if ($check !== false) {
        echo "<br>File is an image - " . $check["mime"] . ".<br>";
        $uploadOk = 1;
    } else {
        echo "<br>File is not an image.<br>";
        $uploadOk = 0;
    }

    // Vérifier si le fichier existe déjà
    if (file_exists($target_file)) {
        echo "<br>Sorry, file already exists.<br>";
        $uploadOk = 0;
    }

    // Vérifier la taille du fichier
    if ($_FILES["avatar"]["size"] > 500000) {
        echo "<br>Sorry, your file is too large.<br>";
        $uploadOk = 0;
    }

    // Autoriser certains formats de fichier
    if ($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg" && $imageFileType != "gif") {
        echo "<br>Sorry, only JPG, JPEG, PNG & GIF files are allowed.<br>";
        $uploadOk = 0;
    }

    // Vérifier si $uploadOk est défini à 0 par une erreur
    if ($uploadOk == 0) {
        echo "<br>Sorry, your file was not uploaded.<br>";
    // Si tout est correct, essayer de télécharger le fichier
    } else {
        if (move_uploaded_file($_FILES["avatar"]["tmp_name"], $target_file)) {
            echo "<br>The file " . htmlspecialchars(basename($_FILES["avatar"]["name"])) . " has been uploaded.<br>";
        } else {
            echo "<br>Sorry, there was an error uploading your file.<br>";
        }
    }
} else {
    echo "<br>No file was uploaded or there was an error uploading the file.<br>";
}

// Afficher les variables d'environnement pour le débogage
echo "\r\n\r\n";
echo "<br>_SERVER:<br>";
echo "<pre>";
print_r($_SERVER);
echo "</pre>";

// suite Générer une réponse HTML

echo "<h1>Données du formulaire</h1>";
echo "<p><strong>Nom :</strong> $name</p>";
echo "<p><strong>Email :</strong> $email</p>";
echo "<p><strong>Message :</strong> $message</p>";
//echo "<p><strong>Avatar :</strong> <img src='./cgi-script/$target_file' alt='Avatar'></p>";
echo "<p><a href='index.html'>Retour au formulaire</a></p>";

echo "</body>";
echo "</html>";
?>