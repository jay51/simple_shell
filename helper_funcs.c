#include "holberton.h"
/**
 *
 *
 *
 */
char **argDup(char **ip, char *newArg)
{
	char **manipString;
	int i, count = 0;

	for (i = 0; ip[i] != NULL; i++)
	{
		count++;
	}

	manipString = malloc(sizeof(char *) * (count + 1));
	manipString[0] = newArg;
	for (i = 1; ip[i] != NULL; i++)
	{
		manipString[i] = ip[i];
	}

	manipString[count] = NULL;

	return (manipString);
}

/**
 *checkPerm - check's the existence of a file
 *
 *@dirsWithSlash: Pointers to strings of directory with appropriate slashes
 *
 * Return: Integer to indicate success or failure
 */
char *checkPerm(char **dirsWithSlash)
{
	int i = 0;
	struct stat *buf;

	buf = malloc(sizeof(struct stat));
	while (dirsWithSlash[i] != NULL)
	{
		if (stat(dirsWithSlash[i], buf) == 0)
		{
			if (access(dirsWithSlash[i], X_OK) == 0)
			{
				return (dirsWithSlash[i]);
			}
		}
		i++;
	}
	return (dirsWithSlash[i]);
}

/**
 *
 *
 *
 */
char **command_concat(char *string1, char **dblArr)
{
	char **concatDArray;
	char **slashPath;
	char *temp;
	char *temp2;
	int i = 0, count = 0, j = 0;

	for (i = 0; dblArr[i] != NULL; i++)
	{
		count++;
	}

	slashPath = malloc(sizeof(char *) * (count + 1));
	for (i = 0; dblArr[i] != NULL; i++)
	{
		temp2 = _strdup(dblArr[i]);
		slashPath[i] = _strcat(temp2, "/");
	}

	concatDArray = malloc(sizeof(char *) * (count + 1));
	for (j = 0; dblArr[j] != NULL; j++)
	{
		temp2 = _strdup(dblArr[j]);
		slashPath[j] = _strcat(temp2, "/");
	}

	concatDArray = malloc(sizeof(char *) * (count + 1));
	for (j = 0; dblArr[j] != NULL; j++)
	{
		temp = _strdup(slashPath[j]);
		concatDArray[j] = _strcat(temp, string1);

	}
	concatDArray[count] = NULL;

	return (concatDArray);
}

/**
 *
 *
 *
 */
char **DArrDup(char **src)
{
	int i, count = 0;
	char **dest;

	for (i = 0; src[i] != NULL; i++)
	{
		count++;
	}
	dest = malloc(sizeof(char *) * (count + 1));
	for (i = 0; src[i] != NULL; i++)
	{
		dest[i] = _strdup(src[i]);
	}
	dest[count] = NULL;

	return (dest);
}

/**
 *
 *
 *
 */
char **tokenizePath(char *inPath)
{
	int i = 0, count;
	char *token;
	char **outArr;
	char *copy_src = _strdup(inPath);

	token = strtok(copy_src, ":");
	while (token != NULL)
	{
		token = strtok(NULL, ":");
		count++;
	}

	outArr = malloc(sizeof(char *) * (count + 1));
	token = strtok(inPath, ":");
	while (token != NULL)
	{
		outArr[i] = token;
		token = strtok(NULL, ":");
		i++;
	}

	outArr[count] = NULL;
	return (outArr);
}

