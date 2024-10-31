#include <stdio.h>
#include <thread>
#include <semaphore.h>

int main() {
    sem_t semaphore;
    int retval;

    retval = sem_init(&semaphore, 0, 0);
    if (sem_getvalue(&semaphore, &retval) == 0) {
        printf("Semaphore value: %d\n", retval);
    } else {
        printf("Failed to get semaphore value\n");
    }
}