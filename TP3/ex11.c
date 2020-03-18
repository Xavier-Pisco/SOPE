#include "stdio.h"
#include "stdlib.h"
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "termios.h"
#include "unistd.h"
#include <sys/stat.h>
#include <fcntl.h>

void write_out(char* s, int i){
    write(STDOUT_FILENO, s, i);
}

int main(){
    size_t MAX_STR_SIZE = 50;
    char *prompt = "minish > ";
    char *next_command = malloc(sizeof(char)*MAX_STR_SIZE);
    char *parsed_command;
    char *command[MAX_STR_SIZE];
    char *args[MAX_STR_SIZE];
    int prompt_no = 9, i, tmp_file, file;
    write_out(prompt, prompt_no);
    getline(&next_command, &MAX_STR_SIZE, stdin);

    while(strcmp(next_command,"quit")){
        i = 0;
        parsed_command = strtok(next_command, " \n");
        while(parsed_command != NULL){
            command[i++] = parsed_command;
            parsed_command = strtok(NULL, " \n");
        }
        command[i] = NULL;
        if (i > 2 && strcmp(command[i - 2],"-o")){
            tmp_file = dup(STDIN_FILENO);
            file = open(command[i - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(STDIN_FILENO, file);
            for (int n = 0; n < i - 2; n++){
                args[n] = command[n];
            }
            if (fork() == 0) {
                execvp(args[0], &args[0]);
                exit(0);
            }
            wait(NULL);
            dup2(tmp_file, STDIN_FILENO);
            close(file);
            close(tmp_file);
        } else {
            if (fork() == 0){
                execvp(command[0], &command[0]);
                exit(0);
            } else 
                wait(NULL);
        }
        write_out(prompt, prompt_no);
        getline(&next_command, &MAX_STR_SIZE, stdin);
    }

}