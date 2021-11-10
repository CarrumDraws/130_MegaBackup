
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

struct data {
    int id;
    int* stack; // How can I store an array into the data struct? Or maybe I just need an int pointer, is that the same thing?
    pthread_mutex_t* locks; // Is this already by reference? maybe. idk.
};

void producer(int numThreads, int stack[], pthread_mutex_t locks[]) {
    int connFD = 10;
    int index = 0;
    while (1) {
        //connFD here
        while(1) {
            index = index % numThreads;
            if(stack[index]==0) {
                pthread_mutex_lock(&locks[index]);
                stack[index] = connFD;
                pthread_mutex_unlock(&locks[index]);
                break;
            }
            index++;
        }
        connFD += 10;
    }
}

void* consumer(void* arg) {
    struct data info = *(struct data*)arg;
    int id = info.id;
    int temp;
    int cycle = 1;
    while(1) {
        if(info.stack[id] != 0) {
            pthread_mutex_lock(&info.locks[id]);
            temp = info.stack[id]; // temp stores the connFD that was stored in stack...
            info.stack[id] = 0; // ...then sets stack value to 0
            pthread_mutex_unlock(&info.locks[id]);
            printf("Cycle: %d | Thread: %d | Data: %d\n", cycle, id, temp);
            //handle_connection(temp, log_file, int* logLen, pthread_mutex_t LogLock);
            cycle++;
            sleep(1);
        }
    }
}

int main() {
    // parse data, get numthreads and log_file
    int numThreads = 5;

    pthread_t threads[numThreads];
    int stack[numThreads];
    pthread_mutex_t locks[numThreads];
    
    sleep(1);

    for (int x = 0; x < numThreads; x++) {
        struct data* myData = (struct data*)malloc(sizeof(struct data));

        myData->id = malloc (sizeof(int));
        myData->stack = (int *) malloc (numThreads * sizeof(int));
        myData->locks = (pthread_mutex_t *) malloc (numThreads * sizeof(pthread_mutex_t));

        myData->id = x;
        myData->stack = stack;
        myData->locks = locks;

        for (int i = 0; i < numThreads; i++) { // for loop to initialize array to 0
            myData->stack[i] = 0;
        }

        pthread_mutex_init(&myData->locks[x], NULL);
        pthread_create(&threads[x], NULL, &consumer, myData);
    }

    // JUNK IN STACK
    producer(numThreads, stack, locks);
    return 0;
}

