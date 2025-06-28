/* COE 628 - Operating Systems
 * Lab 6 Exercise
 * Author: hemalik
 *
 * This program creates multiple producer threads that each add to a shared total sum
 * and a single consumer thread that displays the total sum after all producers are done.
 *
 * To compile use:
 * gcc -pthread -o main main.c
 * main
 * 
 */

#include <stdio.h>      
#include <stdlib.h>     
#include <sys/types.h>  
#include <unistd.h>     
#include <sys/wait.h>   
#include <pthread.h>    

// Define the number of producer threads.
#define PRODUCERS_COUNT 5  

// Define the number of items each producer will produce.
#define ITEMS_TO_PRODUCE 20 

// Function prototypes for producer and consumer threads.
void *produce(void *);

void *display_totals(void *);

// Global variables for the total sum and the count of producers that have finished their job.
long total_sum; 

long producers_done; 

// Mutex locks for protecting shared resources and for condition variable.
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t cond_lock = PTHREAD_MUTEX_INITIALIZER;

// Condition variable to signal the consumer when all producers are done.
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int main(void) {
    int i;
   
    // Initialize random number generator.
    srand(time(NULL)); 
    
    // Initialize total sum to 0.
    total_sum = 0;
    
    // Initialize the count of finished producers to 0.
    producers_done = 0; 

    // Array to hold producer thread identifiers.
    pthread_t producers[PRODUCERS_COUNT];
    
    for (i = 0; i < PRODUCERS_COUNT; i++) {
       
       // Create producer threads.
        pthread_create(&producers[i], NULL, produce, NULL);
    }

    // Thread identifier for the consumer thread.
   
   pthread_t display_thread;
   
   // Create the consumer thread.
    pthread_create(&display_thread, NULL, display_totals, NULL);

    // Wait for all producer threads to finish.
    for (i = 0; i < PRODUCERS_COUNT; i++) {
        pthread_join(producers[i], NULL);
    }

    // Wait for the consumer thread to finish.
    pthread_join(display_thread, NULL);

    return 0;
}

void *produce(void* junk) {
    // Lock the mutex before accessing the shared resource.
    pthread_mutex_lock(&lock); 

    long count = 0;
    long local_sum = 0;

    while (count < ITEMS_TO_PRODUCE) {
      
      // Simulate producing an item and add it to the total sum.
        long tmp_sum = total_sum;
        long number = 1; // Each item contributes 1 to the sum.
        printf("Sum Adding %ld\n", tmp_sum, number);
        total_sum = tmp_sum + number;
        count++;
        local_sum += number;
        usleep(1000); // Simulate work by sleeping for a short time.
    }
    printf("\n");
    printf("Final Local Sum %ld\n", local_sum);
   
   // Increment the count of producers that are done.
    producers_done++;
   
   // Unlock the mutex after updating the shared resource.
    pthread_mutex_unlock(&lock); 

    // Lock the conditional mutex to check/update the condition.
    pthread_mutex_lock(&cond_lock);
    if (producers_done == PRODUCERS_COUNT) {
        // If all producers are done, signal the consumer thread.
        pthread_cond_signal(&condition);
    }
    pthread_mutex_unlock(&cond_lock);

    return NULL;
}

void *display_totals(void* junk) {
    
    // Lock the conditional mutex to wait for the condition.
    pthread_mutex_lock(&cond_lock);
    while (producers_done < PRODUCERS_COUNT) {
     
     // Wait for the signal that all producers are done.
        pthread_cond_wait(&condition, &cond_lock);
    }
   
   // Unlock the mutex once the condition is met.
    pthread_mutex_unlock(&cond_lock);

    // Display the final total sum.
    printf("Final Total %ld\n", total_sum);
}
