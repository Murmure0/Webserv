from os import walk

def generate_file_div(files):
	s = "<ul class=''>"
	for f in files:
		s += f"""<li><a href="/uploads/{f}" download>{f}</a></li>"""
	s += "</ul>"
	return s

f = []
for (dirpath, dirnames, filenames) in walk("./website/uploads"):
	f.extend(filenames)

print(f"""
<html>
<head>
<link rel="stylesheet" href="/static/index.css">
<link rel="stylesheet" href="/static/delete.css">
<link rel="stylesheet" href="/static/download.css">
</head>
<body>
<section>
<h1>Click on the file you want to download</h1>
{generate_file_div(f)}
</section>
</body>
<script src="/static/delete.js"></script>
</html>
""")
