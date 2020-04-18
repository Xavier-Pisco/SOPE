#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

#define READ_SIZE 512
#define MAX_DIR_PATH 512

struct Paths{
    char* source, *dest;
};

void *copy(void * threadargs){
    int f1, f2, nr;
    char s[READ_SIZE];
    struct Paths * paths;
    paths = (struct Paths *) threadargs;

    f1 = open(paths->source,O_RDONLY);
    if (f1 == -1){
        perror(paths->source);
        return NULL;
    }

    f2 = open(paths->dest, O_WRONLY | O_CREAT, 0644);
    if (f2 == -1){
        perror(paths->dest);
        return NULL;
    }

    while((nr = read(f1,s,READ_SIZE))){
        if (nr == -1) break;
        write(f2,s,nr);
    }

    close(f1);
    close(f2);

    return NULL;
}

int main(int argc, char* argv[]){
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    if (argc != 2)
    {
        fprintf( stderr, "Usage: %s dest_dir_name\n", argv[0]);
        exit(1);
    }
    if ((dirp = opendir(".")) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }
    while ((direntp = readdir( dirp)) != NULL)
    {
        if (lstat(direntp->d_name, &stat_buf) != 0) {
            perror(argv[1]);
            exit(3);
        }
        if (S_ISREG(stat_buf.st_mode)) {
            char path[MAX_DIR_PATH];
            strcpy(path, argv[1]);
            strcat(path, "/");
            strcat(path, direntp->d_name);
            pthread_t thread;
            struct Paths *paths = malloc(sizeof(struct Paths *));
            paths->source = direntp->d_name;
            paths->dest = path;
            pthread_create(&thread, NULL, copy, (void *) paths);
            pthread_join(thread, NULL);
        }
        else {
            continue;
        }
    }
    closedir(dirp);
    pthread_exit(0);
}