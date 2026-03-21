#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

#define NUM_THREADS 5

void *runner(void *param) {

    int thread_id = (int)(long)param;
    printf("Thread %d is running\n", thread_id);
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int policy;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;
    int thread_ids[NUM_THREADS];

    pthread_attr_init(&attr);

    if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
        fprintf(stderr, "Unable to set policy! (Are you root?)\n");

    }

    if (pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) != 0) {
        fprintf(stderr, "Unable to set inherit sched!\n");
    }

    struct sched_param param;
    param.sched_priority = 10;
    pthread_attr_setschedparam(&attr, &param);

    if(pthread_attr_getschedpolicy(&attr, &policy) == 0) {
        printf("Policy set to: %s\n",
               (policy == SCHED_FIFO) ? "SCHED_FIFO" :
               (policy == SCHED_RR) ? "SCHED_RR" : "SCHED_OTHER");
    }


    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        int rc = pthread_create(&tid[i], &attr, runner, (void *)(long)thread_ids[i]);
        if (rc != 0) {
            fprintf(stderr, "Error creating thread %d: %s\n", i, strerror(rc));
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_attr_destroy(&attr);
    return 0;
}
