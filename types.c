#include <string.h>

typedef struct {
	int array[4][4];
} Board;

Board init_board() {
	// create a board
	Board board;

	// zero out the board (ensure board is zeroed)
	for (int i = 0; i < 4; i++) {
		memset(board.array[i], 0, sizeof(board.array[i]));
	}

	// debug init
	/*board.array[0][0] = 2;
	board.array[0][1] = 4;
	board.array[0][2] = 8;
	board.array[0][3] = 16;
	board.array[1][0] = 32;
	board.array[1][1] = 64;
	board.array[1][2] = 128;
	board.array[1][3] = 256;
	board.array[2][0] = 512;
	board.array[2][1] = 1024;
	board.array[2][2] = 2048;
	board.array[2][3] = 4096;
	board.array[3][0] = 0;
	board.array[3][1] = 0;
	board.array[3][2] = 0;
	board.array[3][3] = 0;*/

	// return
	return board;
}
