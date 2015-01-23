#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* for for and exec */
#include <sys/wait.h> /* for wait and waitpid */
#include <errno.h> /* for errno, which waitpid uses */

int main(int argc, char **argv) {
    char input[1024]; /* buffer to store the command the user enters */

    printf("we await your command:  ");
    /* Enter a loop where we take a command from the user, then fork and exec it */
    while (fgets(input, sizeof(input), stdin)) {
        /* We have a command stored in input, now we want to prepare
           what will become the child's argv. It's going to have the same
           format as a normal argv */
        
        char *childargv[128];

        /* we'll use strtok to separate it. Man strtok to see what it's doing,
           but basically you call it once with a string to tokenize, and a bunch
           of chars to use as separators. Then in subsequent calls leave the
           string NULL and it will continue. See man strtok */

        childargv[0] = strtok(input, " \n"); /* get first */

        /* tokenize the remaining arguments, if any, using this tight loop */
        char **cap = childargv+1;
        while ((*cap++ = strtok(NULL, " \n")))
            ;

        /* Let's have one of our own commands here */
        if (strcmp(childargv[0], "exit") == 0) {
            return 0;
        }

        /* now time to fork. fork is called once, returns twice */
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "jsh failed to fork. errno = %d\n", errno);
            return 1;
        } else if (pid == 0) {
            /* Child, so we become the command */
            execvp(childargv[0], childargv);
            return 1;
        } else if (pid > 0) {
            /* parent */
            int v; /* used to determine if waitpid errored */
            int retcode; /* used to hold the returned status of the child process,
                            after the child terminates */
            /* waitpid will not return until the child process terminates, so 
               it may be a long time */
            if ((v = waitpid(pid, &retcode, 0)) != pid) {
                fprintf(stderr, "waitpid failed, got %d instead of %d with errno %d\n", v, pid, errno);
                return 1;
            }

            /* Just for user information, if the child didn't return 0 there
               may have been an error, so let's tell the user */
            if (retcode != 0) {
                fprintf(stderr, "child returned %d\n", retcode);
            }
        }

        /* ok, ready to go around again! */
        printf("we await your command:  ");
    }

    return 0;
}
