import java.util.concurrent.Semaphore;

public class Lab2 implements Runnable{
    
    // Create necessary variables
    private static int order = 1;
    private static int numberOfPens;
    private static int numberOfBottles;
    private static int numberOfBooks;
    private static int numberOfScribes;

    // Create necessary semaphores
    private static Semaphore penSemaphore;
    private static Semaphore bottleSemaphore;
    private static Semaphore bookSemaphore;

    private int id;

    // Constructor
    public Lab2() {
        id = order++;
    }

    @Override
    public void run() {
        while(true){
            try {
                // Get pen
                penSemaphore.acquire();
                System.out.println("Scribe " + id + " takes a pen");

                // Try to get bottle and if not, release pen and try again
                if(!bottleSemaphore.tryAcquire()){
                    System.out.println("Scribe " + id + " puts the pen back");
                    penSemaphore.release();
                    Thread.sleep((int)(Math.random() * 10000));
                    continue;
                } else {
                    System.out.println("Scribe " + id + " takes a bottle");

                    // Try to get book and if not, release pen and bottle and try again
                    if(!bookSemaphore.tryAcquire()){
                        System.out.println("Scribe " + id + " puts the bottle back");
                        bottleSemaphore.release();
                        System.out.println("Scribe " + id + " puts the pen back");
                        penSemaphore.release();
                        Thread.sleep((int)(Math.random() * 10000));
                        continue;
                    } else {
                        System.out.println("Scribe " + id + " takes a book");
                        // Write
                        System.out.println("Scribe " + id + " writes a record");
                    }
                }

                // Release book
                System.out.println("Scribe " + id + " puts the book back");
                bookSemaphore.release();
                // Release bottele
                System.out.println("Scribe " + id + " puts the bottle back");
                bottleSemaphore.release();
                // Release pen
                System.out.println("Scribe " + id + " puts the pen back");
                penSemaphore.release();
                // Sleep
                Thread.sleep((int)(Math.random() * 10000));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    

    public static void main(String[] args) {
        // Get arguments
        numberOfScribes = Integer.parseInt(args[0]);
        numberOfPens = Integer.parseInt(args[1]);
        numberOfBottles = Integer.parseInt(args[2]);
        numberOfBooks = Integer.parseInt(args[3]);

        // Create semaphores
        penSemaphore = new Semaphore(numberOfPens);
        bottleSemaphore = new Semaphore(numberOfBottles);
        bookSemaphore = new Semaphore(numberOfBooks);

        // Create scribes threads and start them
        Thread[] scribes = new Thread[numberOfScribes];
        for (int i = 0; i < numberOfScribes; i++) {
            scribes[i] = new Thread(new Lab2());
            scribes[i].start();
        }
    }
}
