#include <stdio.h>
#include <string.h>

#define NUM_ROWS 6
#define NUM_COLS 8

//*********************************************************
//
// Type Declarations
//
//*********************************************************

//*********************************************************
//
// Extern Declarations
//
//*********************************************************

//*********************************************************
//
// Function Prototypes
//
//*********************************************************
int checkBoard();
int checkDiagonal();
int checkRDiagonal();
int checkVertical();
int checkHorizontal();
int returnWinner(char current);
int checkDiagonalLine(int row, int column, int horizontal_step, int vertical_step);


//*********************************************************
//
// Global variables
//
//*********************************************************
char board[NUM_ROWS][NUM_COLS];

//*********************************************************
//
// Main Function
//
//*********************************************************


int main(int argc, char *argv[]) {
	int i;
	FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    


    if (argc < 1) {
    	fprintf(stderr, "Usage: ./osp2b <file> \n");
    	return -1;
    }
	for (i = 1; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			fprintf(stderr, "Can't find %s\n", argv[i]);
			return -1;
		}

		// get the board from file
		int row = 0;
		while ((read = getline(&line, &len, fp)) != -1) {
			// printf("Retrieved line of length %zu :\n", read);
			memcpy(board[row], line, NUM_COLS);
			board[row][NUM_COLS - 1] = '\0';
			row++;
		}

		// printf("%s\n", argv[i]);
		// for (row = 0; row < NUM_ROWS; row++) {
		// 	printf("%s\n", board[row]);
		// }
		// printf("\n\n");

		int result = checkBoard(NUM_ROWS, NUM_COLS, board);
		if (result == 0) {
			printf("NO WINNER\n");
		} else if (result == 1) {
			printf("RED WINS\n");
		} else if (result == 2) {
			printf("BLACK WINS\n");
		}

		fclose(fp);
	}

	return 0;
}

int returnWinner(char current) {
	if (current == '.') {
		return 0;
	} else if (current == 'r') {
		return 1;
	} else if (current == 'b') {
		return 2;
	} else {
		return -1;
	}
}

int checkBoard() {
	int diagonal = checkDiagonal();
	int rDiagonal = checkRDiagonal();
	int horizontal = checkHorizontal();
	int vertical = checkVertical();

	int result = diagonal | rDiagonal | horizontal | vertical;
	return result;
}

int checkDiagonalLine(int row, int column, int horizontal_step, int vertical_step) {

	char current = '\0';
	int count = 0;
	while (row < NUM_ROWS && row >= 0
		&& column < NUM_COLS - 1 && column >= 0
		&& count != 4) {

		if (current != board[row][column]) {
			current = board[row][column];
			count = 1;
		} else {
			if (current != '.') {
				count++;
			}
		}
		row += vertical_step;
		column += horizontal_step;
	}
	if (count == 4) {
		return returnWinner(current);
	}
	return 0;
}

int checkDiagonal() {
	int row;
	int column = 0;
	int result = 0;
	for (row = NUM_ROWS - 4; row >= 0; row--) {
		result = result | checkDiagonalLine(row, column, 1, 1);
	}
	row = 0;
	for (column = 0; column < NUM_COLS - 4; column++) {
		result = result | checkDiagonalLine(row, column, 1, 1);
	}
	return result;
}

int checkRDiagonal() {
	int result = 0;

	int row;
	int column = 0;
	for (row = NUM_ROWS - 1; row >= 3; row--) {
		result = result | checkDiagonalLine(row, column, 1, -1);
	}
	row = NUM_ROWS - 1;
	for (column = 1; column < NUM_COLS - 4; column++) {
		result = result | checkDiagonalLine(row, column, 1, -1);
	}
	return result;
}

int checkHorizontal() {
	int row;
	for (row = 0; row < NUM_ROWS; row++) {
		int column;
		char current = board[row][0];
		int count = 1;
		for (column = 1; column < NUM_COLS && count != 4; column++) {
			if (current != board[row][column]) {
				current = board[row][column];
				count = 1;
			} else {
				if (current != '.') {
					count++;
				}
			}
		}
		if (count == 4) {
			return returnWinner(current);
		}
	}
	return 0;
}

void *checkHorizontalThread(void *param) {
	
}

int checkVertical() {
	int column;
	for (column = 0; column < NUM_COLS - 1; column++) {
		int row;
		char current = board[0][column];
		int count = 1;
		for (row = 1; row < NUM_ROWS && count != 4; row++) {
			if (current != board[row][column]) {
				current = board[row][column];
				count = 1;
			} else {
				if (current != '.') {
					count++;
				}
			}
		}
		if (count == 4) {
			return returnWinner(current);
		}
	}

	return 0;
}