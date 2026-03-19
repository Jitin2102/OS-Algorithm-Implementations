#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    const int SIZE = 4096;
    const char *name = "OS";
    int fd;
    char *ptr;

    // Open the existing shared memory object (O_RDONLY)
    fd = shm_open(name, O_RDONLY, 0666);
    if (fd == -1) {
        perror("shm_open failed");
        return 1;
    }

    // Map the memory object into the consumer's address space
    ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    // Read and print the messages
    printf("Message read from shared memory: %s\n", ptr);

    // Remove the shared memory object from the system
    shm_unlink(name);

    return 0;
}
