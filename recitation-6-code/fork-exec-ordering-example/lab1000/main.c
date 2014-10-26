#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //fork, exec
#include <sys/wait.h> //wait

int main(int argc, char** argv)
{
    printf("I started!\n");
    pid_t pid = fork();
    if (pid < 0){
        fprintf(stderr, "Oops. Fork failed.");
        exit(1);
    } 
    else if (pid == 0) //child process
    {
        printf("I'm the child!\n");
        fork();
        execl("../lab1001/program2", "program2", (char *)0);
        /** DON'T LET THIS TRIP YOU UP. THE NEXT STATEMENT NEVER, EVER PRINTS **/
        printf("execl worked! Yay! \n");
    }
    else { //parent process--just waits until child returns
        if ((waitpid(pid, NULL, 0)) != pid)
            fprintf(stderr, "waitpid failed. :( ");
    }
    printf ("I'm done! Woohoo!\n");
    return 0;
}
