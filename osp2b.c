#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

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
void *checkHorizontalThread(void *param);
void *checkVerticalThread(void *param);
void *checkDiagonalThread(void *param);
void *checkRDiagonalThread (void *param);

//*********************************************************
//
// Global variables
//
//*********************************************************
char board[NUM_ROWS][NUM_COLS];
pthread_mutex_t mutex;

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

	pthread_t tid;
	int result = 0;
	void *thread_result;
	pthread_create(&tid, NULL, checkDiagonalThread, NULL);
	pthread_join(tid, &thread_result);
	result = (int) thread_result;
	return result;
}
void *checkDiagonalThread(void *param) {
	
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
	return (void *) result;
}

int checkRDiagonal() {
	pthread_t tid;
	int result = 0;
	void *thread_result;
	pthread_create(&tid, NULL, checkRDiagonalThread, NULL);
	pthread_join(tid, &thread_result);
	result = (int) thread_result;
	return result;
}

void *checkRDiagonalThread (void *param) {
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
	return (void *) result;
}

int checkHorizontal() {
	int row;
	pthread_t tid[NUM_ROWS];
	pthread_attr_t attr[NUM_ROWS];
	int result = 0;
	void *thread_result;
	for (row = 0; row < NUM_ROWS; row++) {
		pthread_attr_init(&attr[row]);
		pthread_create(&tid[row], &attr[row], checkHorizontalThread, (void *) row);
	}

	for (row = 0; row < NUM_ROWS; row++) {
		pthread_join(tid[row], &thread_result);
		result = result | ((int) thread_result);
	}
	return result;
}

void *checkHorizontalThread(void *param) {
	int row = (int) param;
	int column;
	char current = board[row][0];
	int count = 1;
	for (column = 1; column < (NUM_COLS - 1) && count != 4; column++) {
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
		return (void *) returnWinner(current);
	}
	return (void *) 0;
}

int checkVertical() {
	int column;
	pthread_t tid[NUM_COLS - 1];
	pthread_attr_t attr[NUM_COLS - 1];
	int result = 0;
	void *thread_result;
	for (column = 0; column < NUM_COLS - 1; column++) {
		pthread_attr_init(&attr[column]);
		pthread_create(&tid[column], &attr[column], checkVerticalThread, (void *) column);
	}

	for (column = 0; column < NUM_COLS - 1; column++) {
		pthread_join(tid[column], &thread_result);
		result = result | ((int) thread_result);
	}

	return result;
}

void *checkVerticalThread(void *param) {
	int column = (int) param;
	char current = board[0][column];
	int count = 1;
	int row;
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
		return (void *) returnWinner(current);
	}
	return (void *) 0;
}