#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "arg.h"

typedef struct script {
	char *where;
	size_t length;
} script; 

static char *input;
static script *scripts;
static int scriptc;

static void
die(const char *msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

static void
usage() {
	fprintf(stderr, "usage %s: [-h] [-o outfile] [file]\n", argv0);
	exit(1);
}

static void
readinput(FILE *f) {
	size_t cap = 128, i;
	char c;

	input = malloc(cap);

	for (i = 0; (c = getc(f)) != EOF ; i++) {
		if (i > cap - 1) 
			input = realloc(input, (cap *= 1.5));

		input[i] = c;
	}
	input[i] = '\0';
}

static int
isstart(char c, size_t pos) {
	return (input[pos] == c && /* is this the char we were looking for */
			(
			(pos == 0 || input[pos - 1] == '\n') /* are we on the start of a line */
			)
			);
}

static int
findscript() {
	static size_t pos;
	script sc = (script){0, -1};

	for (; pos < strlen(input); pos++) {
		if (isstart('{', pos)) {
			sc.where = &input[pos + 1];
			sc.length = 0;
		} else if (isstart('}', pos)) {
			if (sc.length == -1) 
				die("attempting to close unopened script");
			sc.length = &input[pos] - sc.where;
			pos++;

			scripts = realloc(scripts, sizeof(script) * ++scriptc);
			scripts[scriptc - 1] = sc;
			return 1;
		}
	}

	return 0;
}

static void 
execute(script sc, FILE *out) {
	char *tmpname;
	FILE *prog, *tmp;
	char template[] = "/tmp/XXXXXX";
	char c;

	tmpname = mktemp(template);
	tmp = fopen(tmpname, "w+");
	
	fprintf(tmp, "#!/bin/bash\n");
	fprintf(tmp, "%.*s\n", (int)sc.length, sc.where);
	fclose(tmp);

	chmod(tmpname, S_IRUSR | S_IXUSR);

	prog = popen(tmpname, "r");

	while ((c = getc(prog)) != EOF)
		putc(c, out);

	pclose(prog);
	remove(tmpname);
}

static void
format(FILE *out) {
	for (int i = 0; i < strlen(input); i++) {
		for (int j = 0; j < scriptc; j++) {
			if (scripts[j].where == &input[i]) {
				execute(scripts[j], out);
				i += scripts[j].length;
			}
		}
		if (!isstart('{', i) && !isstart('}', i))
			putc(input[i], out);
	}
}

int 
main(int argc, char **argv) {
	FILE *in, *out = stdout;
	char *outname = NULL;

	ARGBEGIN {
	case 'o':
		outname = EARGF(usage());
		break;
	case 'h':
	default:
		usage();
	} ARGEND;

	if (argc == 0) 
		in = stdin;
	else if (argc == 1) {
		in = fopen(argv[argc - 1], "r");
		if (!in) 
			die("Couldn't open in file");
	} else 
		usage();

	if (outname) {
		out = fopen(outname, "w");
		if (!out) 
			die("Couldn't open out file");
	}

	readinput(in);

	while (findscript()) ;

	format(out);

	free(scripts);
	fclose(in);
	free(input);
}
