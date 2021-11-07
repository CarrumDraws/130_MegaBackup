
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

void* myturn(void* arg) { // 2. A Void Pointer can point to anything => we can pass and return ANY data type!
    int *intptr = (int*) arg; // HOW DOES THIS WORK WITH MUTIPLE INPUTS
    for(int i = 0; i < 6; i++) {
        sleep(1);
        printf("My Turn! %d\n", *intptr);
        *intptr = *intptr + 1;
    }
    return intptr;
}
void yourturn() {
    for(int i = 0; i < 3; i++) { 
        sleep(1);
        printf("Your Turn!\n");
    }
}


pthread_mutex_t mutex; // Declare MUTEX (outside main)
int mails = 0;
void* routine_1(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex); // Lock MUTEX
        mails++;
        pthread_mutex_unlock(&mutex); // Unlock MUTEX
    }
    return (int*) 5;
}

pthread_mutex_t mutexFuel; 
pthread_cond_t condFuel; // Declare COND
int fuel = 0;
void* car(void* arg) {
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40) {
        printf("Insufficient Fuel.\n");
        pthread_cond_wait(&condFuel, &mutexFuel); // If condition doesn't hold, COND_WAIT. Unlock mutex...
    }
    fuel -= 40;
    printf("Got Fuel. Fuel Left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
    return (int*) 5;
}
void* fuel_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutexFuel); // v CRIT SEC v
        fuel += 15;
        printf("Added Fuel. Current Fuel: %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel); // ^ CRIT SEC ^
        pthread_cond_signal(&condFuel); // Send a COND_SIGNAL when applicable, unless
        sleep(1);
    }
    return (int*) 5;
}

// NOTE: include <semaphore.h>
sem_t semaphore; // Declare SEMAPHORE
void* routine_2(void* args) {
    sem_wait(&semaphore); // v CRIT SEC v
    sleep(1);
    printf("Hello from thread %d\n", *(int*)args); // Take in args > cast as int pointer > dereference
    sem_post(&semaphore); // ^ CRIT SEC ^
    return (int*) 5;
}

int main() {
    // pthread_t newthread; // instantiate THREAD (inside main...?)
    // int v = 0;
    // int *result;
    // pthread_create(&newthread, NULL, &myturn, &v); // create THREAD tied to MYTURN function- starts it!
    // yourturn();
    // pthread_join(newthread, (void *)&result); // Waits until newthread is done, also recieves input
    // printf("Thread's Done! Result is %d\n", *result);

    // pthread_t raceConOne, raceConTwo;
    // pthread_mutex_init(&mutex, NULL); // Initialize Mutex
    // pthread_create(&raceConOne, NULL, &routine_1, NULL);
    // pthread_create(&raceConTwo, NULL, &routine_1, NULL);
    // pthread_join(raceConOne, NULL);
    // pthread_join(raceConTwo, NULL);
    // pthread_mutex_destroy(&mutex); // Destroy Mutex
    // printf("Goal: 200000, Actual: %d\n", mails);

    // pthread_t fuelThread, carThread;
    // pthread_mutex_init(&mutexFuel, NULL);
    // pthread_cond_init(&condFuel, NULL); // COND: Lets you move mutex locks around.
    // pthread_create(&fuelThread, NULL, &fuel_filling, NULL);
    // pthread_create(&carThread, NULL, &car, NULL);
    // pthread_join(fuelThread, NULL);
    // pthread_join(carThread, NULL);
    // pthread_mutex_destroy(&mutexFuel); 
    // pthread_cond_destroy(&condFuel); // Destroy COND

    int THREAD_NUM = 4;
    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 2); // Initialize SEMAPHORE
    for (int i = 0; i < THREAD_NUM; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine_2, a) != 0) {
            printf("Failed to Create");
        }
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Failed to Join");
        }
    }
    sem_destroy(&semaphore);
    return 0;
}
