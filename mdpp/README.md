# MDPP - Mark Down Pre Processor

This is a very simple pre processor for static markdown content,
you can write it as follows.

```

# Foo
Some text

Some other text

{
    echo "# heading from shell script"
}

```

This will generate the following markdown:

```

# Foo
Some text

Some other text

# heading from shell script

```

Anything inside of `{}` will be executed as a shell script. This is not intended to be used at runtime as it would be stupidly insecure, so don't do that! 

Your probably going to want `pandoc` to compile the markdown to html, other markdown compilers are available.

Just as a warning, if you have `{` on the start of a line, inside a  "\`\`\`"  block, it will be expanded, expect errors! 
