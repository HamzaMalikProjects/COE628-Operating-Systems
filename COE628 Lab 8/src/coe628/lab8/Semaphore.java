package coe628.lab8;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Implements a semaphore mechanism to control access to resources, following
 * the concept invented by Edsger Dijkstra.
 * <p>
 * Semaphores are used to manage concurrent access to a set of resources. The
 * semaphore's value represents the number of resources available. A semaphore
 * can increment (signal) or decrement (wait) its value to control resource
 * access.
 * </p>
 *
 * @see <a href="http://en.wikipedia.org/wiki/Semaphore_(programming)">Semaphore (Programming) - Wikipedia</a>
 */
public class Semaphore {

    /**
     * The current value of the semaphore, indicating the number of available resources.
     */
    private int value;

    /**
     * Initializes a new Semaphore instance with a specified initial value.
     *
     * @param value The initial number of available resources (must be non-negative).
     */
    public Semaphore(int value) {
        if (value < 0) {
            throw new IllegalArgumentException("Semaphore initial value must be >= 0.");
        }
        this.value = value;
    }

    /**
     * Increments the semaphore's value, potentially releasing a waiting thread.
     * This method is non-blocking and may wake up a thread that is waiting for
     * a resource to become available.
     */
    public synchronized void up() {
        value++;
        // Notifies one waiting thread
        notify();
    }

    /**
     * Decrements the semaphore's value, requesting a resource. If no resources
     * are available (value is 0), the calling thread will block until a resource
     * becomes available.
     * 
     * This method blocks if there are no available resources, ensuring exclusive
     * access to a resource.
     */
    public synchronized void down() {
        // Loop to handle spurious wakeups
        while (value == 0) {
            try {
                // Wait until a resource becomes available
                wait();
            } catch (InterruptedException e) {
                // Re-interrupt the current thread if interrupted during wait
                Thread.currentThread().interrupt();
                // Optionally, handle the interruption or exit the method
                return;
            }
        }
        value--;
    }
}
