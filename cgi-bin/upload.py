import cgi, os

try:
	form = cgi.FieldStorage()
	fileitem = form["file1"]
	path = "website/uploads/"


	isExist = os.path.exists(path)

	if not isExist:
		os.makedirs(path)

	if fileitem.filename:
		fn = os.path.basename(fileitem.filename)
		open(path + fn, 'wb').write(fileitem.file.read())
		message = "The file '" + fn + "' was uploaded successfully with python"

	else:
		message = "No file was uploaded"

	print (f"""
	<html><body>
	<p>{message}</p>
	<a href="/example_pages/page_to_upload.html">Upload an other file</a>
	</br>
	<a href="/">Return home</a>
	</body></html>
	""" )
except:
	print("Please don't be mean with me...")
