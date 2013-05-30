<?php
session_start();
error_reporting(E_ALL);
ini_set("display_errors", 1);

$_SESSION['ref'] = "AjaxMenu.php";
require_once('Ajax.inc');
require_once('db_locoolly.php');

$Ajax = new Ajax();

$IEflag = 0;
$FireFoxFlag = 0;
$SafariFlag = 0;
$OperaFlag = 0;
$ChromeFlag = 0;
$Ajax->queryBrowser();

$title = "Community Management Menu";
$header = "Locoolly Data Entry";
$Ajax->DisplayHeader($header);
$Ajax->DisplayStyles();
$Ajax->DisplayBody($title);

?>
<?php

$mysqli = $Ajax->ConnectDatabase();
$Ajax->DisplayDatabase();
$Ajax->DisplayServer();
$Ajax->DisplayPopups();

/*
	Create the "program" specific sql query
*/

/*
	Display the "program" specific query results
*/

$Ajax->DisplayCommunityHobbyManagement();

$Ajax->DisplayFooter();

$Ajax->setProgramMask('$ProgramMask');
$Ajax->getProgramMask();
?>
<script type="text/javascript">
window.onload = init;
</script>
</body>
</html>