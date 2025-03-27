#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

// enable raw shell
void enable_raw() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// disable raw shell
void disable_raw(struct termios original) {
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
}

// get the keyboard input
char get_key(char buffer[]) {
	//printf("keycall %c\n", buffer[0]);
	if (buffer[0] == '\033' && buffer[1] == '[') {
        switch (buffer[2]) {
            case 'A': return KEY_UP;
            case 'B': return KEY_DOWN;
            case 'C': return KEY_RIGHT;
            case 'D': return KEY_LEFT;
            default: return KEY_FAIL;
        }
    } else {
    	return buffer[0];
    }
}

