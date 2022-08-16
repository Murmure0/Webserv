#!/usr/local/bin/php
<html>
<head>
<title>CGI_POST</title>
<body>
<?php
$arr=getenv();
foreach ($arr as $key=>$val)
echo "$key=>$val
";?>
<br>
<?php
echo("boouh");
?><br>
</body>
</html>
