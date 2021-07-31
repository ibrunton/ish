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
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtins.h"
/*
 * List of builtin commands
 * Followed by their functions
 */
char *builtin_str[] = {
	"cd",
	"exit",
	"version"
};

int (*builtin_func[]) (char **) = {
	&ish_cd,
	&ish_exit,
	&ish_version,
};

int ish_num_builtins () {
	return sizeof (builtin_str) / sizeof (char *);
}

/* Launches external programs
 */
int ish_launch (char** args) {
	pid_t pid, wpid;
	int status;

	pid = fork ();
	if (pid == 0) {
		// Child process
		if (execvp (args[0], args) == -1) {
			perror ("ish");
		}
		exit (EXIT_FAILURE);
	}
	else if (pid < 0) {
		/* Error forking */
		perror ("ish");
	}
	else {
		do {
			wpid = waitpid (pid, &status, WUNTRACED);
		} while (!WIFEXITED (status) && !WIFSIGNALED (status));
	}

	return 1;
}

/* If command is a built-in, do it.
 * Otherwise, call ish_launch for external programs.
 */
int ish_execute (char** args) {
	int i;

	if (args[0] == NULL) { /* an empty command was entered */
		return 1;
	}

	for (i = 0; i < ish_num_builtins (); i++) {
		if (strcmp (args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	return ish_launch (args);
}

#define ISH_TOKEN_BUFFSIZE 64
#define ISH_TOKEN_DELIM " \t\r\n\a"
char** ish_tokenise (char* line) {
	int buffsize = ISH_TOKEN_BUFFSIZE, position = 0;
	char** tokens = malloc (buffsize * sizeof (char*));
	char* token;

	if (!tokens) {
		fprintf (stderr, "ish: allocation error\n");
		exit (EXIT_FAILURE);
	}

	token = strtok (line, ISH_TOKEN_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= buffsize) {
			buffsize += ISH_TOKEN_BUFFSIZE;
			tokens = realloc (tokens, buffsize * sizeof (char*));
			if (!tokens) {
				fprintf (stderr, "ish: allocation error\n");
				exit (EXIT_FAILURE);
			}
		}

		token = strtok(NULL, ISH_TOKEN_DELIM);
	}

	tokens[position] = NULL;
	return tokens;
}

#define ISH_RL_BUFFER_SIZE 1024
char* ish_read_line () {
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
		line = ish_read_line ();
		args = ish_tokenise (line);
		status = ish_execute (args);
		free (line);
		free (args);
	} while (status);
}

int main (int argc, char *argv[]) {
	loop ();
	return EXIT_SUCCESS;
}
