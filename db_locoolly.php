<?php

function db_connect()
{
	$result = new mysqli("web", "acct", "passwd", "db");
	
	   if (!$result) 

     throw new Exception('Could not connect to database server');
else
     return $result;
}

?>
