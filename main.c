#include "types.h"
#include "draw.h"
#include "logic.c"

// included for raw mode
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

#include "keyboard.h"

int main() {
	// enter raw mode
	struct termios original;
	tcgetattr(STDIN_FILENO, &original);
	enable_raw();

	// init the board
	Board board = init_board();

	// choose a random seed
	init_random();

	// create buffers and game over var
	char buffer[3]; // buffer for keyboard inputs
	bool over = false;

	// clear screen
	clear();

	print_header(HEADER_INIT);	// print the header without "last keypress"
	populate_random(&board);	// populate the first number on the board
	draw(board);				// draw the board
	printf("\n");				// print newline (padding)
	fflush(stdout);				// flush stdout (as not to have incomplete write).

	// while keyboard input...
	while (read(STDIN_FILENO, buffer, 3)) {
		// if game is over, jump to end.
		if (over == true) {
			goto close;
		}

		// get the key
		char key = get_key(buffer);

		// check if the key is valid or not.
		if (!(key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT || key == 'q' || key == 'Q' || key == KEY_FAIL)) {
			continue; // skip for new input
		}

		// check if user is quitting
		if (key == 'q' || key == 'Q') {
			goto close;
		}

		// random backspace testing
		//if (key == (char)8 || key == (char)127) {
		//	printf("\b \b");
		/*} else*/

		// flush output
		fflush(stdout);

		// do action here
		action(&board, key);

		// check if playable after action, if so populate, if not close.
		if (is_playable(board) == true) {
			clear();			// clear screen
			print_header(key);	// print header

			// add one random number (2 or 4) to the board.
			populate_random(&board);

			// draw the board to the screen.
			draw(board);

			// pad.
			printf("\n");
		} else {
			// clear the screen, print game over and show closing message.
			clear();
			printf("-- GAME OVER --\n");
			printf("Press any key to close.\n");

			// flush just in case ;)
			fflush(stdout);

			// send game over, skip rest of logic (not that there is any).
			over = true;
			continue;
		}
	}

// close case
close:
	disable_raw(original);
	printf("Closing... \n");	
	clear();
	return 0;

	// WARNSAFE
	goto error;

// error case (unused)
error:
	return -1;
}