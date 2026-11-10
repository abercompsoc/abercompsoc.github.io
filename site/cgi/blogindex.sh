#!/bin/sh

echo "Content-Type: text/html"
echo 

echo "<h1>Compsocs epic blogs</h1>"

for blog in $(ls /var/blogs); do
	title=$(basename -s ".md" $blog)
	loc="/cgi/blog.sh?$blog"
	echo "<a href='$loc'>$title</a>"
done
