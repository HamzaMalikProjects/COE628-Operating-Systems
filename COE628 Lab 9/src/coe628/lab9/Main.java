/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package coe628.lab9;

/**
 *
 * @author hemalik
 */

/**
 * The Main class for the Dining Philosophers problem. This class initializes the philosophers and forks,
 * and sets up the scenario where each philosopher alternates between thinking and eating.
 */

public class Main {
    // The number of philosophers (and forks) participating in the problem.
    static final int NUM_PHILOSOPHERS = 5;
    // Array to hold the philosopher objects.
    static DiningPhilosophers[] philosophers = new DiningPhilosophers[NUM_PHILOSOPHERS];
    // Array to hold the forks. Each fork can be used by two neighboring philosophers.
    static Fork[] forks = new Fork[NUM_PHILOSOPHERS];
    
    public static void main(String[] args) {
        // Initialize forks with unique IDs for identification and debugging.
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            forks[i] = new Fork(i);
        }
        
        // Initialize philosophers, assigning them their respective left and right forks.
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            Fork leftFork = forks[i]; // Each philosopher's left fork is straightforwardly assigned.
            // Right fork is assigned using modulo operation to wrap around the array for the last philosopher.
            Fork rightFork = forks[(i + 1) % NUM_PHILOSOPHERS];

            // To prevent deadlock, we alter the fork picking order for the last philosopher.
            // This breaks the circular wait condition necessary for a deadlock to occur.
            if (i == NUM_PHILOSOPHERS - 1) {
                // The last philosopher picks up the right fork first, then the left fork.
                philosophers[i] = new DiningPhilosophers(i, rightFork, leftFork);
            } else {
                // All other philosophers pick up the left fork first, then the right fork.
                philosophers[i] = new DiningPhilosophers(i, leftFork, rightFork);
            }

            // Starting the philosopher's thread. Each philosopher begins their routine of thinking and eating.
            Thread philosopherThread = new Thread(philosophers[i], "Philosopher " + i);
            philosopherThread.start();
        }
    }
}
