#!/usr/bin/python)

# Import modules for CGI handling
import cgi

# Create instance of FieldStorage
form = cgi.FieldStorage()
print(form)

# # Get data from fields
# user_name = form.getvalue('user_name')
# user_message  = form.getvalue('user_message')

# print ("<html>")
# print ("<head>")
# print ("<title>Webserv CGI</title>")
# print ("</head>")
# print ("<body>")
# print ("<h2>Hello %s</h2>" % (user_name,))
# print ("<p>Le message est : %s</p>" % (user_message))
# print ("</body>")
# print ("</html>")
