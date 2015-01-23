This example demonstrates the orders in which programs execute after calling
fork() and execl(). 

Output should be:

I started!                      //parent process
I'm the child!                  //first child
I only print once...or do I?    //first or second child
I only print once...or do I?    //first or second child
I'm done! Woohoo!               //parent process

OR

I started!
I'm the child!
I only print once...or do I?    //first child
I'm done! Woohoo!               //parent process
I only print once...or do I?    //second child

directory structure:

fork-exec-ordering-example
|
|--lab1000
|  |
|  |--Makefile
|  |--main.c
|
|--lab1001
|  |
|  |--Makefile
|  |--program2.c
|
|--README.txt
