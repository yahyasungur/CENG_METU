import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Scribe implements Runnable {
    private static int nextId = 1;
    private static int pens;
    private static int bottles;
    private static Lock penLock;
    private static Lock bottleLock;

    private int id;

    public Scribe() {
        id = nextId++;
    }

    @Override
    public void run() {
        while (true) {
            try {
                // Acquire a pen
                penLock.lock();
                if (pens > 0) {
                    pens--;
                    System.out.println("Scribe " + id + " takes a pen");
                    penLock.unlock();    
                } else {
                    penLock.unlock(); // Release the pen lock if no pen is available
                    Thread.sleep(1000); // Wait for a pen to be available
                    continue; // Retry
                }

                // Acquire an ink bottle
                bottleLock.lock();
                if (bottles > 0) {
                    bottles--;
                    System.out.println("Scribe " + id + " takes a bottle");
                    bottleLock.unlock(); // Release the bottle lock
                } else {
                    // Put back the pen since no bottle is available
                    bottleLock.unlock(); // Release the bottle lock
                    penLock.lock();
                    pens++;
                    System.out.println("Scribe " + id + " puts the pen back");
                    penLock.unlock(); // Release the pen lock
                    Thread.sleep(1000); // Wait for a bottle to be available
                    continue; // Retry
                }

                // Write a record
                System.out.println("Scribe " + id + " writes a record");

                // Put back the pen and bottle
                penLock.lock();
                bottleLock.lock();
                pens++;
                bottles++;
                System.out.println("Scribe " + id + " puts the pen back");
                System.out.println("Scribe " + id + " puts the bottle back");

                // Release the locks
                penLock.unlock();
                bottleLock.unlock();

                // Sleep for a while before the next iteration
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        int numberOfScribes = Integer.parseInt(args[0]);
        pens = Integer.parseInt(args[1]);
        bottles = Integer.parseInt(args[2]);
        penLock = new ReentrantLock();
        bottleLock = new ReentrantLock();

        for (int i = 0; i < numberOfScribes; i++) {
            Thread thread = new Thread(new Scribe());
            thread.start();
        }
    }
}
