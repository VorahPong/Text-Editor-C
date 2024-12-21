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

struct termios original_termios;    // stored the original setting of terminal

/*
    disableRawMode() will return the terminal to it's original state
*/
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

/*
    enableRawMode() function will turn off echo in terminal.
    It also called disableRawMode() when the program exits.
*/
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &original_termios);
    atexit(disableRawMode);

    struct termios raw = original_termios;
    raw.c_lflag &= ~(ECHO | ICANON); // flip bits
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    // TCSAFLUSH will discards any unread input
}

/*
    main() is a starting point
*/
int main() {
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        
    }
    return 0;
}