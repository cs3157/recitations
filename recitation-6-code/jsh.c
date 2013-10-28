#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* for for and exec */
#include <sys/wait.h> /* for wait and waitpid */
#include <errno.h> /* for errno, which waitpid uses */

int main(int argc, char **argv) {
    char input[1024];

    printf("what? ");
    while (fgets(input, sizeof(input), stdin)) {
        char *parameters[128];
        parameters[0] = strtok(input, " \n");

        /* tokenize the parameters into an array */
        char **param = parameters+1;
        while ((*param++ = strtok(NULL, " \n")))
            ;

        pid_t pid;
        /* now time to fork */
        if ((pid = fork()) < 0) {
            fprintf(stderr, "jsh failed to fork. errno = %d\n", errno);
            return 1;
        } else if (pid == 0) {
            /* Child, so we become the command */
            execvp(parameters[0], parameters);
            return 1;
        } else if (pid > 0) {
            /* parent */
            int v;
            int retcode;
            if ((v = waitpid(pid, &retcode, 0)) != pid) {
                fprintf(stderr, "waitpid failed, got %d instead of %d with errno %d\n", v, pid, errno);
                return 1;
            }

            if (retcode != 0) {
                fprintf(stderr, "child returned %d\n", retcode);
            }
        }

        /* ok, ready to go around again! */
        printf("what? ");
    }

    return 0;
}
