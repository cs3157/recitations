#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

static void die(const char *s)
{
    perror(s);
    exit(1); 
}

int main()
{
    char	buf[100];
    pid_t	pid;
    int		status;

    printf("AP> ");

    while (fgets(buf, sizeof(buf), stdin) != NULL) {

        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0; // replace newline with '\0'

        pid = fork();
        if (pid < 0) {
            die("fork error");
        } else if (pid == 0) {  
            // child process
            execl(buf, buf, (char *)0);
            die("execl failed");
        } else {
            // parent process
            if (waitpid(pid, &status, 0) != pid)
                die("waitpid failed");
        }

        printf("AP> ");
    }

    return 0;
}
