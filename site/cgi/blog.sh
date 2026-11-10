#!/bin/sh

echo "Content-Type: text/html"
echo 
echo "$(pandoc /var/www/README.md)"
echo "<pre>$REMOTE_ADDR</pre>"

