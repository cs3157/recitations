#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *convert(char *word, char *pig_word) {

	/*
	 * Copy second half of word to first half of pig_word
	 *
	 */
	
	int half_word_len = strlen(word)/2;
		
	strcpy(pig_word, word + half_word_len);
	
	/*
	 * Copy first half of word to second half of pig_word
	 *
	 */	
	

	int idx = 0;
	int start_idx = strlen(pig_word);
	
	while(idx < half_word_len) {
		
		pig_word[start_idx + idx + 10] = *(word + idx);
		idx++;
	}

	
	// pig_word[start_idx + idx] = 0;

	/*
	 * Append "ay" to end of pig_word
	 *
	 */

	strcat(pig_word, "ay");

	return pig_word;
}

int main(int argc, char **argv) {
	
	/*
	 * Allocate space and evaluate phrase_len using sizeof()
	 *
	 */

	char *pig_phrase[argc];
	pig_phrase[argc - 1] = NULL;

        /*
	 * iterate through phrase 
	 * we will allocate space for each word
	 * then pass that space to be filled by a convert function	
	 *
	 */	

	for (int i = 1; i < argc; i++) {

		char *word = *(argv+i);
		
		/*
		 * Allocate space for new word 
		 *
		 */

		int pig_word_len = strlen(word) + strlen("ay") + 1;

				
		// Program wont work unless we malloc 
		char *pig_word = malloc(pig_word_len * sizeof(char));

		/*
		 * Fill in array with converted pointer
		 *
		 */		

		pig_phrase[i-1] = convert(word, pig_word);	
		
	}

	/* 
	 * Iterate through and print new phrase
	 *
	 */
	char **pig_phrase_itr = pig_phrase;
	/*
	 * Question: Why do we need a char** here instead of using pig_phrase itself?
	 *
	 */
	while (*pig_phrase_itr){
		printf("%s ", *pig_phrase_itr);
		pig_phrase_itr++;
		free(*pig_phrase_itr);
	}
	printf("\n");
}
