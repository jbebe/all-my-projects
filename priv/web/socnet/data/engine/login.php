<?php if (!isset($unique)) exit("pre_reg"); ?>
<div id="top-bar">
	<div id="login">
		<form method="post" action="<?php print($base_url); ?>?page=3">
			<div class="alignable">e-mail cím: <input type="text" name="login_email" /></div>
			<div class="alignable">jelszó: <input type="password" name="login_password" /></div>
			<input type="submit" value="Login" />
		</form>
	</div>
</div>
<div id="register-wrapper">
	<h1>regisztrálj!</h1>
	<div id="register">
		<form method="post" action="<?php print($base_url); ?>?page=2">
	<div class="clear">neme: <select class="putleft" name="sex">
		<option value="0">nő</option>
		<option value="1">férfi</option>
	</select></div>
	<div class="clear">e-mail:			 <input class="putleft" type="text" name="email" /></div>
	<div class="clear">kereszt név:     <input class="putleft" type="text" name="firstname" /></div>
	<div class="clear">vezeték név:     <input class="putleft" type="text" name="lastname" /></div>
	<div class="clear">születési dátum: <select class="putleft" name="year">
		<?php
			$output = "";
			for($i = 1900; $i < 2014; $i++)
				$output .= "<option value='".$i."'>".$i."</option>\n";
			print($output);
		?>
	</select>
	<select class="putleft" name="month">
		<?php
			$output = "";
			$month = ["Január","Február","Március",
						 "Április","Május","Június","Július",
						 "Augusztus","Szeptember",
						 "Október","November","December"];
			for($i = 0; $i < count($month); $i++)
				$output .= "<option value='".($i+1)."'>".($month[$i])."</option>\n";
			print($output);
		?>
	</select>
	<select class="putleft" name="day">
		<?php
			$output = "";
			for($i = 1; $i < 32; $i++)
				$output .= "<option value='".$i."'>".$i."</option>\n";
			print($output);
		?>
	</select></div>
	<div class="clear">lakhely:		 <select class="putleft" name="location">
		<?php
			$output = "";
			$loc = ["Budapest","külföld","Bács-Kiskun megye",
					   "Baranya megye","Békés megye",
					   "Borsod-Abaúj-Zemplén megye","Csongrád megye",
					   "Fejér megye","Győr-Moson-Sopron megye",
					   "Hajdú-Bihar megye","Heves megye",
					   "Jász-Nagykun-Szolnok megye","Komárom-Esztergom megye",
					   "Nógrád megye","Pest megye","Somogy megye",
					   "Szabolcs-Szatmár-Bereg megye","Tolna megye","Vas megye",
					   "Veszprém megye","Zala megye"];
			for($i = 0; $i < count($loc); $i++)
				$output .= "<option value='" . $loc[$i] . "'>" . $loc[$i] . "</option>\n";
			print($output);
			?>
	</select></div>
	<div class="clear">jelszó:<input class="putleft" type="password" name="password" /></div>
	<div class="clear"><input type="submit" class="putleft" value="Sign Up" /></div>
</form>
	</div>
</div>