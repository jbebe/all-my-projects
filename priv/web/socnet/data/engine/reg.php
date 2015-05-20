<?php if (!isset($unique)) exit("reg");
	require("data/engine/mysql.php");
	
	if (	   empty($_POST['email'])
			|| !isset($_POST['sex'])
			|| empty($_POST['firstname'])
			|| empty($_POST['lastname'])
			|| empty($_POST['year'])
			|| empty($_POST['month'])
			|| empty($_POST['day'])
			|| empty($_POST['location'])
			|| empty($_POST['password'])
	) exit($err_reg_empty);
	
	if (preg_match('/^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.(?:[a-zA-Z]{2}|com|org|net|edu|gov|mil|biz|info|mobi|name|aero|asia|jobs|museum)$/', $_POST['email'], $mat))
		$email = mysql_real_escape_string($mat[0]);
	else $email = "";	
	$sex = 			$_POST['sex']+0;
	$firstname = 	mysql_real_escape_string(preg_replace('/[^\w\'\- ]/u', '', $_POST['firstname']));
	$lastname = 	mysql_real_escape_string(preg_replace('/[^\w\'\- ]/u', '', $_POST['lastname']));
	$year = 		$_POST['year']+0;
	$month = 		$_POST['month']+0;
	$day = 			$_POST['day']+0;
	$location = 	mysql_real_escape_string($_POST['location']);
	$password = 	md5($_POST['password']);
	
	if (	($sex<0||$sex>1) ||
			($email=="") ||
			($firstname=="") ||
			($lastname=="") ||
			($year<1900||$year>2013) ||
			($month<0||$month>12) ||
			($day<0||$day>31) ||
			($location=="") ||
			($password=="d41d8cd98f00b204e9800998ecf8427e")
	   ) exit($err_reg);
	
	$result = mysql_query("SELECT id FROM user WHERE `email` = '$email'") or die($err_mysql_query_insert);
	if (mysql_fetch_array($result,MYSQL_NUM) != false) exit($err_mysql_query_email);
	
	$mysql_insert_query  = "INSERT INTO `user`(`hash`,`email`,`sex`,`born`,`lastname`,`firstname`,`location`) VALUES (";
	$mysql_insert_query .= "'$password','$email','$sex','$year-$month-$day','$lastname','$firstname','$location')";
	
	mysql_query($mysql_insert_query,$mysql_connection) or die($err_mysql_query_insert);
	mysql_close($mysql_connection);
	header("Location:$base_url");
?>