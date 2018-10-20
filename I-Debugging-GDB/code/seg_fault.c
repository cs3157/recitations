#include <stdio.h>

int main() {
	char *str;

	char a[2];
	a[0] = 'z';
	a[1] = '\0';
	printf("%s\n", a);

	str = "hi";

	*(str+1) = 'n';
	return 0;
}

