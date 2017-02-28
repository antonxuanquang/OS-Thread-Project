#include <stdio.h>

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

//*********************************************************
//
// Global variables
//
//*********************************************************

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
    char board[NUM_ROWS][NUM_COLS];
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
		printf("%s\n", argv[i]);
		int row = 0;
		while ((read = getline(&line, &len, fp)) != -1) {
			// printf("Retrieved line of length %zu :\n", read);
			memcpy(board[row], line, NUM_COLS);
			board[row][NUM_COLS - 1] = '\0';
			row++;
		}

		for (row = 0; row < NUM_ROWS; row++) {
			printf("%s\n", board[row]);
		}
		printf("\n\n");

		fclose(fp);
	}
	return 0;
}