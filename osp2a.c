#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>


#define NUM_THREADS 3

//*********************************************************
//
// Type Declarations
//
//*********************************************************
typedef enum {CONSONANT, VOWEL, OTHER} word_type;
struct thread_args {
	int argc;
	word_type mode;
	char **argv;
} thread_args;

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
void *count_word(void *param);
void yield(int i);

//*********************************************************
//
// Global variables
//
//*********************************************************
int position = 1;

//*********************************************************
//
// Main Function
//
//*********************************************************
int main(int argc, char *argv[]) {

	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr[NUM_THREADS];
	struct thread_args* args[NUM_THREADS];
	int i;

	if (argc < 2) {
		fprintf(stderr,"usage: osp2a <input> ...\n");
		return -1;
	}
	for (i = 0; i < NUM_THREADS; i++) {
		args[i] = (struct thread_args*) malloc(sizeof(thread_args));
		args[i]->argc = argc;
		args[i]->mode = i;
		args[i]->argv = argv;
	}

	for (i = 0; i < NUM_THREADS; i++) {
		pthread_attr_init(&attr[i]);
		pthread_create(&tid[i], &attr[i], count_word, args[i]);
	}

	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(tid[i], NULL);
	}
	
	return 0;
}

void *count_word(void *param) {
	int i;
	struct thread_args *arg = (struct thread_args*) param;
	for (i = 1; i < arg->argc; i++) {
		char *token=arg->argv[i];
		if (!isalpha(token[0]) && arg->mode == OTHER && i == position) {
			if (strlen(token) > 0) printf("OTHER: %s\n", token);
			position++;
		} else {
			if (isalpha(token[0]) && arg->mode == CONSONANT 
				&& strcspn(&token[0], "EUAOIeuaoi") > 0 && i == position) {
				if (strlen(token) > 0) printf("CONSONANT: %s\n", token);
				position++;
			} else if (isalpha(token[0]) && arg->mode == VOWEL 
				&& !(strcspn(&token[0], "EUAOIeuaoi") > 0) && i == position) {
				if (strlen(token) > 0) printf("VOWEL: %s\n", token);
				position++;
			}
		}
		yield(i);
	}
}

void yield(int i) {
	while (i == position) {
		sched_yield();
	}
}