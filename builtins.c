/*
 *        Project:  ish
 *       Filename:  builtins.c
 *
 *    Description:  
 *
 *        Version:  0.1a
 *        Created:  2021-07-27 19:41
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <unistd.h>
#include "builtins.h"

/*
 * Built-in function implementations
 */

int ish_cd (char **args) {
	if (args[1] == NULL) {
		fprintf (stderr, "ish: expected argument to `cd'\n");
	}
	else {
		if (chdir (args[1]) != 0) {
			perror ("ish");
		}
	}

	return 1;
}

int ish_exit (char **args) {
	return 0;
}

int ish_version (char **args) {
	printf ("%s %s\n", APPNAME, VERSION);
	return 1;
}
