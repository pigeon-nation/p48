#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "keyboard.h"
#include "types.h"

// init the random seed

void init_random() {
	srand(time(NULL));
}

// generate random number from range start to end stop (inclusive both ends)
int gen_random(int start, int stop) {
	return (rand() % (stop - start + 1)) + start;
}

// determine if a game is still playable
bool is_playable(Board board) {
	bool state = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board.array[i][j] == 0) {
				state = true;
				goto ret;
			}
		}
	}

ret:
	return state;
}

// populate the board with random numbers.
void populate_random(Board *board) {
	while (1) {
		int x = gen_random(0, 3);
		int y = gen_random(0, 3);

		if (board->array[x][y] == 0) {
            int n = gen_random(0, 9);
            // skewed chance to get 2 < 4, but 4 is still frequent.
            if (n < 8) {
			    board->array[x][y] = 2;
            } else {
                board->array[x][y] = 4;
            }
			break;
		} else {
			continue;
		}
	}
}

// move the numbers according the 2048 rules (hopefully).
void action(Board *board, char direction) {
    bool merged[4][4] = {false};

    switch (direction) {
        case KEY_UP:
            for (int y = 0; y < 4; y++) {
                for (int x = 1; x < 4; x++) {
                    if (board->array[x][y] != 0) {
                        int k = x;
                        while (k > 0 && board->array[k - 1][y] == 0) {
                            board->array[k - 1][y] = board->array[k][y];
                            board->array[k][y] = 0;
                            k--;
                        }
                        if (k > 0 && board->array[k - 1][y] == board->array[k][y] && !merged[k - 1][y]) {
                            board->array[k - 1][y] *= 2;
                            board->array[k][y] = 0;
                            merged[k - 1][y] = true;
                        }
                    }
                }
            }
            break;

        case KEY_DOWN:
            for (int y = 0; y < 4; y++) {
                for (int x = 2; x >= 0; x--) {
                    if (board->array[x][y] != 0) {
                        int k = x;
                        while (k < 3 && board->array[k + 1][y] == 0) {
                            board->array[k + 1][y] = board->array[k][y];
                            board->array[k][y] = 0;
                            k++;
                        }
                        if (k < 3 && board->array[k + 1][y] == board->array[k][y] && !merged[k + 1][y]) {
                            board->array[k + 1][y] *= 2;
                            board->array[k][y] = 0;
                            merged[k + 1][y] = true;
                        }
                    }
                }
            }
            break;

        case KEY_LEFT:
            for (int x = 0; x < 4; x++) {
                for (int y = 1; y < 4; y++) {
                    if (board->array[x][y] != 0) {
                        int k = y;
                        while (k > 0 && board->array[x][k - 1] == 0) {
                            board->array[x][k - 1] = board->array[x][k];
                            board->array[x][k] = 0;
                            k--;
                        }
                        if (k > 0 && board->array[x][k - 1] == board->array[x][k] && !merged[x][k - 1]) {
                            board->array[x][k - 1] *= 2;
                            board->array[x][k] = 0;
                            merged[x][k - 1] = true;
                        }
                    }
                }
            }
            break;

        case KEY_RIGHT:
            for (int x = 0; x < 4; x++) {
                for (int y = 2; y >= 0; y--) {
                    if (board->array[x][y] != 0) {
                        int k = y;
                        while (k < 3 && board->array[x][k + 1] == 0) {
                            board->array[x][k + 1] = board->array[x][k];
                            board->array[x][k] = 0;
                            k++;
                        }
                        if (k < 3 && board->array[x][k + 1] == board->array[x][k] && !merged[x][k + 1]) {
                            board->array[x][k + 1] *= 2;
                            board->array[x][k] = 0;
                            merged[x][k + 1] = true;
                        }
                    }
                }
            }
            break;

        default:
            printf("Invalid direction. (KB-IN ERROR LIKELY)\n");
            break;
    }
}

