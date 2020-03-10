#include<stdio.h>
#include<string.h>
#define SLEN 64
#define false 0
#define true 1
#define bool int
#define allowed allowedLetters[2]
int main(int argc, char *allowedLetters[]) {
	if (argc != 3) {
		fputs("Usage:\n\t", stderr);
		fputs(allowedLetters[0], stderr);
		fputs(" <Location of dictionary> <Allowed letters>.\n", stderr);
		return 1;
	}

	int allowedLettersLen = strlen(allowed);

	// Make lowercase.
	for (int i = 0; i < allowedLettersLen; i++) {
		if (allowed[i]>'@' && allowed[i]<'[') {
			allowed[i]+=' ';
		}
	}

	FILE *dictionary = fopen(allowedLetters[1], "r");
	if (dictionary == NULL) {
		fputs("Error reading dictionary.\n", stderr);
		return 1;
	}
	char word[SLEN];

	while (fgets(word, SLEN, dictionary) != NULL) {
		bool LetterNotValid;
		/* loop through all the letters of word
		 *        last letter is newline
		 *                    |
		 */for (int i = 0, l = strlen(word) - 1; i < l; i++) {
			LetterNotValid = true;
			//loop through all allowed letters
			for (int j = 0; j < allowedLettersLen; j++)
				//check if word[i] is an allowed letter
				if (word[i] == allowed[j]) {
					LetterNotValid = false;
					break;
				}
			if (LetterNotValid)
				goto endOfLoop;
		}
		fputs(word, stdout);
		endOfLoop: /*/*/;
	}

	fclose(dictionary);

	return 0;
}
