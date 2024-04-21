<?php

	echo '
		<header class="text-center p-3 mb-5" style="position: sticky; top: 0; z-index: 2; background-color: rgba(58, 58, 58, 0.8)">
		<h1>Bank';
	if (isset($_SESSION["login"])) {
		echo '<span class="float-left" style="font-size: 20px; position: absolute; top: 0; left: 0; padding-left: 10px;""><a class="pr-3" style="color: #03BFCE;" href="index.php"><i class="fas fa-home"></i>Home</a></span>';
		echo '<span class="float-right" style="font-size: 20px; position: absolute; top: 0; right: 0; padding-right: 10px;""><a class="pr-3" style="color: #03BFCE;" href="logout.php"><i class="fas fa-sign-out-alt"></i>Log out</a>
		<br><a class="pr-3" style="color: #FFFFFF" href="ownDetails.php"><p> ' . $_SESSION["name"] . '</p></a></span>';
	} else {
		echo '<span class="float-right" style="font-size: 20px; position: absolute; top: 0; right: 0; padding-right: 10px;">
			 <a class="pr-3" style="color: #03BFCE;" href="login.php"><i class="fas fa-sign-in-alt"></i>Log in</a></span>';
	}
	echo '</h1>';
	echo '</header>';
?>