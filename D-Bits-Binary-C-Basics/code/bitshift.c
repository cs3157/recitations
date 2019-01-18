#include <stdio.h>

int main() {

	int num = 20;
	printf("%d\n", num);
	printf("20 left-shifted: %d\n", num << 1);
	printf("20 right-shifted: %d\n", num >> 1);

	int num2 = 15;
	int num3 = 23;

	printf("15 & 23: %d\n", num3&num2);
	printf("15 | 23: %d\n", num3|num2);
}
