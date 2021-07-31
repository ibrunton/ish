/*
 *        Project:  ish
 *       Filename:  builtins.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021-07-27 19:41
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#ifndef BUILTINS_H
#define BUILTINS_H

/*
 * List of builtin commands
 * Followed by their functions
 */

int ish_cd (char **args);
int ish_exit (char **args);


#endif /* BUILTINS_H */
