#1

```c
int x = 1, y = 2;
int *p;
p = &x;
int *n = &y;
n = p;
*p = 0;

```
what is x?
what is y?

```c
*p++
```

what is x?
what is y?

```c
++*p;
(*)p++;
```
what is x?
what is y?


Do you feel anything wrong about this code? If you do, what line/s?
```c
int i = 1234;
double d = 3.14;

int *pi = &i;
double *pd = &d;
int *pi2 = &i;

pi = pd; 
pi = pi + pi2; 
pi = pi + 2.0; 
pi >> 2 

if (pi+1 > pd) {  // generates warning, but it compiles
	printf("pi+1 > pd);
}

char *s = "hello";
if (s == "hello") { //generates warning, but it compiles
	printf("s == "hello");
}

pi = (int *) pd; //this is allowed.

void *pv;
pv = pd; 
```
```c
pi = pd; // you cannot assign a pointer to another of a different type
pi = pi + pi2; // you cannot add pointers together 
pi = pi + 2.0; // you cannot add floats or doubles. only integers.
pi >> 2 // you cannot bitshift the pointers

pi = (int *) pd; //this is allowed.
```
what statements will get printed?
```c
char c = 0;
char *p = &c;
char *q = NULL;

if (p) {
	printf("printed");
}

if (*p) {
	printf("printed 1"); 
}

if (q) {
	printf("printed1"); 
}

if (*q) {
	
}
```
Ans: prints, doesn't print, doesnt, crash

what is the value of x and y?
```c
int x = 1;
int y = 2;

swap (int x, int y);
swap (x, y);
```



#2

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
	int x = 5;
	int *p = &x;
	int y = 7;
	int *d = &y;
	double value = 2.0;
	double value2 = 3.0;
	double *k2 = &value2;
	double *k = &value;
	char *s = "hello";
	char *ed = malloc(sizeof(100));

	printf("k is          %p\n", k);
	printf("k2 is         %p\n", k2);
	printf("malloced d is %p\n", ed);
	printf("s is          %p\n", s);

	if (s == "hello") {
		printf("its the same\n");
	}
	if (p+1 > (int *) k) {
		printf("inside the if statement");
	}
	

}
```
* NOTE: "its the same" prints because of the compiler optimization of preventing duplicate copy creation of "hello"

* please write in order of what variables have higher values. k, k2, ed and s

#3 (arrays)

What part would cause the error?
```c
int a[10];
a[0] = 100;
a[10] = 300; 
```
a[10] = 300 //out of bounds. compiles, but it causes abort trap; runtime error


* Which initialization of array is wrong?
```c
int a[] = {100, 200, 300};
int b[10] = {-1};
char c[] = "abc";
char d[3] = "abc";

char *c = malloc(1);
c[0] = 'z';
c = "hello";
c[0] = '1'; 
```
* c[0] = 'z'; -> //works
* c = "hello" -> works
* c[0] = '1'; -> does not work

What would these print statements print?
```c
int x;
int a[10];
printf("%d\n", sizeof(x));
printf("%d\n", sizeof(100));
printf("%d\n", sizeof(a[10])); //40
printf("%d\n", sizeof(a)); //8
```

What would the print statements print out?

```c
int a[] = {1, 2, 3, 4, 5];
int *p = a;
printf("%d\n", *p);
p += 1;
printf("%d\n", *p);
int x = p[2];
printf(%d\n", *p); // note that it still points to 2, but x is 4.
char *pc = "hello";
int x = 2;
printf("%c\n", *(pc+x)); 
printf("%d\n", (pc + y - (p + y))); 
printf("%c\n", (pc+1)[2]); 
```

* printf("%c\n", *(pc+x)); //l will be printed.
* printf("%d\n", (pc + y - (p + y))); //error char * and int * arenot pointers to compatible types
* printf("%c\n", (pc+1)[2]); //prints out l
Q. What would these print out?

```c
int a[] = {100, 200, 300, 400, 500, 600};
int *p;
p = a;

  printf("%d\n", (&a[0])[0]);
  printf("%d\n", (&*(a + 0))[0]);
  printf("%d\n", (a + 0)[0]);
  printf("%d\n", (0 + a)[0]);
  printf("%d\n", 0[a]);
  printf("%d\n", *(0 + a));
  printf("%d\n", &a[0] + 0);
  printf("%d\n", *(&a[0] + 0)); 
  printf("%d\n", *(&a[3] - 2));
  printf("%d\n", *(&a[3]));
  printf("%d\n", (&a[0]));
  printf("%d\n", a + 5);
  printf("%d\n", *(a + 5));
  printf("%d\n", &a[5]);
  printf("%d\n", &a[0] + 5);
  //&*(a+0)[0]
```
A. Result:
* 100
* 100
* 100
* 100
* 100
* 100
* 1581701216
* 100
* 200
* 400
* 1581701216
* 1581701236
* 600
* 1581701236
* 1581701236

Q. When do we use malloc()?
A. 1. When we want the size of the array to be dynamic
   2 .When we want a permanent array that is not transient. 

Are these for loops equivalent? If not, why not?
```c
int a[10] = {0};
int i;
int *p = a;

// loop 1
for (i = 0; i<10; i++) {
	printf("%d", a[i];
}

// loop 2
for (i = 0; i<10; i++) {
	printf("%d", *p++);
}

// loop 3
--p;
for (i = 0; i<10; i++) {
	printf("%d", *++p);
}
```

Q. Where are string literals saved?
A. Either code section or static data section.


Q. What would these print statements print if I run ./a.out hello world

```c
int main(int argc, char **argv) {
	for (i = 1; i < argc; i++)
		printf("%s\n", argv[i]);
}
```
hello
world

```c
int main(int argc, char **argv) {
	while (--argc > 0)
		printf("%s\n", *++argv);
	printf("%d\n", argc");
}
```
hello
world
0
```c
int main(int argc, char **argv) {
	while (argc-- > 0)
		printf("%s\n", *++argv);
		printf("%d\n", argc);
}
```
hello
world
(null)
-1
NOTE THAT argc-- means argc gets decremented in the next line (confirmed with code).
```c
int main(int argc, char **argv) {
	argv++;
	while (argc-- > 0)
		printf("%s\n", *argv++);
		printf("%d\n", argc);
}
```
The last one is hello word and null. 

#4 Variable Scopes
Q. What would the print statement print?
```c
int x;
main() {
	printf("value of x is %d\n", x);
}
```
A. It should print 0, because for global variables which get the default value of 9.

#5 Function pointers

Q. What is wrong with the following code?
```c
void qsort(void *baseAddress, size_t numElem, size_t sizeElem, int (*compareFn)(const void *, const void*));

int compareFloat(const void *v1, const void *v2) {
	float x = *(float *)v1;
	float y = *(float *)v2;
	if (x < y)
		return -1;
	else if (x>y)
		return 1;
	else 
		return 0;
}

int compareString(const void *v1, const void *v2) {
	return strcmp((char *)v2, (char *) v2);
}

int main(int argc, char **argv) {
	qsort(array_of_100_floats, 100, sizeof(float), &compareFloat);
	qsort(argv, argc, sizeof(char *), &compareString));
}
```
Explanation 1.
* compareFloat: 1. cast the pointer to the right type of float *, which is the type of baseAddress. 
		2. then dereference the casted pointer to get float. 
* compareString: 1. I need to cast the pointer to the type of baseAddress, which is char **. But in this case, it is casted to the pointer of char *.
		2. I need to dereference the pointer and get the type of string, but in this case, dereferencing is not done. 
		- These two points are the ones that need to be changed. 
Explanation 2.
* Notice that what we do in the second qsort is string comparison. 
* When it comes to qsort of int, we are sending int *, int, sizeof(int), int comparison function that opens int *.
* When it comes to qsort of string, we are sending char **, int, sizeof(char *), char * comparison function that opens char **. But see that strcmp accepts casts v1 to char * rather than char **, when char ** pointer comes into the function.

#6 Complicated Declarations

Q. Describe what these declarations are
* int (*ptr)[13] 
* int *daytab[13] 

A. 
* ptr is a pointer to int array of size 13.
* daytab is a (int *) typed array of size 13.

#7 String Concatenation
* What is the difference between these implementations? 

```c
#include <stdio.h>
#include <stdlib.h>

void mgetline(char **s, int lim);
void mystrcat(char *s, char *t);

int main() {
	char *s, t;
	putchar('s');
	putchar(':');
	mgetline(&s, 100);

	putchar('t');
	putchar(':');
}

void mgetline(char **s, int lim) {
	s = (char *) malloc(lim*4);
	char c;
	int i = 0;
	while ((c = getchar() && (c != EOF) && (c != '\n')) {
		*(*s+i) = c;
		i++;
	}
	printf("mget s is %s\n", *s);
	
	if (c == '\n') {
		*(*s+i) = '\n';
		i++;
	}
	*(*s+i) = '\0';
}

void mystrcat(char *s, char *t) {
	printf("s is %s\n", s);

	while (*s != '\0') {
		printf(" individual char is %c\n", *s);
		s++;
	}
	s--;

	while(*t != '\0' && *s != '\0') {
		*s = *t;
		s++;
		t++;
	}
}
```
```c
char *mgetline(char *s, int lim) {
	s = (char *) malloc(lim*4);
	char c;
	int i = 0;
	while ((c = getchar() && (c != EOF) && (c != '\n')) {
		*(*s+i) = c;
		i++;
	}
	printf("mget s is %s\n", *s);
	
	if (c == '\n') {
		*(*s+i) = '\n';
		i++;
	}
	*(*s+i) = '\0';
	return s;
}
```
Note that this implementation has mgetline which does not return anything. In that case, we are sending the pointer to whatever we want to be copied. In this case, we are sending the address of s, which makes it a pointer to s. If you do that, it will make a copy of the &s, which is another pointer to s. Then nothing can be returned from this function and the work is still done. 
