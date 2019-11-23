#ifndef HOLBSHELL
#define HOLBSHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
char *_strdup(char *str);
char **_tokenize(char *str);
int _putchar(char c);
int _printR(char *str);
char *newLine(char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *pathFind(char **Enviro);
void getDirs(char **input, char **Env);
int functionExecute(char **input);
#endif