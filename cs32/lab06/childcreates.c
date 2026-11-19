#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


//child is a zero value
//so we're inside child if fork == 0
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: forkloop <iterations>\n");
        exit(1);
    }

    int iterations = strtol(argv[1], NULL, 10);

    for (int i = 0; i < iterations; i++) {
        int n = fork();
        if (n < 0) {
            perror("fork");
            exit(1);
        }
        printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);
        //but we have to stop being in the parent 
        if (n > 0 ){
            //move onto child
            break; 
        }

        //we want to be in child
        if (n == 0){
            continue;
        }
    }
    wait(NULL);

    return 0;
}
