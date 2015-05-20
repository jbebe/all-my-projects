<?php
	require("data/engine/mysql.php");
	$mysql_select_query = "SELECT * FROM `user` WHERE `id` = '".$_SESSION['id']."'";
	$result = mysql_query($mysql_select_query,$mysql_connection) or die($err_mysql_query_login);
	$result = mysql_fetch_array($result,MYSQL_ASSOC);
?>
<div id="top-bar">
	<div id="bar-container">
		<a href="?page=5">Üdv, <?php print($result["firstname"]); ?></a>
		<a href="?page=4" style="float:right;margin-right:10px">KILÉP » █</a>
	</div>
</div>
<div id="wall-container">
	<div id="left-c">
		<img src="data/img/avatar_<?php print($result["sex"]); ?>.gif" />
		<?php
			foreach ($result as $key => $value)
				if ($key != "hash") print($key . ": " . $value . "<br/>");
		?>
	</div>
	<div id="right-c">
		<form method="post" action="?page=6">
			<textarea name="message"></textarea>
			<input type="hidden" name="id" value="<?php print($result['id']); ?>" />
			<input type="submit" value="Send" style="float:right;margin:5px 0;"/>
		</form>
		<div id="feed">
			<?php
				$mysql_select_query = "SELECT `fromid`, `date`, `msg` FROM `wall` WHERE `fromid` = ".$_SESSION['id']." ORDER BY date DESC";
				$result = mysql_query($mysql_select_query,$mysql_connection) or die($err_mysql_query_login);
				while($temp = mysql_fetch_array($result,MYSQL_ASSOC))
					print($temp['fromid']." - ".$temp['date'].": ".$temp['msg']."<br/>");
				mysql_close();
			?>
		</div>
	</div>
	<div class="clear">&nbsp;</div>
</div>