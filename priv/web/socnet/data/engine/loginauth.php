<?php
	require("data/engine/mysql.php");
	
	$email = $_POST['login_email'];
	$hash = md5($_POST['login_password']);
	
	$mysql_select_query = "SELECT `id` FROM `user` WHERE `email` = '";
	$mysql_select_query .= $email . "' AND `hash` = '".$hash."'"	;
	
	$result = mysql_query($mysql_select_query,$mysql_connection) or die($err_mysql_query_login);
	$result = mysql_fetch_array($result,MYSQL_NUM);
	
	if ($result != false){
		session_start();
		$_SESSION["id"] = $result[0]+0;
		header("Location: $base_url?page=5");
	}
	else {
		header("Location: $base_url");
	}
	mysql_close();
?>