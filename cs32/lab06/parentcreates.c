#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>



//for this one only the parent creates 2 forks so 
//parent is non zero value
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: forkloop <iterations>\n");
        exit(1);
    }

    int iterations = strtol(argv[1], NULL, 10);

    for (int i = 0; i < iterations; i++) {
        //keeps forking
        int n = fork();
        if (n < 0) {
            perror("fork");
            exit(1);
        } 
        
        printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);
        
        //child dont run so just exit 
        if (n == 0){
            exit(0);
        }
       
    }

    //has iterations children so need to go through & waits for them
    for (int i = 0; i < iterations; i++){
        wait(NULL);
    }

    return 0;
}
