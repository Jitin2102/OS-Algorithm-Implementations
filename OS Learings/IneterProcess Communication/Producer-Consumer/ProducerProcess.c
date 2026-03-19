#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    const int size = 4096;
    const char *name = "OS";

    const char *message_0 = "Hello";
    const char *message_1 = "World!";


    int fd;
    char *ptr;

    // shared memory object
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    // Configure size
    ftruncate(fd, size);

    ptr = (char *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Write to shared memory
    sprintf(ptr, "%s", message_0);
    ptr += strlen(message_0);
    sprintf(ptr, "%s", message_1);
    ptr += strlen(message_1);
    printf("Done\n");
    return 0;
}
