local ($buffer, @pairs, $pair, $name, $value, %FORM);
# Read in text
$ENV{'REQUEST_METHOD'} =~ tr/a-z/A-Z/;

if ($ENV{'REQUEST_METHOD'} eq "GET") {
   $buffer = $ENV{'QUERY_STRING'};
}

# Split information into name/value pairs
@pairs = split(/&/, $buffer);

foreach $pair (@pairs) {
   ($name, $value) = split(/=/, $pair);
   $value =~ tr/+/ /;
   $value =~ s/%(..)/pack("C", hex($1))/eg;
   $FORM{$name} = $value;
}

$user_name = $FORM{user_name};
$user_message  = $FORM{user_message};

print "<html>";
print "<head>";
print "<title>Hello.pr</title>";
print "</head>";
print "<body>";
print "<h2>Hello $user_name </h2>";
print "<p>Le message est : $user_message </p>";
print "</body>";
print "</html>";

1;
