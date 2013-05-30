<?php
require_once('../db_fns.php');
error_reporting(E_ALL);
ini_set("display_errors", 1);
/* 
 * Example to illustrate the use of the class 
 */ 
//Include the file containing the class 
include "queryToJson.class.php";
$mysqli = db_connect();
$get_gov_sql = "
		SELECT CityName, CountyID FROM City
		ORDER BY CityName
		LIMIT 15
	";

$result = mysqli_query($mysqli, $get_gov_sql) or die(mysqli_error($mysqli));
//perform a query 
//$result = mysql_query("select * from foo"); 
//create a new QueryToJson object 
$jsonQuery = new QueryToJson; 
//Use the function to get the JSON sring 
$jsonObject = $jsonQuery->queryToJson($result, "foo"); 
?>
