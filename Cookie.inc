<?php
error_reporting(E_ALL);
ini_set("display_errors", 1);
class Cookie
{
	// class Page's attributes
	public $content;
	public $mask;
	public $mysqli;
	public $programmask;

	public function setMysqli($mysqli) {
		$this->mysqli = $mysqli;
	}

	public function getMysqli() {
		return $this->mysqli;
	}

	// class Page's operations/methods
	public function __set($name, $value)
	{
		$this->name = $value;
	}

	public function setAuthorizedFunctionMask($mask) {
		//echo "setAuthorizedFunctionMask set to $mask<br />";
		$this->mask = $mask;
	}

	public function getAuthorizedFunctionMask() {
		//echo "getAuthroizedFunctionMask returning $this->mask<br />";
		return $this->mask;
	}

	public function setProgramMask($programmask) {
		// 3 Jan 2013
		//echo "setProgramMask set to $programmask<br />";
		$this->programmask = $programmask;
	}

	public function getProgramMask() {
		
		// 3 Jan 2013
		//echo "getProgramMask returning $this->programmask<br />";
		return $this->programmask;
	}

	public function QueryStates()
	// 3 Jan 2013
	{
		$get_gov_sql = "
			SELECT StateName, StateAbbreviation, StateID
			FROM State
			ORDER BY StateName
			";
		return $get_gov_sql;
	}
	
	public function QueryCounty($StateAbbreviation)
	// 3 Jan 2013
	{
		$get_gov_sql = "
			SELECT CountyName, CountyID, S.StateAbbreviation
			FROM County
			INNER Join State S
			ON County.StateID = S.StateID
			WHERE StateAbbreviation = '".$StateAbbreviation."'
			ORDER BY CountyName
			";
		return $get_gov_sql;
	}

	public function QueryCity($CountyID)
	// 3 Jan 2013
	{
		$get_gov_sql = "
			SELECT CityName, CityID
			FROM City
			WHERE CountyID = '".$CountyID."'
			ORDER BY CityName
			";
		return $get_gov_sql;
	}

	public function QueryCountryState($State)
	// 3 Jan 2013
	{
		$get_gov_sql = "
			SELECT CountyName, CountyID, S.StateID
			FROM County
			INNER JOIN State S
			ON County.StateID = S.StateID
			WHERE S.StateAbbreviation = '".$State."'
			ORDER BY StateName
			";
		return $get_gov_sql;
	}

	/*
		Display the "program" specific query results
	*/

	public function DisplayCommunityHobbyManagement()
	// 3 Jan 2013
	{
		$self = $_SERVER["PHP_SELF"];
		$mysqli = $this->getMysqli();
		$programmask = "";

		echo "<div id=\"subWrapper\">";

	
		$delete = false;
		$insert = false;
		$edit = false;
		$view = false;
		
		if ($programmask == "delete") {
			$delete = true;
			$edit = true;
			$view = true;
		}
		
		if ($programmask == "modify") {
			$edit = true;
		}
		
		if ($programmask == "insert") {
			$insert = true;
		}
		
		if ($programmask == "view") {
			$view = true;
		}

		$name = "";
		$SessionName = "";
		if (isset($_SESSION["SessionName"])) {
			$SessionName = $_SESSION['SessionName'];
		}

		if (!empty($SessionName)) {
			;
			//echo "<h2>SessionName : $SessionName</h2>";
		} else {
			//$_SESSION["SessionName"] = "wee";
			;
		}

		if (isset($_SESSION)) {
			;
			//echo "<h5>Dump of cookie, where the 'persistance' information : ";
			//var_dump($_SESSION);
			//echo "</h5>";
		}

		$req = $_SERVER["REQUEST_METHOD"];
		
		$Link = "";
		if (isset($_SESSION["Link"])) {
			$Link = $_SESSION["Link"];
		}
		$StateAbbreviation = "";
		if (isset($_SESSION["StateAbbreviation"])) {
			$StateAbbreviation = $_SESSION["StateAbbreviation"];
		}
		$CountyName = "";
		if (isset($_SESSION["CountyID"])) {
			$CountyID = $_SESSION["CountyID"];
			//$CountyName = $this->Decode($CountyName);
		}
		$CookieName = "";
		if (isset($_SESSION["CityID"])) {
			$CityID = $_SESSION["CityID"];
			//$CookieName = $this->Decode($CookieName);
		}

		echo "<h3><a onclick=\"resetCookie()\">Reset Cookie</a></h3>";
		if ($Link != "") {
			if ($Link == "ViewCity") {
				//echo "<h2>CountyID: $CountyID!</h2>";
				$statesql = "
					SELECT CountyName
					FROM County
					WHERE CountyID = '".$CountyID."'
					";
				//echo "city sql : $statesql<br />";
				$get_state_res = mysqli_query($mysqli, $statesql) or die(mysqli_error($mysqli));
				$gov_recs = mysqli_fetch_array($get_state_res);
				$CountyName = urldecode($gov_recs['CountyName']);
				$CountyName = $this->Decode($CountyName);
				echo "<h3>Cities for $StateAbbreviation, $CountyName County</h3>";
				$msqli = $this->getMysqli();
				//SELECT CookieName, CityID
				$statesql = $this->QueryCity($CountyID);
				//echo "city sql : $statesql<br />";
				$get_state_res = mysqli_query($mysqli, $statesql) or die(mysqli_error($mysqli));
				$num_rows = mysqli_num_rows($get_state_res);
				$index = 1;
				$count = 0;
				$row = 0;


				echo "<div id=\"subWrapper0\">";
				while ($gov_recs = mysqli_fetch_array($get_state_res)) {
					$count++;
					$CityName = $gov_recs['CityName'];
					$CityName = $this->Decode($CityName);
					$CityID = $gov_recs['CityID'];
					$classname = "statesCol" . $index;

					$id = "states" . $count;

					/*
						SELECT HS.HobbyShotsID, HS.MasterTableID, HS.PhotoDescription,
						HS.ImageName, HS.Vetted, MT.TableDisplay, P.PostalCode,
						P.PostalCodeID, HS.DateModified
					*/

					$getsql = $this->QueryCity("$CityID");
					//echo "City Sql : $getsql<br />";
					$get_sql_res = mysqli_query($mysqli, $getsql) or die(mysqli_error($mysqli));
					$num_rows = mysqli_num_rows($get_sql_res);
					//echo "ManagementCounty rows: $num_rows<br />";

					echo "<p id=\"$id\" name = \"$id\" class=\"$classname\">";
					if ($num_rows > 0) {
						echo "<a onclick = \"submitSpecialFormJS('CommunityManagementViewHuh','$StateAbbreviation', '$CountyID', '$CityID')\" >";
					}
					echo "$CityName";
					if ($num_rows > 0) {
						echo "<span class=\"foundInfo\">";
					}

					if ($num_rows > 0) {
						echo "</a>";
						echo "</span>";
					}
					echo "</p>";

					if ($count % 4 == 0) {
					//if ($index >= 4) {
						echo "</div>";
						$row++;
						echo "<div id=\"subWrapper$row\">";
						$index = 0;
						
					}
					$index++;
				}
				echo "</div>";
				echo "</div> <!-- final -->";
			}

			if ($Link == "ViewCounty") {
				$msqli = $this->getMysqli();
				echo "<h3>Counties for $StateAbbreviation</h3>";
				//SELECT CountyName, CountyID, S.StateAbbreviation
				$statesql = $this->QueryCounty($StateAbbreviation);
				//echo "<h3>statesql : $statesql</h3>";
				$get_state_res = mysqli_query($mysqli, $statesql) or die(mysqli_error($mysqli));
				$num_rows = mysqli_num_rows($get_state_res);
				//echo "num_rows : $num_rows<br />";
				$index = 1;
				$count = 0;
				$row = 0;


				echo "<div id=\"subWrapper0\">";
				while ($gov_recs = mysqli_fetch_array($get_state_res)) {
					$count++;
					$CountyName = $gov_recs['CountyName'];
					//$CountyName = $this->Decode($CountyName);
					$CountyID = $gov_recs['CountyID'];
					$StateAbbreviation = $gov_recs['StateAbbreviation'];
					$classname = "statesCol" . $index;

					$id = "states" . $count;

					/*
						SELECT HS.HobbyShotsID, HS.MasterTableID, HS.PhotoDescription,
						HS.ImageName, HS.Vetted, MT.TableDisplay, P.PostalCode,
						P.PostalCodeID, HS.DateModified
					*/

					$num_rows = 0;
					$getsql = $this->QueryCity("$CountyID");
					//echo "CountySql : $getsql<br />";
					$get_sql_res = mysqli_query($mysqli, $getsql) or die(mysqli_error($mysqli));
					$num_rows = mysqli_num_rows($get_sql_res);
					//echo "ManagementCounty rows: $num_rows<br />";
					if ($num_rows == 0) {
						$count--;
						continue;
					}

					echo "<p id=\"$id\" name = \"$id\" class=\"$classname\">";
					if ($num_rows > 0) {
						$_SESSION['Link'] = "ViewCity";
						echo "<a onclick = \"submitSpecialFormJS('ViewCity','$StateAbbreviation', '$CountyID', '')\" >";
					}
					echo "$CountyName";
					if ($num_rows > 0) {
						echo "<span class=\"foundInfo\">";
					}
					echo " ($num_rows)";
					if ($num_rows > 0) {
						echo "</a>";
						echo "</span>";
					}
					echo "</p>";

					if ($count % 4 == 0) {
					//if ($index >= 4) {
						echo "</div>";
						$row++;
						echo "<div id=\"subWrapper$row\">";
						$index = 0;
						
					}
					$index++;
				}
				echo "</div>";
				echo "</div> <!-- final -->";
			}

			if ($Link == "ViewState") {
				//echo "<h3>State : ViewState</h3>";
				$msqli = $this->getMysqli();
				//SELECT StateName, StateAbbreviation, StateID
				$statesql = $this->QueryStates();
				$get_state_res = mysqli_query($mysqli, $statesql) or die(mysqli_error($mysqli));

				$index = 1;
				$count = 0;
				$row = 0;

				//if (
				echo "<div id=\"subWrapper0\">";
				while ($gov_recs = mysqli_fetch_array($get_state_res)) {
					$count++;
					$StateName = $gov_recs['StateName'];
					$StateAbbreviation = $gov_recs['StateAbbreviation'];
					$classname = "statesCol" . $index;

					$id = "states" . $count;

					$getsql = $this->QueryCountryState("$StateAbbreviation");
					$get_sql_res = mysqli_query($mysqli, $getsql) or die(mysqli_error($mysqli));
					$num_rows = mysqli_num_rows($get_sql_res);

					echo "<p id=\"$id\" name = \"$id\" class=\"$classname\">";
					if ($num_rows > 0) {
						//$_SESSION['State'] = $StateAbbreviation;
						$_SESSION['Link'] = "ViewCounty";
					
						echo "<a onclick = \"submitSpecialFormJS('ViewCounty','$StateAbbreviation', '', '')\" >";
					}
					echo "$StateName";
					if ($num_rows > 0) {
						echo "<span class=\"foundInfo\">";
					}

					echo " ($num_rows)";
					if ($num_rows > 0) {
						echo "</a>";
						echo "</span>";
					}
					echo "</p>";

					if ($count % 4 == 0) {
					//if ($index >= 4) {
						echo "</div>";
						$row++;
						echo "<div id=\"subWrapper$row\">";
						$index = 0;
						
					}
					$index++;
				}
				echo "</div>";
				echo "</div> <!-- final -->";
			}

			if ($Link == "" ) {
				;
			}

			if ($Link == "") {
				;
			}
		} else {
			echo "<p class=\"subheads\">";
			//echo "<h3>State: Default</h3>";
			//echo "<a onclick = \"submitSpecialFormJS('ViewState','','','')\" >United States City Names</a>";
			$_SESSION['Link'] = "ViewState";
			echo "<a onclick = \"submitSpecialFormJS('ViewState','','','')\" >United States City Names</a>";
			echo "</p>";
		}

		//echo "<input type=\"submit\" name=\"submit\" id=\"submit\" />";
		//echo "</div>";
		?>
		</div>
		<?php
	}

	public function DisplayPopups()
	// 3 Jan 2013
	{

		$self = $_SERVER["PHP_SELF"];
		echo '<div id="entrypopups">';
		echo "<form action=\"$self\" id=\"submitSpecialForm\" name=\"submitSpecialForm\" method=\"post\" >";
		echo "<input type=\"hidden\" name=\"Link\" id=\"Link\" />";
		echo "<input type=\"hidden\" name=\"StateAbbreviation\" id=\"StateAbbreviation\"  />";
		echo "<input type=\"hidden\" name=\"CityID\" id=\"CityID\" />";
		echo "<input type=\"hidden\" name=\"CountyID\" id=\"CountyID\" />";
		echo "<input type='hidden' name='name' id='name' >";
		echo "</form>";
	}

	public function ConnectDatabase()
	// 3 Jan 2013
	{
		$mysqli = db_connect();
		if (mysqli_connect_errno()) {
			printf("Connect failed: %s\n", mysqli_connect_error());
			exit();
		}
		//$d = "texty";
		//$this->Decode($d);
		$this->mysqli = $mysqli;
		$this->setMysqli($mysqli);
		return $mysqli;
	}

	public function DisplayServer()
	// 3 Jan 2013
	{
		$serve = $_SERVER["SERVER_NAME"];
		echo '<div id="server" class="server">';
		echo "Server : " .$serve;
		echo "</div>";
	}

	public function DisplayDatabase()
	// 3 Jan 2013
	{
		$mysqli = $this->getMysqli();
		echo '<div id="database" class = "database">';
		$get_gov_sql = "
		SELECT DATABASE()
		";
	
		$get_gov_res = mysqli_query($mysqli, $get_gov_sql) or die(mysqli_error($mysqli));
		$num_rows = mysqli_num_rows($get_gov_res);

		if ($num_rows > 0) {
			$gov_recs = mysqli_fetch_array($get_gov_res);
			$record = $gov_recs[0];
			$db = "LocoollyDatabase = '$record';";
			?>
			<script>
			<?php echo $db; ?>
			</script>
			<?php
			echo "Database : " . $record;
		}
		echo '</div>';
	}

	public function Decode($string)
	{
		$string = str_replace("%25","%",$string);
		$string = str_replace("%20"," ",$string);
		$string = str_replace("%23","#",$string);
		$string = str_replace("%26","&",$string);
		$string = str_replace("%27","'",$string);
		$string = str_replace("%29",")",$string);
		$string = str_replace("%2B","+",$string);
		$string = str_replace("+"," ",$string);
		$string = str_replace("%2C",",",$string);
		$string = str_replace("%2F","/",$string);
		$string = str_replace("+"," ",$string);
		$string = str_replace("%40","@",$string);
		$string = str_replace("%27","'",$string);

		return $string;
	}
	
	public function DisplayHeader($title)
	// 3 Jan 2013
	{
		?>
		<!DOCTYPE html>
		<html>
		<head>
		<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
		<meta name="author" content ="Steven C Shepard" />
		<meta name="description" content = "A template for Locoolly Production sites" />
		<meta name="keywords" content="web development, webdev, html5" />
		<meta name="robots" content="noindex" />
		<?php
		echo "<title>" .$title . "</title>";
		?>
		<link rel="shortcut icon" href="favicon.ico" />
		<script src="Template.js" type="text/javascript"></script>
		<link href="Template.css" rel="stylesheet" type="text/css" />
		</head>
		<header>
		<script>
		function resetCookie() {
			req = new XMLHttpRequest();
			url = 'clearCookie.php';
			url=url+"?sid="+Math.random();
			//console.log("getFileHandle, url : " + url);
						
			req.open("GET",url, false);
			req.send(null);
			req.onreadystatechange = dummy;

			var div = document.getElementById("submitSpecialForm");
			div.method = "post";

			if (div) {
				//alert("submitting!");
				div.submit();
			}
		}

		function dummy() {
			;
		}

		function submitSpecialFormJS(mode, StateAbbreviation, CountyID, CityID) {
			var div = document.getElementById("submitSpecialForm");
			//alert("StateAbbreviation : " + StateAbbreviation);

			req = new XMLHttpRequest();
			url = 'updateCookie.php';
			url += "?StateAbbreviation="+StateAbbreviation;
			url += "&CountyID="+CountyID;
			url += "&CityID="+CityID;
			url += "&sid="+Math.random();
			//console.log("getFileHandle, url : " + url);
						
			req.open("GET",url, false);
			req.send(null);
			req.onreadystatechange = dummy;
			//alert("Pulling the plug");

			if (div) {
				//alert("submitting!");
				div.submit();
				;
			}
		}
		</script>
		</header>
		<nav>
		</nav>
		<section>
		<?php
	}
	
	public function DisplayBody($h1) {
		// 3 Jan 2013
		?>
		<body>
		<div id="wrapper">
		<?php
		echo "<h1>" . $h1 . "</h1>";
		?>
		<?php
	}
	
	public function DisplayTitle()
	{
		?>
		<?php
		;
	}
	
	public function queryBrowser() {
		// 3 Jan 2013
		$IEflag = 0;
		$IE9flag = 0;
		$IE8flag = 0;
		$IE7flag = 0;
		$FireFoxFlag = 0;
		$SafariFlag = 0;
		$OperaFlag = 0;
		$ChromeFlag = 0;

		$browser = strtolower($_SERVER['HTTP_USER_AGENT']); // what browser they use.
	
		if(preg_match("/msie 9/", $browser)) {
			//Internet Explorer
			$IEflag = 0;
			$IE9flag = 1;
			$IE8flag = 0;
			$IE7flag = 0;
			return "IE9flag";
			}
		if(preg_match("/msie 8/", $browser)) {
			//Internet Explorer
			$IEflag = 0;
			$IE9flag = 0;
			$IE8flag = 1;
			$IE7flag = 0;
			return "IE8flag";
			}
		if(preg_match("/msie 7/", $browser)) {
			//Internet Explorer
			$IEflag = 0;
			$IE9flag = 0;
			$IE8flag = 0;
			$IE7flag = 1;
			return "IE7flag";
			}
		if (preg_match("/firefox/", $browser)) {
			//Firefox
			$FireFoxFlag = 1;
			return "FireFoxFlag";
		}
		
		if (preg_match("/chrome/", $browser)) {
			//Safari
			$ChromeFlag = 1;
			return "ChromeFlag";
		} else if (preg_match("/safari/", $browser)) {
			//Chrome
			$SafariFlag = 1;
			return "SafariFlag";
		}
		
		if (preg_match("/opera/", $browser)) {
			//Opera
			$OperaFlag = 1;
			return "OperaFlag";
		}
	}

	public function DisplayStyles()
	// 3 Jan 2013
	{
		?>
		</section>
		<aside>
		</aside>
		<style>
		* {
			margin: 0px;
			padding: 0px;
		}
		body * {
			font-family: Verdana;
			font-size: 1em;
		}

		fieldset.optionGroup {
			background: pink;
		}

		fieldset.optionGroup label {
			display: inline;
			float: none;
			width: 40px;
		}

		fieldset.optionGroup input {
			display: inline;
			float: none;
			width: 20px;
		}

		#hobbyRadioFalse {
			margin-left: 230px;
		}

		#hobbyRadioTrue {
			margin-left: 260px;
		}


		.SelectOption {
			display: block;
			float: left;
			margin-left: 14em;
			margin-top: -1.0em;
			background-color: #211;
			color: white;
		}
		
		.navigation
			{
				float: left;
				width: 100%;
				background: #333;
			}
			
			.navigation ul
			{
				margin: 0;
				padding: 0;
			}
			
			.navigation ul li
			{
				list-style-type: none;
				display: inline;
			}
			
			.navigation li a
			{
				display: block;
				float: left;
				padding: 5px 10px;
				color: #fff;
				text-decoration: none;
				border-right: 1px solid #fff;
			}
			.navigation li
			{
				color: #fff;
				text-decoration: none;
				padding: 1em;
				border-right: 1px solid #fff;
			}
			
		.navigation li a:hover {
			background: white;
			color: gold;
		}

		.action {
			font-size: 2em;
			color: pink;
		}
		p {
			color: green;
		}
		.database {
			font-size: 120%;
			color: red;
		}
		.server {
			font-size: 120%;
			color: blue;
		}
		.entryDisplay {
			background-color: #555;
			width: 14em;
			font-size: 90%;
			text-align: center;
			color: white;
		}
		.entryError {
			background-color: #555;
			background-color: #123;
			width: 14em;
			font-size: 90%;
			text-align: center;
			color: pink;
		}
		.inputReadOnly {
			position: absolute;
			margin-left: 4.2em;
			background-color: #555;
			font-size: 90%;
			text-align: center;
			color: pink;
		}
		
		.inputSpecial {
			position: absolute;
			font-size: 90%;
			margin-left: 4.1em;
			background-color: #211;
			color: white;
		}
		.inputDisplay {
			position: absolute;
			font-size: 90%;
			margin-left: 2.9em;
			background-color: #211;
			color: white;
		}
		.imgHobbyShots {
			position: absolute;
			margin-top: 80px;
			margin-left: 150px;
		}
		.inputError {
			position: absolute;
			font-size: 90%;
			margin-left: 4.1em;
			background-color: #823;
			color: pink;
		}
		.CookieName {
			font-size: 2em;
			color: pink;
		}
		#CookieName {
			font: purple;
		}
		.action {
			font-size: 120%;
			color: red;
		}
		#gMaps {
			position: absolute;
			width: 200px;
			height: 200px;
			left: 800px;
			left: 740px;
			left: 780px;
			top: 50px;
			background-color: pink;
		}
		div .entry {
			width: 800px;
			height: 30px;
			margin: 0 auto;
			background-color: blue;
			color: purple;
		}
		div .view {
			position: relative;
			background-color: yellow;
			width: 25px;
			height: 25px;
		}
		div .edit {
			position: relative;
			background-color: #111;
			width: 25px;
			height: 25px;
		}
		div .modify {
			position: relative;
			background-color: #111;
			width: 25px;
			height: 25px;
		}
		.details {
			color: #fff;
			width: 200px;
		}
		h1 {
			font-size: 25px;
		}
		.urlOLD {
			text-decoration: none;
			list-style-type: disc;
		}
		.urlOLD a {
			text-decoration: none;
			list-style-type: disc;
		}
		.urlOLD a:link {
			color: gold;
		}
		.urlOLD a:visited {
			color: gold;
		}
		.urlOLD a:hover {
			color: #111;
			border: 1px solid red;
		}
		.urlOLD a:active {
			color: gold;
		}
		.navigation {
			float: left;;
			width: 100%;
			padding-top: 5px;
			padding-bottom: 5px;
			background: #333;
		}
		
		li {
			text-decoration: none;
			list-style-type: disc;
			
			font: #987;
		}
		footer {
			clear:both;
		}
		</style>
		<?php
	}
	
	public function DisplayFooterNew()
	// 3 Jan 2013
	{
		?>
		</div>
		<footer>
		<address>
		</address>
		</footer>
		<?php
	}
}
