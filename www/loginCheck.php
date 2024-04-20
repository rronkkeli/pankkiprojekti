<?php

//Onko käyttäjä jo kirjautunut sisään
if(!isset($_SESSION["login"]) || (time() - $_SESSION["activity"] > 900)){
	$_SESSION = array();
	session_destroy();

	header("location: login.php");
	exit;
} else {
	$_SESSION["activity"] = time();
}
?>