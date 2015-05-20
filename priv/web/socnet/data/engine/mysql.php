<?php if (!isset($unique)) exit("mysql");

	$mysql_connection = mysql_connect(
        "localhost",
        $mysql_username,
        $mysql_password
    ) or die($err_mysql_connection);
    
	
    mysql_select_db($mysql_dbname) or die($err_mysql_db);
    mysql_query("SET NAMES 'utf8'");
	mysql_query("SET CHARACTER SET 'utf8'");
?>