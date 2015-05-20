<?php $unique = 1;
    $titles = ["login","home"];
    if (isset($_GET['page'])) $page_type = $_GET['page']+0;
	else $page_type = 1;
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
	<title>socnet - <?php print(($page_type==1?$titles[0]:$titles[1])); ?></title>
    <link rel="stylesheet" href="data/css/main.css" />
</head>
<body>
<?php
	require("data/engine/config.php");
    session_start();
	switch ($page_type){
		case 1:
            if (isset($_SESSION['id'])) header("Location: $base_url?page=5");
			else require("data/engine/login.php");
			break;
		case 2:
            if (isset($_SESSION['id'])) header("Location: $base_url?page=5");
			else require("data/engine/reg.php");
			break;
        case 3:
            if (isset($_SESSION['id'])) header("Location: $base_url?page=5");
            else require("data/engine/loginauth.php");
            break;
		case 4:
			if (isset($_SESSION['id'])) require("data/engine/logout.php");
            else header("Location: $base_url");
			break;
        case 5:
            if (isset($_SESSION['id'])) require("data/engine/wall.php");
            else header("Location: $base_url");
			break;
        case 6:
            if (isset($_SESSION['id'])) require("data/engine/wallsend.php");
            else header("Location: $base_url");
		default:
			header("Location:$base_url");
	}
?>
</body>
</html>