import java.util.concurrent.Semaphore;

public class Pre2 implements Runnable {
    // Declare the necessary semaphores
    private static Semaphore penSemaphore;
    private static Semaphore bottleSemaphore;

    // Declare the necessary variables
    private static int order = 1;
    private static int numberOfPens;
    private static int numberOfBottles;

    private int id;

    // Constructor
    public Pre2() {
        id = order++;
    }
    
    @Override
    public void run() {
        while(true){
            try{
                // Acquire a bottle
                bottleSemaphore.acquire();
                System.out.println("Scribe " + id + " takes a bottle");

                // try to acquire a pen and if not available, put back the bottle and retry
                if(!penSemaphore.tryAcquire()){
                    System.out.println("Scribe " + id + " puts the bottle back");
                    bottleSemaphore.release();
                    Thread.sleep(1000);
                    continue;
                }else{
                    // Acquire a pen
                    System.out.println("Scribe " + id + " takes a pen");
                }

                // Write a record
                System.out.println("Scribe " + id + " writes a record");

                // Put back the pen and bottle
                System.out.println("Scribe " + id + " puts the pen back");
                penSemaphore.release();
                System.out.println("Scribe " + id + " puts the bottle back");
                bottleSemaphore.release();
                
                // Sleep for 1 second
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        int numberOfScribes = Integer.parseInt(args[0]);
        numberOfPens = Integer.parseInt(args[1]);
        numberOfBottles = Integer.parseInt(args[2]);
        penSemaphore = new Semaphore(numberOfPens, true);
        bottleSemaphore = new Semaphore(numberOfBottles, true);

        // Create and start the scribe threads
        Thread[] scribes = new Thread[numberOfScribes];
        for (int i = 0; i < numberOfScribes; i++) {
            scribes[i] = new Thread(new Pre2());
            scribes[i].start();
        }
    }
}
