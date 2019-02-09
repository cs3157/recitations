//Pointer demo
//Gustaf Ahdritz
//COMS 3157

void foo_1(int x, int *z){
        
        x++;
        
        int a = *z;

        a++;
}

int main(){
        
        int x = 5;
        int y = 7;
        int *z = &y;
        
        printf("The value of z is: %p\n", z);

        foo_1(x, z);

        printf("The value of x is %d\n", x);
        printf("The value at address z is %d\n", *z);

	return 0;
}
