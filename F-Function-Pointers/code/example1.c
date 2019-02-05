#include <stdio.h>

void runAnotherFunction( int (*fn) () ) {
	printf("Going to run fn: \n");
	fn();
	printf("Ran fn\n");
}

int wasteTime() {
	int i = 0;
	while (i<5) {
		printf("%d\n", i++);
	}

	return i;
}



int main() {
	runAnotherFunction(wasteTime);
}
