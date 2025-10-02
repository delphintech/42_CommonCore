<?php
include 'session_config.php';
// Fonction pour mettre à jour l'avatar de l'utilisateur
function updateAvatar($userid, $input) {
    $target_file = getenv('DOCUMENT_ROOT') . "/" .htmlspecialchars($_SESSION[$userid]['avatar']);
    error_log("Target file: " . $target_file);
    $newTargetFile = $target_file;
    //create new avatar, get extension form content type
    $imageFileType = getenv('CONTENT_TYPE');
    if ($imageFileType != 'image/png') {
        error_log("Invalid content type.");
        return htmlspecialchars($_SESSION[$userid]['avatar']);//return old avatar
    }
    if (file_exists($target_file)) {
        if (!getimagesize($target_file)) {
            error_log("Old avatar is not an image.");
        }
        else
        {
            unlink($target_file);
            error_log("Old avatar deleted.");
        }
    }else{
        error_log("Old avatar not found.");
    }

    $avatar = substr($newTargetFile, strlen($_SERVER['DOCUMENT_ROOT']));
    error_log("New avatar: " . $avatar);
    if (file_put_contents($newTargetFile, $input)) {
        error_log("Avatar updated successfully.");      
       return $avatar;
    } else {
        error_log("Failed to update avatar.");
        return "";
    }
}

function updateEmail($userid, $newEmail) {
    error_log("Email updated successfully.");
    return $newEmail;
}

// Fonction pour mettre à jour le nom de l'utilisateur
function updateName($userid, $newName) {
    error_log("Name updated successfully.");
    return $newName;
}


if ($_SERVER['REQUEST_METHOD'] == 'PUT') {
    $input = file_get_contents('php://input');
       // Récupérer l'action à effectuer 
    $action = isset($_GET['action']) ? $_GET['action'] : null;
    if (!$action) {
        error_log('Invalid request. action is missing.');
        exit;
    }
    $userid = isset($_GET['userid']) ? $_GET['userid'] : null;
    if (!$userid) {
        error_log('Invalid request. userid is missing.');
        exit;
    }

    /*  // Lire les données des COOKIES
     $name = isset($_COOKIE['name']) ? htmlspecialchars($_COOKIE['name']) : "inconnu";
     $email = isset($_COOKIE['email']) ? htmlspecialchars($_COOKIE['email']) : "inconnu";
     $avatar = isset($_COOKIE['avatar']) ? htmlspecialchars($_COOKIE['avatar']) : ""; */
    //recuperer la session
    $key =  $userid;
    error_log("Key: " . $key);
    error_log("Session: " . print_r($_SESSION, true));
    error_log("_GET: " . print_r($_GET, true));
    if (isset( $_SESSION[$key]))
    {
         // Lire les données des SESSION
        $name = isset($_SESSION[$key]['username']) ? htmlspecialchars($_SESSION[$key]['username']) : "inconnu";
        $email = isset($_SESSION[$key]['email']) ? htmlspecialchars($_SESSION[$key]['email']) : "inconnu";
        $avatar = isset($_SESSION[$key]['avatar']) ? htmlspecialchars($_SESSION[$key]['avatar']) : "";
        $allowed = true;
    }
    else{
        error_log('Invalid request. User not found.');
        exit;
    }
    switch ($action) {
        case 'updateAvatar':
            updateAvatar($userid, $input);// on ne change pas le nom du fichier
            break;
        case 'updateEmail':
            parse_str($input, $data);
            $email = updateEmail($userid, $data['email']);
            $_SESSION[$key]['email'] = $email;
            //copy and unset the old session
            $_SESSION[$email] = $_SESSION[$key];
            unset($_SESSION[$key]);
            break;
        case 'updateName':
            parse_str($input, $data);
            $name = updateName($userid, $data['name']);
            $_SESSION[$key]['username'] = $name;
            break;
        default:
        error_log('Unknown action.');
            exit ;
    }

   
}
else {
    error_log('Invalid request. PUT method is required.');
    exit;
}
setcookie("name", $name, time() + 3600, "/");
setcookie("email", $email, time() + 3600, "/");
setcookie("avatar", $avatar, time() + 3600, "/");
?>