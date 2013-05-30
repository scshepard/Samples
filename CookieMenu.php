<?php
session_start();
error_reporting(E_ALL);
ini_set("display_errors", 1);

$_SESSION['ref'] = "CookieMenu.php";
require_once('Cookie.inc');
require_once('db_locoolly.php');

$Cookie = new Cookie();

$IEflag = 0;
$FireFoxFlag = 0;
$SafariFlag = 0;
$OperaFlag = 0;
$ChromeFlag = 0;
$Cookie->queryBrowser();

$title = "Community Management Menu";
$header = "Locoolly Data Entry";
$Cookie->DisplayHeader($header);
$Cookie->DisplayStyles();
$Cookie->DisplayBody($title);

?>
<script type="text/javascript">
function init() {
	return;
}
</script>
<?php

$mysqli = $Cookie->ConnectDatabase();
$Cookie->DisplayDatabase();
$Cookie->DisplayServer();
$Cookie->DisplayPopups();

/*
	Create the "program" specific sql query
*/

/*
	Display the "program" specific query results
*/

$Cookie->DisplayCommunityHobbyManagement();

$Cookie->DisplayFooterNew();

$Cookie->setProgramMask('$ProgramMask');
$Cookie->getProgramMask();
?>
<script type="text/javascript">
window.onload = init;
</script>
</body>
</html>