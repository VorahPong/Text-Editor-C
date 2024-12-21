/*
    Name: Vorahpong, Mean
    Begin Date: Dec, 21, 2024
    Description: This is a Text Editor app build from scratch following GitHub Project Based Learning.
*/

#include <unistd.h>
#include <termios.h>

struct termios original_termios;    // stored the original setting of terminal

/*
    enableRawMode() function will turn off echo in terminal 
*/
void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO); // flip bits
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/*
    disableRawMode() will return the terminal to it's original state
*/
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

/*
    main() is a starting point
*/
int main() {
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}