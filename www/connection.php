<?php 
//Virheilmoitukset näkyviin
ini_set("display_errors", 1);
ini_set("error_reporting", E_ALL);

//Muuttujat / Asetukset
define("HOST", "127.0.0.1");
define("USERNAME", "bankadmin");
define("PASSWORD", "bankadminpassword");
define("DATABASENAME", "bank");
define("PORT", "4000");
define("DSN", "mysql:host=" . HOST . ";dbname=" . DATABASENAME . ";charset=UTF8;port=" . PORT);

//Yhteys tietokantaan
try {
	$connect = new PDO(DSN, USERNAME, PASSWORD);
	//Virheet
	$connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch(PDOException $virhe) {
	die("VIRHE: " . $virhe->getMessage());
}

?>