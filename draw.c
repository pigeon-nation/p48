#include <stdio.h>
#include "types.h"
#include <string.h>

// WINDOWS/UNIX TERMINAL HEIGHT
// i know the game is not windows compatable, but this is some generic code i like to use.
// ----------------------------
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

void get_termsize(int *rows, int *columns) {
    #if defined(_WIN32) || defined(_WIN64)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        *columns = 100;
        *rows = 100;
    }
    #else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != -1) {
        *columns = w.ws_col;
        *rows = w.ws_row;
    } else {
        *columns = 100;
        *rows = 100;
    }
    #endif
}
// ----------------------------

// clear the screen, preserving what was on it before the clear by padding with \n
void clear() {
	int rows;
	int cols;
	
	get_termsize(&rows, &cols);

	// pad screen
	for (int i = 0; i < rows; i++) {
		printf("\n");
	}

	// reset visible term
	printf("%c%c", ESCAPE, ESCAPE_CLEAR_SCREEN);
}

// print the "game by pigeon nation" header
void print_header(char key) {
	printf("2048 by Pigeon Nation\n");
	printf("Press \"q\" to quit.\n");
	if (key == HEADER_INIT) {
		printf("Use arrows or WASD to control.\n\n");
	} else {
		printf("Latest Keypress: %c\n\n", key);
	}
}

// set the text colour to ANSI COLOUR int(color_code)
void set_ansi_color(int color_code) {
    if (color_code >= 0 && color_code <= 255) {
        printf("\033[38;5;%dm", color_code);
    } else {
        printf("error: invalid ANSI 256 color code (%d) - code must be between 0 and 255.\n", color_code);
    }
}

// set the screen colour to that required by int(num). does not reset the colour, or print the int.
void setcolor(int num) {
	switch (num) {
		case 2: 
			set_ansi_color(DARKRED);
			break;
		case 4:
			set_ansi_color(RED);
			break;
		case 8:
			set_ansi_color(PINKRED);
			break;
		case 16:
			set_ansi_color(DARKPINKRED);
			break;
		case 32:
			set_ansi_color(PINK);
			break;
		case 64:
			set_ansi_color(LIGHTPINK);
			break;
		case 128:
			set_ansi_color(LIGHTORANGE);
			break;
		case 256:
			set_ansi_color(ORANGE);
			break;
		case 512:
			set_ansi_color(LIGHTGOLD);
			break;
		case 1024:
			set_ansi_color(GOLD);
			break;
		case 2048:
			set_ansi_color(YELLOW);
			break;
		case 4096:
			set_ansi_color(RED);
			printf(BLINKING);
			break;
		default: // . char colouring
			set_ansi_color(DOTWHITE);
			break;
	}
}

// draw the board.
void draw(Board board) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			setcolor(board.array[i][j]);
			if (!(board.array[i][j] == 0)) {
				int num = board.array[i][j];
				if (num < 10) {				// padding differes for number length
					printf("%d    ", num);
				} else if (num < 100) {
					printf("%d   ", num);
				} else if (num < 1000) {
					printf("%d  ", num);
				} else if (num < 10000) {
					printf("%d ", num);
				} else {					// support 16,385 and above (kind of... formatting errors will occour if chars of an int >= 5)
					printf("%d", num);
				}
			} else {
				printf(".    ");
			}
			printf("%s", ESCAPE_RESET);
		}
		printf("\n\n\n");
	}
}
