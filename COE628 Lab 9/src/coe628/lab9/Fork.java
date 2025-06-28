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

import java.util.logging.Level;
import java.util.logging.Logger;

// The Fork class represents each fork in the dining philosophers problem.
// It utilizes a semaphore to manage access, ensuring mutual exclusion.
public class Fork {
    Semaphore semaphore = new Semaphore(1); // Semaphore initialized with a single permit, representing the fork's availability.
    int id; // Unique identifier for the fork.
    
    /**
     * Initializes a new Fork instance with a specified identifier.
     * The identifier is used to distinguish between different forks.
     *
     * @param id The unique identifier for this fork.
     */
    public Fork(int id) {
        this.id = id; // Assign the unique identifier to this fork.
    }
    
    /**
     * Retrieves the fork's identifier in a user-friendly format.
     * The identifier is incremented by 1 to make it 1-indexed, which is more intuitive for display.
     *
     * @return The adjusted identifier of the fork for display purposes.
     */
    int getId() {
        return (id + 1); // Return the fork's identifier as 1-indexed for ease of understanding.
    }
    
    /**
     * Tries to acquire the fork for a philosopher. If the fork is already in use (semaphore is at 0),
     * this method will block the calling thread (philosopher) until the fork becomes available.
     *
     * @param philosopherId The ID of the philosopher attempting to pick up the fork.
     */
    void get_fork(int philosopherId) {
        try {
            // Log a message if the fork is currently in use and the philosopher needs to wait.
            if(semaphore.getvalue() <= 0) {
                System.out.println("Philosopher " + philosopherId + " is waiting for Fork " + getId());
            }
            semaphore.down(); // Acquire the fork by decreasing the semaphore's permits, possibly waiting if unavailable.
        } catch (InterruptedException ex) {
            Logger.getLogger(Fork.class.getName()).log(Level.SEVERE, null, ex); // Log interruption exceptions.
        }
    }

    /**
     * Releases the fork once a philosopher finishes using it.
     * This is signalled by incrementing the semaphore's permit count, potentially unblocking a waiting philosopher.
     */
    void put_fork() {
        try {  
            semaphore.up(); // Release the fork by incrementing the semaphore's permits.
        } catch (InterruptedException ex) {
            Logger.getLogger(Fork.class.getName()).log(Level.SEVERE, null, ex); // Log any interruption exceptions.
        }
    }
    
    /**
     * Checks if the fork is available for use.
     * 
     * @return true if the fork is free (semaphore permit > 0), otherwise false.
     */
    boolean isFree() {
        return semaphore.getvalue() > 0;  // Evaluate the fork's availability based on the semaphore's current permit count.
    }
}
