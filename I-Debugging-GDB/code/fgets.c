#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	FILE *fp = fopen(*++argv, "r");
	
	fseek(fp, 2, SEEK_SET);

	char buf[10];

	while (fread(buf, sizeof(buf), 1, fp)) {
		fprintf(stdout, "%s\n", buf);
	}

	fclose(fp);
 
	char buf2[100];
	while (fgets(buf2, sizeof(buf2), stdin)) {
		int bufLength = strlen(buf2);
		printf("%d\n", bufLength);
		fprintf(stdout, "%s\n", buf2);
		fflush(stdout);
	}
}
