#include "termios.h"
#include "unistd.h"
#include "string.h"

#define MAX_PASS_SIZE 20

int main(){
    struct termios initial, changed;
    char pass[MAX_PASS_SIZE + 1], ch;

    write(STDOUT_FILENO, "Password: ", 10);

    tcgetattr(STDIN_FILENO, &initial);
    changed = initial;
    changed.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &changed);

    int i;

    for (i = 0; i < MAX_PASS_SIZE; i++){
        read(STDIN_FILENO, &ch, 1);
        if (ch == '\n')
            break;
        
        pass[i] = ch;
        write(STDOUT_FILENO, "*", 1);
    }
    pass[i] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &initial);
    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, pass, strlen(pass));
    write(STDOUT_FILENO, "\n", 1);
    
    return 0;
}