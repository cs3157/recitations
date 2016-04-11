#include <stdio.h>
#include <string.h>

int main(){
	FILE *fp;
	size_t fread_val;
	char buffer[100];
	char *s1 = "hello\n";
	char *s2 = "world";

	/* fputs() / fgets() */
	printf("---------------test1---------------\n");
	fp = fopen("test", "w+");
	fputs(s1, fp); // writes 'hello\n' up to but not including '\0'
	fputs(s1, fp);
	fseek(fp, 0, SEEK_SET);

	// file currently contains 'hello\nhello\n'
	fgets(buffer, 100, fp); // case 1: stops reading line when '\n' is read
				// '\n' is read, so it is stored into the buffer
				// note that '\0' is stored after the last character in buffer
	printf("case 1: %s", buffer);
	fflush(stdout);

	FILE *fp_t1c1 = fopen("test1_case1", "w");
	// buffer currently contains 'hello\n\0' 
	fwrite(buffer, 15, 1, fp_t1c1);
	fclose(fp_t1c1);
	fseek(fp, 0, SEEK_SET);

	// file currently contains 'hello\nhello\n'
	fgets(buffer, 3, fp); // case 2: stops reading line when 3-1 characters are read
	printf("case 2: %s", buffer);
	fflush(stdout);

	FILE *fp_t1c2 = fopen("test1_case2", "w");
	// buffer currently contains 'he\0lo\n\0' 
	fwrite(buffer, 15, 1, fp_t1c2);
	fclose(fp_t1c2);
	
	fclose(fp);

	memset(&buffer[0], 0, sizeof(buffer));

	/* fwrite() / fread() */
	printf("---------------test2---------------\n");
	fp = fopen("test", "w+");
	fwrite(s1, strlen(s1), 1, fp);
	fwrite(buffer, 2, 1, fp);
	fwrite(s2, strlen(s2), 1, fp);
	fseek(fp, 0, SEEK_SET);
	// file currently contains 'hello\n\0\0world'
	fread_val = fread(buffer, strlen(s1) + 1, 1, fp); // case 1: read 7 bytes
	printf("case 1: %s", buffer);
	printf("fread return value = %zd\n", fread_val);
	printf("EOF? %d\n", feof(fp));
	fflush(stdout);
	
	FILE *fp_t2c1 = fopen("test2_case1", "w");
	// buffer currently contains 'hello\n\0' 
	fwrite(buffer, 7, 1, fp_t2c1);
	fclose(fp_t2c1);

	memset(&buffer[0], 0, sizeof(buffer));
	fseek(fp, 0, SEEK_SET);
	// file currently contains 'hello\n\0\0world'
	fread_val = fread(buffer, 100, 1, fp); // case 2: read 100 bytes (will reach EOF)
	printf("case 2: %s", buffer);
	printf("fread return value = %zd\n", fread_val);
	printf("EOF? %d\n", feof(fp));
	fflush(stdout);

	FILE *fp_t2c2 = fopen("test2_case2", "w");
	// buffer currently contains 'hello\n\0\0world' 
	fwrite(buffer, 100, 1, fp_t2c2);
	fclose(fp_t2c2);

	memset(&buffer[0], 0, sizeof(buffer));
	fseek(fp, 0, SEEK_SET);
	
	/* fwrite() vs. fputs() */
	printf("---------------test3---------------\n");
	fwrite(s2, strlen(s2), 1, fp);
	fwrite(buffer, 5, 1, fp);
	fwrite(s1, strlen(s1), 1, fp);
	
	fseek(fp, SEEK_SET, 0);
	// file currently contains 'world\0\0\0\0\0hello\n'
	fread(buffer, 15, 1, fp);
	printf("%s", buffer);
	fflush(stdout);
	fclose(fp);

	FILE *fp1 = fopen("test3_fwrite", "w");
	// buffer currently contains 'world\0\0\0\0\0hello\n' 
	fwrite(buffer, 15, 1, fp1);
	fclose(fp1);

	FILE *fp2 = fopen("test3_fputs", "w+");
	// buffer currently contains 'world\0\0\0\0\0hello\n' 
	fputs(buffer, fp2); // writes buffer to fp2 up to but not including '\0'
	fclose(fp2);

	return 0;
}
