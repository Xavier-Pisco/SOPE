#include "termios.h"
#include "unistd.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

#define READ_SIZE 50

int copy_directory(char *dir1, char *dir2);
int copy_file(char* source, char* dest);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf( stderr, "Usage: %s dir_name dir_name\n", argv[0]);
        exit(1);
    }
    return copy_directory(argv[1], argv[2]);
} 

int copy_directory(char *d1, char *d2){
    
    DIR* dir1, *dir2;
    struct stat stat_buf;
    pid_t pid;
    struct dirent *direntp1, *direntp2;
    char *current = ".", *previous = "..";
    
    if ((dir1 = opendir( d1)) == NULL)
    {
        perror(d1);
        exit(2);
    }
    if (stat(d2, &stat_buf) == -1){
        mkdir(d2, 0744);
    }
    if ((dir2 = opendir(d2)) == NULL)
    {
        perror(d2);
        exit(2);
    }
    while ((direntp1 = readdir(dir1)) != NULL)
    {
        direntp2 = readdir(dir2);
        printf("%s %s\n", d1, d2);
        if (lstat(direntp1->d_name, &stat_buf) != 0) {
            perror(d1);
            exit(3);
        }
        if (S_ISREG(stat_buf.st_mode)) {
            pid = fork();
            if (pid == 0){
                copy_file(direntp1->d_name, direntp2->d_name);
                exit(0);
            }
        }
        else if (S_ISDIR(stat_buf.st_mode)) {
            if (strcmp(d1,current) || strcmp(d1,previous)) continue;
            mkdir(d2,0744);
            direntp2 = readdir(dir2);
            copy_directory(direntp1->d_name, direntp2->d_name);
        }
    }
    closedir(dir1);
    closedir(dir2);

    exit(0);
}

int copy_file(char* source, char* dest){

    int f1, f2, nr;
    char s[READ_SIZE];
    
    f1 = open(source,O_RDONLY);
    if (f1 == -1){
        perror(source);
        return 2;
    }

    f2 = open(dest, O_WRONLY | O_CREAT, 0644);
    if (f2 == -1){
        perror(dest);
        return 2;
    }

    while((nr = read(f1,s,READ_SIZE))){
        if (nr == -1) break;
        write(f2,s,nr);
    }

    close(f1);
    close(f2);

    return 0;
} 