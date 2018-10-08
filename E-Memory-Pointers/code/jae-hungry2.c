#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int* seamless(int *balance, int orderNum) {
	
	int price;
    int serviceFee = 15;
      
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
    
    serviceFee = 52;
    *balance -= price+serviceFee;     
   
    int* receipt= malloc(sizeof(int)*2);
    receipt[0] = price;
    receipt[1] = serviceFee;
    return receipt;
}

int main(int argc, char **argv) {
    
    if(argc < 2){
        perror("You have no money Jae!");
        exit(1);
    }
    
    int jaeNetWorth = atoi(argv[1]);	// salad with bacon
    int jaeOrder = 77;
    
    printf("Jae is worth $%d\n", jaeNetWorth);
	
    int *receipt= seamless(&jaeNetWorth, jaeOrder);
    printf("Jae is now worth $%d\n", jaeNetWorth);
    free(receipt);
}

