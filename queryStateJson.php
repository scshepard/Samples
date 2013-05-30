<?php
require_once('db_fns.php');
error_reporting(E_ALL);
ini_set("display_errors", 1);
// decode JSON string to PHP object
//$decoded = json_decode($_GET['json']);
//$encoded = json_encode($json);
	//$x = db_connect();
	
	$type = "Undefined";

	class ResultSet {
		var $resultSet = array();

		function set_results($initial) {
			$this->resultSet[] = $initial;
		}

		function add_results($resultSet) {
			$this->resultSet[] = $resultSet;
		}

		function get_results() {
			return $this->results;
		}
	}

	$city = new ResultSet();

	$StateAbbreviation = "";

	if (isset($_GET['StateAbbreviation'])) {
		$StateAbbreviation = $_GET['StateAbbreviation'];
		//echo "StateAbbreviation : $StateAbbreviation";
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

	//header('Content-type: application/json');
	$temp = array(); 

	$get_gov_sql = "
		SELECT StateName, StateAbbreviation, StateID
		FROM State
		ORDER BY StateName
	";

	$get_gov_res = mysqli_query($mysqli, $get_gov_sql) or die(mysqli_error($mysqli));
	$num_rows = mysqli_num_rows($get_gov_res);

	$first = true;

	/*
	$city->set_count($num_rows);
	$city->set_error(0);
	$city->get_count();
	$city->set_origin($self);
	$city->set_server($serve);
	$city->set_database($database);
	$city->set_sql($get_gov_sql);
	$city->get_sql();
	*/

	echo "[";
	while($rec = mysqli_fetch_assoc($get_gov_res)) {
		if ($first) {
			echo "{";
			$first = false;
		} else {
			echo ",{";
		}

		$StateName = $rec['StateName'];
		$StateAbbreviation = $rec['StateAbbreviation'];
		$StateID = $rec['StateID'];

		$sql = "
			SELECT COUNT(CountyName) AS Count
			FROM County
			WHERE StateID = ".$StateID."
		";

		$get = mysqli_query($mysqli, $sql) or die(mysqli_error($mysqli));
		$res = mysqli_fetch_array($get);
		$Count = $res['Count'];

		$temp['Count'] = $Count;
		$rec = array_merge($rec,$temp);

		$enc = json_encode($StateName);
		$StateID = json_encode($StateID);
		$Count = json_encode($Count);
		$chunk = "\"StateName\":$enc,\"StateID\":$StateID,\"Count\":$Count";
		echo $chunk;

		/*
			":[{"StateName":"Alabama","StateAbbreviation":"AL","StateID":"24"},
			$city->add_results($rec);
		*/

		/*
			0":"15","Count":"15"},{"0":"75","Count":"75"},{"0":"58","Count":"58"},{"0":"64","Count
			$city->add_results($res);
		*/

		/*
			":["67","27","15","75
			$city->add_results($Count);
		*/

		echo "}";
		}

	//$data = json_encode($city);
	//echo $data;
	echo "]";

