# compsoc website

This website is made for nginx using the nginx-cgi module, configs provided


# what is a CGI script 
CGI scripts are a fast, simple, and easy way to do web hosting. They allow you
to handle a request with a programming language of your choice. They work by calling
a script when a request is made, and responding with the `stdout` of that script. The
script has some info passed in via enviroment vairables, and the request body via 
`stdin`.

# idea

The idea for this will be to have some static html pages for index.html and such.
Then we can have them link to a blogs page, or something like that, which can run a 
script something like this:

``` 
print header + css
for each markdown file in ./blogs/ {
    write the title as a link
}
print footer
```
Which will generate an index page for all blogs

And then another script like this:

```
print header + css
compile blog to html
print footer
```
Which will generate the blog itself
