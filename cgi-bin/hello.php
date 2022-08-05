#!/usr/local/bin/php
<html>
<head>
<title>CGI_POST</title>
<body>
<?php
echo ("|" . $_GET[0] . "|");
$env = $_SERVER["REQUEST_METHOD"];
echo ($env);
echo("<br>");
if ($env == "GET")
{
	echo 'Bonjour ' . htmlspecialchars($_GET["name"]) . '!';
}
else
	$query = stream_get_contents(STDIN);?>
<br>
<?php
echo("boouh");
?><br>
</body>
</html>
