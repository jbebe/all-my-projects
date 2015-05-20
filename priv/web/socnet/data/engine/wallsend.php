<?php
	require("data/engine/mysql.php");
	
	$msg = mysql_real_escape_string($_POST['message']);
	$mysql_insert_query  = "INSERT INTO `wall`(`fromid`,`date`,`msg`) VALUES (";
	$mysql_insert_query .= $_SESSION['id'].",NOW(),'$msg')";
	
	mysql_query($mysql_insert_query,$mysql_connection) or die($err_mysql_query_insert);
	mysql_close($mysql_connection);
	header("Location:$base_url");
?>