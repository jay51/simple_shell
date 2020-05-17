#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define SH_LINE_BUFFSIZE 1024
#define SH_TOK_BUFFSIZE 64
#define SH_TOK_DELIM " \t\r\n\a"


void looop_sh();
char* sh_readline();
char** sh_split_line(char* line);
int sh_execute(char** args);


// builtin cammands
int sh_cd(char** args);
int sh_exit(char** args);
int sh_help(char** args);


#define SH_BUILTIN_LENGTH 3
char* builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char**) = {
    &sh_cd,
    &sh_exit,
    &sh_help
};


int main(int argc, char** argv){

    looop_sh();

    return EXIT_SUCCESS;
}



void looop_sh() {

    char* line;
    char** args;
    int status;

    do {

        printf("sh# ");
        line = sh_readline();
        // printf("line: %s\n", line);
        args = sh_split_line(line);
        char** tmp = args;
        // while(*tmp) {
            // printf("args: %s\n", *tmp);
            // *tmp++;
        // }
        status = sh_execute(args);
        
        free(line);
        free(args);
    } while(status);
}




char* sh_readline() {

    int position = 0;
    char* buffer = malloc(sizeof(char) * SH_LINE_BUFFSIZE);
    int c;

    char* line = NULL;
    ssize_t buffsize = 0;

    if((getline(&line, &buffsize, stdin)) == -1) {

        if(feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}




char** sh_split_line(char* line){

    int position = 0;
    char* token;
    char** tokens = malloc(sizeof(char*) * SH_TOK_BUFFSIZE);

    if(!tokens) {
        perror("alocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SH_TOK_DELIM);
    while(token != NULL) {

        tokens[position] = token;
        position++;
        
        token = strtok(NULL, SH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}


int sh_launch(char** args) {

    pid_t pid, wpid;
    int status;
    pid = fork();
    if(pid == 0){
        // child process
        if(execvp(args[0], args) == -1){
            perror("execv");
        }
        exit(EXIT_FAILURE);

    } else if(pid < 0) {
        perror("fork");

    } else {

        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && WIFSIGNALED(status));
    }
    return 1;
}


// builtins are shell commands that need to run in the shell process (not fork)
int sh_cd(char** args) {

    if(args[1] == NULL) {
        fprintf(stderr, "sh: expected argument \"cd\" \n");

    } else {

        if(chdir(args[1]) != 0) {
            perror("chdir");
        }

    }

    return 1;
}


int sh_exit(char** args) { return 0; } 


int sh_help(char** args) {
    int i;
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < SH_BUILTIN_LENGTH; i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}


int sh_execute(char** args) {

    int i;

    if(args[0] == NULL) {
        return 1;
    }

    for(i = 0; i < SH_BUILTIN_LENGTH; i++) {
        if(strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }


    return sh_launch(args);
}

