#!/bin/sh

# this script assumes follow variables exist
# 	TITLE - the title of the page
# 	PAGES - the dir that contains nested pages
# 	STYLE - the path to the style.css 
#	...

function header() {
	echo "<link rel="stylesheet" href="${STYLE}">"

	echo "<h1 id="heading-title">${TITLE}</h1>"
	echo "<title>${TITLE}</title>"

	echo "<div id="navbar">"

	for page in $(ls $PAGES); do
		echo "<a href="./pages/${page}">${PAGE}</a>"
	done

	echo "</div>" 
}

header

