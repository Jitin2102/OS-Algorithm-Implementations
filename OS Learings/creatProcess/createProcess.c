#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Run mspaint.exe from its Windows location
        execlp("/mnt/c/Windows/System32/mspaint.exe", "mspaint.exe", NULL);

        perror("Failed to start mspaint");
        exit(1);
    } else {
        printf("Parent waiting for Paint to close...\n");
        wait(NULL);
        printf("Paint closed. Child complete.\n");
    }
    return 0;
}
