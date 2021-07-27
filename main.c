/*
 *        Project:  ish
 *       Filename:  main.c
 *
 *    Description:  A shell from scratch
 *
 *        Version:  0.1a
 *        Created:  2021-07-27 17:47
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>

/*#include "builtins.h"*/

int execute (char** args) {
}

#define ISH_TOKEN_BUFFSIZE 64
#define ISH_TOKEN_DELIM " \t\r\n\a"
char** tokenise (char* line) {
}

#define ISH_RL_BUFFER_SIZE 1024
char* read_line () {
	int buffsize = ISH_RL_BUFFER_SIZE;
	int position = 0;
	char* buffer = malloc (sizeof (char) * buffsize);
	int c;

	if (!buffer) {
		fprintf (stderr, "ish: allocation error\n");
		exit (EXIT_FAILURE);
	}

	while (1) {
		c = getchar ();

		if (c == EOF || c == '\n') {
			buffer[position] = '\0';
			return buffer;
		}
		else {
			buffer[position] = c;
		}
		position++;

		if (position >= buffsize) {
			buffsize += ISH_RL_BUFFER_SIZE;
			buffer = realloc (buffer, buffsize);

			if (!buffer) {
				fprintf (stderr, "ish: allocation error\n");
				exit (EXIT_FAILURE);
			}
		}
	}
}

void loop () {
	char* line;
	char** args;
	int status = 1;

	do {
		printf ("> ");
		line = read_line ();
		printf ("%s\n", line);
		args = tokenise (line);
		status = execute (args);
		free (line);
		free (args);
	} while (status);
}

int main (int argc, char *argv[]) {
	loop ();
	return EXIT_SUCCESS;
}
