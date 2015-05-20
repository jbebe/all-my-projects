<?php if (!isset($unique)) exit("config");

    // mysql settings
    $mysql_username = "root";
    $mysql_password = "";
    $mysql_dbname = "socnet";
    
    // others
    $base_url = "http://localhost/socnet/";
    
    // errors:
    $err_mysql_connection = "A mysql kapcsolat nem jött létre!";
    $err_mysql_db = "Nem sikerült az adatbázishoz kapcsolódni!";
    $err_mysql_query_insert = "Nem sikerült a regisztráció";
    $err_mysql_query_login = "Nem sikerült bejelentkezni!";
    $err_mysql_query_email = "Ez az e-mail cím már foglalt!";
    $err_reg_empty = "Nem töltöttél ki mindent!";
    $err_reg = "Hibás adatot adtál meg!";
?>