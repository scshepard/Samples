<?php
session_start();

error_reporting('E_ALL');
ini_set ( 'display_errors', 'On' );

function db_connect()
{
	$self = $_SERVER["PHP_SELF"];
	$serve = $_SERVER["SERVER_NAME"];
	//echo "self is : $self<br />";
	//echo "serve is : $serve<br />";
	//www.devlocmac.com

	$cmd = "LocoollySelf = '$self';";
	$server = "LocoollyServer = '$serve';";

	$pos = strpos($serve, "locoolly.com");
	if ($pos != 0) {
		//echo "doing mjlj1234<br />";
		$result = new mysqli("web", "act", "pwd", "database");
	}

	$pos = strpos($serve, "devlocmac.com");
	if ($pos != 0) {
		//echo "doing cl25341<br />";
		$result = new mysqli("web", "act", "pwd", "database");
	}

  // if ($result == "failed")
    // throw new Exception('Could not connect to database server');
   //else
     return $result;
}

?>
