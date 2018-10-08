#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void seamless(int *balance, int orderNum) {
	
	int price;
    
    int *pricePointer = &price;
	
    if(orderNum == 10) {
		price = 12;
    }
	else if(orderNum == 77) {
		price = 15;
    }
	else {
		price = 0;
    }    
    printf("Price Address: %p; Price Pointer Address: %p\n", &price, &pricePointer);
    *balance -= price;     
        
}

int main(int argc, char** argv) {
    
    if(argc < 2){
        perror("You have no money Jae!");
        exit(1);
    } 
    int jaeNetWorth = atoi(argv[1]);	
    int jaeOrder = 77;      // Salad with Bacon

    printf("Jae is worth $%d\n", jaeNetWorth);
	 
    seamless(&jaeNetWorth, jaeOrder);
    printf("Jae is now worth $%d\n", jaeNetWorth);

}
