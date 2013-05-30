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

$title = "Steven Shepard, Web Engineering Samples";
$header = "Samples";
$City->DisplayHeader($header);
$City->DisplayStyles();
$City->DisplayBody($title);

?>
<script src="modernizr-1.5.js"></script>
<script type="text/javascript">
function init() {
	return;
}
</script>
<?php

//$mysqli = $City->ConnectDatabase();
//$City->DisplayDatabase();
//$City->DisplayServer();
$City->DisplayPopups();

/*
	Create the "program" specific sql query
*/

/*
	Display the "program" specific query results
*/

//$City->DisplayCommunityHobbyManagement();
?>
<style type="text/css">
article p:first-of-type{
	padding-top: 4em;
}
aside {
	position: relative;
	top: -11.0em;
	left: 1em;
	border-radius: 25px;
	float: right;
	width: 25%;
	background-color: lightgoldenrodyellow;
	border: 3px solid rgb(47,79,79);
	margin: 30px;
	padding: 10px;
}
.skip {
	padding-top: 1.5em;
}
article p.left {
	text-align: left;
}
article p.right {
	text-align: right;
}
article strong {
	text-align: center;
}
</style>
<article>
<p>Online HTML5 portfolio for <a href="mailto:steven.charles.shepard@hotmail.com?subject=Samples%20Response">Steven Charles Shepard</a>
</p>
<p>

</p>

<p class="skip"><a href="http://www.locoolly.com/viewtahoe.php" alt="Photo Gallery" target="_blank">Photo gallery using the JavaScript Module Pattern</a></p>

<p class="skip">
Four variations based on US ZipCode database SQL queries, in response to user selections.
</p>
<p class="skip">
Initial (or default) SQL query:
<br />
<strong>SELECT StateName, StateAbbreviation, StateID
<br />
FROM State
<br />
ORDER BY StateName ASC</strong>
<br />
<p class="skip"><a href="CityMenu.php" alt="Form Variation" target = "_blank" >Variation 1 - Selection stored within HTML form</a></p>

<p><a href="CookieMenu.php" alt="Cookie Variation" target = "_blank" >Variation 2 - Selection stored with Session cookies</a></p>

<p><a href="AjaxMenu.php" alt="AJAX Variation" target = "_blank" >Variation 3 - Selections displayed in DOM using AJAX</a></p>

<p><a href="JsonMenu.php" alt="JSON Variation" target = "_blank" >Variation 4 - Selections displayed in DOM using AJAX and JSON</a></p>

<p class="skip">
<a href="http://www.locoolly.com/Production/City/queryDatabase.php?mode=ViewState&StateAbbreviation=&CountyID=&CityID=&sid=0.098887" alt="XML Reponse" target = "_blank" >CSS Styled XML response to list of US States</a></p>

<p class="skip">
<a href="Response.json" alt="JSON Reponse" target = "_blank" >JSON response to list of Cities in Yuba County</a></p>


</article>
<aside>
<p><a href="http://radar.oreilly.com/2011/07/what-is-html5.html" alt="HTML5" target = "_blank" >HTML5</a></p>
<p><a href="http://www.css3.info/" alt="CSS3" target = "_blank" >CSS3</a></p>
<p><a href="http://www.w3schools.com/ajax/ajax_intro.asp" alt="AJAX" target = "_blank" >AJAX</a></p>
<p><a href="http://www.w3.org/TR/DOM-Level-2-Core/introduction.html" alt="DOM" target = "_blank" >DOM</a></p>
<p><a href="http://www.addyosmani.com/resources/essentialjsdesignpatterns/book/" alt="Module Pattern" target = "_blank" >JavaScript Module Pattern</a></p>
<p><a href="http://www.codeproject.com/Articles/31271/Ajax-Tutorial-for-Beginners-with-XML-JSON-Part-2" alt="JSON" target = "_blank" >JavaScript Object Notation</a></p>
</aside>
<?

$City->DisplayFooterNew();

$City->setProgramMask('$ProgramMask');
$City->getProgramMask();
?>
<script type="text/javascript">
window.onload = init;
</script>
</body>
</html>