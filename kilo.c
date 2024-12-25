/*
    Name: Vorahpong, Mean
    Begin Date: Dec, 21, 2024
    Description: This is a Text Editor app build from scratch following GitHub Project Based Learning.
*/

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

struct termios original_termios;    // stored the original setting of terminal

void die(const char * s) {
    perror(s);
    exit(1);
} 

/*
    disableRawMode() will return the terminal to it's original state
*/
void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) == -1) {
        die("tcsetattr");
    }
}

/*
    enableRawMode() function will turn off echo in terminal.
    It also called disableRawMode() when the program exits.
*/
void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &original_termios) == -1)
        die("tcgetattr");
    
    atexit(disableRawMode);

    struct termios raw = original_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); // flip bits
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
    // TCSAFLUSH will discards any unread input
}

/*
    main() is a starting point
*/
int main() {
    enableRawMode();

    while (1) {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
            die("read");
            
        if(iscntrl(c)) { // test if c is a control variable aka the ASCII code from 32-126 otherwise they are printable.
            printf("%d\r\n", c); // print numeric value of the char
        } else {
            printf("%d ('%c')\r\n", c, c); // print the char
        }
        if (c == 'q') break;
    }
    return 0;
}