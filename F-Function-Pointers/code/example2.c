#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void handleRandom(int random, int (*fn) (int)) {
	printf("My number is: ");
	fn(random);
}

int handleOdd(int random) {
	printf("%d (from %d)\n", random, random);
	return 0;
}

int handleEven(int random) {
	printf("%d (from %d)\n", random/2, random);
	return 0;
}


int main(void) {
	srand(time(NULL));

	int i;
	for (i = 0; i<10; i++) {
		int random = rand()%10;

		if (random%2==0)
			handleRandom(random, &handleEven);
		else
			handleRandom(random, handleOdd);
	}

}
