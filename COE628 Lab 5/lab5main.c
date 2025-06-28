#include  <stdio.h> /* printf */
#include  <sys/types.h> /* pid_t */
#include <unistd.h> /* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h>  /* wait */
#include <pthread.h>
#include <sys/stat.h>

// Hamza Malik
//501112545

void * count(void *); // Function prototype for the thread's routine
int globalNumber = 0;
int num_of_threads = 5;
//Create a mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; // Mutex initialization for thread synchronization

int main(void) {
    int i;
    pthread_t counterThread[5];


    //Create the 5 threads
     for(i = 0; i < num_of_threads; i++){
        pthread_create(&counterThread[i], NULL, count, NULL);
    }
    //Wait for all treads to finish
 for(i = 0; i < num_of_threads; i++){
        pthread_join(counterThread[i], NULL);
    }
    
    printf("Final Counter Value: %d\n", globalNumber);
    return (0);
}
// The function to be executed by each thread
void * count(void * junk) {
    int loopCount = 0;
    pthread_mutex_lock(&mutex1);
    while (loopCount < 10) {
        int tmpNumber = globalNumber;
        printf("counter: %d, Thread: %ld, PID: %d\n",
                tmpNumber, pthread_self(), getpid());
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        loopCount++;
    }
        // Unlocking the mutex to allow other threads to access the global variable
    pthread_mutex_unlock(&mutex1);
    return (0); // Return NULL pointer as required by pthread_create() function signature
}
