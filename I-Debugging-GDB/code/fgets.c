#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	FILE *fp = fopen(*++argv, "r");
	
	fseek(fp, 2, SEEK_SET);

	char buf[200];

	fgets(buf, 100-1, fp);
	fprintf(stdout, "%s\n", buf);
	fflush(stdout);
	fclose(fp); 
}
