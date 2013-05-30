<?php
require_once('db_fns.php');
error_reporting(E_ALL);
ini_set("display_errors", 1);

	//$x = db_connect();
	$type = "Undefined";

	$mode = "";
	$StateAbbreviation = "";
	$CountyID = 0;
	$CityID = 0;

	if (isset($_GET['mode'])) {
		$mode = trim($_GET['mode']);
	}
	
	if (isset($_GET['StateAbbreviation'])) {
		$StateAbbreviation = $_GET['StateAbbreviation'];
	}
	
	if (isset($_GET['CountyID'])) {
		$CountyID = $_GET['CountyID'];
	}
	
	if (isset($_GET['CityID'])) {
		$CityID = $_GET['CityID'];
	}

	$self = $_SERVER["PHP_SELF"];
	$serve = $_SERVER["SERVER_NAME"];

	$cmd = "LocoollySelf = '$self';";
	$server = "LocoollyServer = '$serve';";

	//connect to database
	$mysqli = db_connect();

	$get_gov_sql = "
		SELECT DATABASE()
	";

	$get_gov_res = mysqli_query($mysqli, $get_gov_sql) or die(mysqli_error($mysqli));
	$num_rows = mysqli_num_rows($get_gov_res);

	$database = "unk";
	if ($num_rows > 0) {
		$gov_recs = mysqli_fetch_array($get_gov_res);
		$database = $gov_recs[0];
		}

	header("Content-Type: text/xml");
	echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	echo "<?xml-stylesheet type=\"text/css\" href=\"locoollyLogin.css\" ?>";
	echo "<querydatabaseentry>";

	if ($mode == "ViewState") {
		$get_postal_sql = "
			SELECT StateName, StateAbbreviation, StateID
			FROM State
			ORDER BY StateName
		";

		$get_postal_res = mysqli_query($mysqli, $get_postal_sql) or die(mysqli_error($mysqli));
		$postal_rows = mysqli_num_rows($get_postal_res);
	
		echo "<desc>error count</desc><error>0</error>";
		echo "<desc>Origin</desc><origin>".$self."</origin>";
		echo "<desc>query sql</desc><sql>".$get_postal_sql."</sql>";
		echo "<desc>record count</desc><count>".$postal_rows."</count>";
		echo "<desc>Server Name</desc><server>".$serve."</server>";
		echo "<desc>Database</desc><database>".$database."</database>";
	
		if ($postal_rows > 0) {
			while ($name_info = mysqli_fetch_array($get_postal_res)){
				echo "<databaselist>";

				$StateName = $name_info['StateName'];
				$StateAbbreviation = $name_info['StateAbbreviation'];
				$StateID = $name_info['StateID'];
				$sql = "
					SELECT COUNT(CountyName) AS Count
					FROM County
					WHERE StateID = ".$StateID."
				";
				$get = mysqli_query($mysqli, $sql) or die(mysqli_error($mysqli));
				$res = mysqli_fetch_array($get);
				$Count = $res['Count'];

				echo "<desc>State Abbreviation</desc><stateabbreviation>".$StateAbbreviation."</stateabbreviation>";
				echo "<desc>State Name</desc><statename>".$StateName."</statename>";
				echo "<desc>state id</desc><stateid>".$StateID."</stateid>";
				echo "<desc>County Count</desc><matrixcount>".$Count."</matrixcount>";
				//echo "<desc>Sql</desc><sql>$sql</sql>";
				echo "</databaselist>";
			}
		}
		
		}
		
	if ($mode == "ViewCounty") {
		$get_postal_sql = "
				SELECT CountyName, CountyID, S.StateAbbreviation
				FROM County
				INNER Join State S
				ON County.StateID = S.StateID
				WHERE StateAbbreviation = '".$StateAbbreviation."'
				ORDER BY CountyName
			";
	
		$get_postal_res = mysqli_query($mysqli, $get_postal_sql) or die(mysqli_error($mysqli));
		$postal_rows = mysqli_num_rows($get_postal_res);
		
		echo "<desc>error count</desc><error>0</error>";
		echo "<desc>Origin</desc><origin>".$self."</origin>";
		echo "<desc>query sql</desc><sql>".$get_postal_sql."</sql>";
		echo "<desc>record count</desc><count>".$postal_rows."</count>";
		echo "<desc>Server Name</desc><server>".$serve."</server>";
		echo "<desc>Database</desc><database>".$database."</database>";
		
		if ($postal_rows > 0) {
			while ($name_info = mysqli_fetch_array($get_postal_res)){
				echo "<databaselist>";
	
				$CountyName = $name_info['CountyName'];
				$CountyID = $name_info['CountyID'];
				$sql = "
					SELECT COUNT(CityName) AS Count
					FROM City
					WHERE CountyID = '".$CountyID."'
				";
				$get = mysqli_query($mysqli, $sql) or die(mysqli_error($mysqli));
				$res = mysqli_fetch_array($get);
				$Count = $res['Count'];
	
				echo "<desc>County Name</desc><countyname>".$CountyName."</countyname>";
				echo "<desc>County id</desc><countyid>".$CountyID."</countyid>";
				echo "<desc>County Count</desc><matrixcount>".$Count."</matrixcount>";
				echo "<desc>Sql</desc><sql>$sql</sql>";
				echo "</databaselist>";
			}
		}
	}

	if ($mode == "ViewCity") {
		$get_postal_sql = "
				SELECT CityName, CityID
				FROM City
				WHERE CountyID = '".$CountyID."'
				ORDER BY CityName
			";
	
		$get_postal_res = mysqli_query($mysqli, $get_postal_sql) or die(mysqli_error($mysqli));
		$postal_rows = mysqli_num_rows($get_postal_res);
		
		echo "<desc>error count</desc><error>0</error>";
		echo "<desc>Origin</desc><origin>".$self."</origin>";
		echo "<desc>query sql</desc><sql>".$get_postal_sql."</sql>";
		echo "<desc>record count</desc><count>".$postal_rows."</count>";
		echo "<desc>Server Name</desc><server>".$serve."</server>";
		echo "<desc>Database</desc><database>".$database."</database>";
		
		if ($postal_rows > 0) {
			while ($name_info = mysqli_fetch_array($get_postal_res)){
				echo "<databaselist>";
	
				$CityName = $name_info['CityName'];
				$CityID = $name_info['CityID'];
				$sql = "
					SELECT COUNT(PostalCode) AS Count
					FROM PostalCode
					WHERE CityID = '".$CityID."'
				";
				$get = mysqli_query($mysqli, $sql) or die(mysqli_error($mysqli));
				$res = mysqli_fetch_array($get);
				$Count = $res['Count'];
	
				echo "<desc>City Name</desc><cityname>".$CityName."</cityname>";
				echo "<desc>City id</desc><cityid>".$CityID."</cityid>";
				echo "<desc>City Count</desc><matrixcount>".$Count."</matrixcount>";
				echo "<desc>Sql</desc><sql>$sql</sql>";
				echo "</databaselist>";
			}
		}
	}

	echo "</querydatabaseentry>";

	mysqli_close($mysqli);
