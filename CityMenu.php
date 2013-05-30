<?php
session_start();
error_reporting(E_ALL);
ini_set("display_errors", 1);

require_once('City.inc');
require_once('db_locoolly.php');

$City = new City();

$IEflag = 0;
$FireFoxFlag = 0;
$SafariFlag = 0;
$OperaFlag = 0;
$ChromeFlag = 0;
$City->queryBrowser();

$title = "Community Management Menu";
$header = "Locoolly Data Entry";
$City->DisplayHeader($header);
$City->DisplayStyles();
$City->DisplayBody($title);

?>
<script type="text/javascript">
function init() {
	return;
}
</script>
<?php

$mysqli = $City->ConnectDatabase();
$City->DisplayDatabase();
$City->DisplayServer();
$City->DisplayPopups();

/*
	Create the "program" specific sql query
*/

/*
	Display the "program" specific query results
*/

$City->DisplayCommunityHobbyManagement();

$City->DisplayFooterNew();

$City->setProgramMask('$ProgramMask');
$City->getProgramMask();
?>
<script type="text/javascript">
window.onload = init;
</script>
</body>
</html>