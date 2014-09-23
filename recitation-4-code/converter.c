#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define LINELENGTH 141

void printchar(unsigned char c) {
    if (isgraph(c)) {
        printf("%5c", c);
        return;
    }
    switch (c) {
		case 0:
			printf("%5s", "NUL");
			break;
		case 1:
			printf("%5s", "SOH");
			break;
		case 2:
			printf("%5s", "STX");
			break;
		case 3:
			printf("%5s", "ETX");
			break;
		case 4:
			printf("%5s", "EOT");
			break;
		case 5:
			printf("%5s", "ENQ");
			break;
		case 6:
			printf("%5s", "ACK");
			break;
		case 7:
			printf("%5s", "BEL");
			break;
		case 8:
			printf("%5s", "BS");
			break;
		case 9:
			printf("%5s", "HT");
			break;
		case 10:
			printf("%5s", "LF");
			break;
		case 11:
			printf("%5s", "VT");
			break;
		case 12:
			printf("%5s", "FF");
			break;
		case 13:
			printf("%5s", "CR");
			break;
		case 14:
			printf("%5s", "SO");
			break;
		case 15:
			printf("%5s", "SI");
			break;
		case 16:
			printf("%5s", "DLE");
			break;
		case 17:
			printf("%5s", "DC1");
			break;
		case 18:
			printf("%5s", "DC2");
			break;
		case 19:
			printf("%5s", "DC3");
			break;
		case 20:
			printf("%5s", "DC4");
			break;
		case 21:
			printf("%5s", "NAK");
			break;
		case 22:
			printf("%5s", "SYN");
			break;
		case 23:
			printf("%5s", "ETB");
			break;
		case 24:
			printf("%5s", "CAN");
			break;
		case 25:
			printf("%5s", "EM");
			break;
		case 26:
			printf("%5s", "SUB");
			break;
		case 27:
			printf("%5s", "ESC");
			break;
		case 28:
			printf("%5s", "FS");
			break;
		case 29:
			printf("%5s", "GS");
			break;
		case 30:
			printf("%5s", "RS");
			break;
		case 31:
			printf("%5s", "US");
			break;
		case 32:
			printf("%5s", "SP");
			break;
        default:
            printf("%5s", "???");
    }
}

void printhr(int prefix, int n, int width) {
    int j, k;
    for (j = 0; j < prefix; j++) {
        printf("=");
    }
    for (j = 0; j < n; j++) {
        printf("+");
        for (k = 0; k < width; k++) {
            printf("=");
        }
    }
    printf("\n");
}




int main(int argc, const char * argv[])
{
    int size;
    printf("Enter a number of bytes plz: ");
    scanf("%d", &size);
    
    unsigned char *p = (unsigned char *)malloc(size);
    if (!p) {
        printf("shit the bed");
        exit(1);
    }
    
    int i;
    printf("Ok, please enter DECIMAL value for each byte: \n");
    for (i = 0; i < size; i++) {
        scanf("%hhu", p+i);
        //printf("Printing: %hhu, %hhd, %c\n", *(p+i), *(p+i), *(p+i));
    }
    

    
    


    
    /* CHAR */
    char *charp = p;
    printhr(25, size / sizeof(char), 5);
    printf("%24s ", "char as unsigned hex");
    
    for (i = 0; i < size / sizeof(char); i++) {
        printf("| 0x%02hhx", charp[i]);
    }

    printf("\n%24s ", "unsigned dec");
    for (i = 0; i < size / sizeof(char); i++) {
        printf("|%5hhu", charp[i]);
    }

    printf("\n%24s ", "signed dec");
    for (i = 0; i < size / sizeof(char); i++) {
        printf("|%5hhd", charp[i]);
    }

    printf("\n%24s ", "character");
    for (i = 0; i < size / sizeof(char); i++) {
        printf("|");
        printchar(charp[i]);
    }
    printf("\n");
    
    
    
    /* SHORT */
    short *shortp = p;
    printhr(25, size / sizeof(short), 11);
    
    printf("%24s ", "short as unsigned hex");
    for (i = 0; i < size / sizeof(short); i++) {
        printf("|     0x%04hx", shortp[i]);
    }
    
    printf("\n%24s ", "unsigned dec");
    for (i = 0; i < size / sizeof(short); i++) {
        printf("|%11hu", shortp[i]);
    }
    
    printf("\n%24s ", "signed dec");
    for (i = 0; i < size / sizeof(short); i++) {
        printf("|%11hd", shortp[i]);
    }
    printf("\n");
    
    
    
    /* INT */
    int *intp = p;
    float *floatp = p;
    printhr(25, size / sizeof(int), 23);
    
    printf("%24s ", "int as unsigned hex");
    for (i = 0; i < size / sizeof(int); i++) {
        printf("|             0x%08x", intp[i]);
    }
    
    printf("\n%24s ", "unsigned dec");
    for (i = 0; i < size / sizeof(int); i++) {
        printf("|%23u", intp[i]);
    }
    
    printf("\n%24s ", "signed dec");
    for (i = 0; i < size / sizeof(int); i++) {
        printf("|%23d", intp[i]);
    }

    printf("\n%24s ", "float");
    for (i = 0; i < size / sizeof(float); i++) {
        printf("|%23f", floatp[i]);
    }
    printf("\n");
    
    
    
    
    
    /* LONG */
    long *longp = p;
    double *doublep = p;
    printhr(25, size / sizeof(long), 47);
    
    printf("%24s ", "long as unsigned hex");
    for (i = 0; i < size / sizeof(long); i++) {
        printf("|                             0x%016lx", longp[i]);
    }
    
    printf("\n%24s ", "unsigned dec");
    for (i = 0; i < size / sizeof(long); i++) {
        printf("|%47lu", longp[i]);
    }
    
    printf("\n%24s ", "signed dec");
    for (i = 0; i < size / sizeof(long); i++) {
        printf("|%47ld", longp[i]);
    }
    
    printf("\n%24s ", "double");
    for (i = 0; i < size / sizeof(double); i++) {
        printf("|%47lf", doublep[i]);
    }
    printf("\n");
    
    printhr(25, size / sizeof(long), 47);
    
    
    
    free(p);
    
    
//    double pi = 3.141592653589793;
//    printf("%72s%lx\n", " ", *((long *)&pi));
//    p = (unsigned char *)&pi;
//    printf("%72s", " ");
//    for (i = 0; i < sizeof(double); i++) {
//        printf("%5hhu ", *p++);
//    }
//    printf("\n");
    
    
}

