#!/bin/sh

echo "Content-Type: text/html"
echo 

echo "<meta charset='utf8'>"

! [ -z "$QUERY_STRING" ] ||  (echo "<h1>no blog given</h1>" && exit 1)

blog="/var/blogs/${QUERY_STRING}"

[ -e "$blog" ] ||  (echo "<h1>invalid blog $QUERY_STRING</h1>" && exit 1)

pandoc "$blog"
