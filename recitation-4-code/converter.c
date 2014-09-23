#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define PREFIX 21

void printchar(unsigned char c) {
    if (isgraph(c)) {
        printf("%4c", c);
        return;
    }
    switch (c) {
		case 0:
			printf("%4s", "NUL");
			break;
		case 1:
			printf("%4s", "SOH");
			break;
		case 2:
			printf("%4s", "STX");
			break;
		case 3:
			printf("%4s", "ETX");
			break;
		case 4:
			printf("%4s", "EOT");
			break;
		case 5:
			printf("%4s", "ENQ");
			break;
		case 6:
			printf("%4s", "ACK");
			break;
		case 7:
			printf("%4s", "BEL");
			break;
		case 8:
			printf("%4s", "BS");
			break;
		case 9:
			printf("%4s", "HT");
			break;
		case 10:
			printf("%4s", "LF");
			break;
		case 11:
			printf("%4s", "VT");
			break;
		case 12:
			printf("%4s", "FF");
			break;
		case 13:
			printf("%4s", "CR");
			break;
		case 14:
			printf("%4s", "SO");
			break;
		case 15:
			printf("%4s", "SI");
			break;
		case 16:
			printf("%4s", "DLE");
			break;
		case 17:
			printf("%4s", "DC1");
			break;
		case 18:
			printf("%4s", "DC2");
			break;
		case 19:
			printf("%4s", "DC3");
			break;
		case 20:
			printf("%4s", "DC4");
			break;
		case 21:
			printf("%4s", "NAK");
			break;
		case 22:
			printf("%4s", "SYN");
			break;
		case 23:
			printf("%4s", "ETB");
			break;
		case 24:
			printf("%4s", "CAN");
			break;
		case 25:
			printf("%4s", "EM");
			break;
		case 26:
			printf("%4s", "SUB");
			break;
		case 27:
			printf("%4s", "ESC");
			break;
		case 28:
			printf("%4s", "FS");
			break;
		case 29:
			printf("%4s", "GS");
			break;
		case 30:
			printf("%4s", "RS");
			break;
		case 31:
			printf("%4s", "US");
			break;
		case 32:
			printf("%4s", "SP");
			break;
        default:
            printf("%4s", "???");
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
    printf("Ok, please enter UNSIGNED DECIMAL value for each byte: \n");
    for (i = 0; i < size; i++) {
        scanf("%hhu", p+i);
        //printf("Printing: %hhu, %hhd, %c\n", *(p+i), *(p+i), *(p+i));
    }
    

    
    


    
    /* CHAR */
    char *charp = p;
    int width = 4;
    printhr(PREFIX, size / sizeof(char), 4);
    printf("%21s", "char as unsigned hex");
    
    for (i = 0; i < size / sizeof(char); i++) {
        printf("|0x%02hhx", charp[i]);
    }

    printf("\n%21s", "unsigned dec");
    for (i = 0; i < size / sizeof(char); i++) {
        printf("|%4hhu", charp[i]);
    }

    printf("\n%21s", "signed dec");
    for (i = 0; i < size / sizeof(char); i++) {
        printf("|%4hhd", charp[i]);
    }

    printf("\n%21s", "character");
    for (i = 0; i < size / sizeof(char); i++) {
        printf("|");
        printchar(charp[i]);
    }
    printf("\n");
    
    
    /* SHORT */
    short *shortp = p;
    printhr(PREFIX, size / sizeof(short), 9);
    
    printf("%21s", "short as unsigned hex");
    for (i = 0; i < size / sizeof(short); i++) {
        printf("|   0x%04hx", shortp[i]);
    }
    
    printf("\n%21s", "unsigned dec");
    for (i = 0; i < size / sizeof(short); i++) {
        printf("|%9hu", shortp[i]);
    }
    
    printf("\n%21s", "signed dec");
    for (i = 0; i < size / sizeof(short); i++) {
        printf("|%9hd", shortp[i]);
    }
    printf("\n");
    
    
    
    /* INT */
    int *intp = p;
    float *floatp = p;
    printhr(PREFIX, size / sizeof(int), 19);
    
    printf("%21s", "int as unsigned hex");
    for (i = 0; i < size / sizeof(int); i++) {
        printf("|         0x%08x", intp[i]);
    }
    
    printf("\n%21s", "unsigned dec");
    for (i = 0; i < size / sizeof(int); i++) {
        printf("|%19u", intp[i]);
    }
    
    printf("\n%21s", "signed dec");
    for (i = 0; i < size / sizeof(int); i++) {
        printf("|%19d", intp[i]);
    }

    printf("\n%21s", "float");
    for (i = 0; i < size / sizeof(float); i++) {
        printf("|%19.4f", floatp[i]);
    }
    printf("\n");
    
    
    
    
    
    /* LONG */
    long *longp = p;
    double *doublep = p;
    printhr(PREFIX, size / sizeof(long), 39);
    
    printf("%21s", "long as unsigned hex");
    for (i = 0; i < size / sizeof(long); i++) {
        printf("|                     0x%016lx", longp[i]);
    }
    
    printf("\n%21s", "unsigned dec");
    for (i = 0; i < size / sizeof(long); i++) {
        printf("|%39lu", longp[i]);
    }
    
    printf("\n%21s", "signed dec");
    for (i = 0; i < size / sizeof(long); i++) {
        printf("|%39ld", longp[i]);
    }
    
    printf("\n%21s", "double");
    for (i = 0; i < size / sizeof(double); i++) {
        printf("|%39lf", doublep[i]);
    }
    printf("\n");
    
    printhr(PREFIX, size / sizeof(long), 39);
    
    
    
    free(p);
    
    
//    double pi = 3.141592653589793;
//    printf("%72s%lx\n", " ", *((long *)&pi));
//    p = (unsigned char *)&pi;
//    printf("%72s", " ");
//    for (i = 0; i < sizeof(double); i++) {
//        printf("%5hhu ", *p++);
//    }
//    printf("\n");

   return 0; 
}

