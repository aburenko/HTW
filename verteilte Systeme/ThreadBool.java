import java.util.*;


public class ThreadBool implements Runnable {
    public static final int arraySize = 50000000;
    public static final int n = 8; // threads number
    public static int trueNum = 0;
    public static int trueNumLoop = 0;
    public static int threadsNum = 0;
    
    public static boolean []feld = new boolean[arraySize];

    private int startN;
    private int endN;
    private int result;
    
    ThreadBool(int start, int end) {
        startN = start;
        endN = end;
    }
    
    public static void main(String[] args) {
        //System.out.println(Runtime.getRuntime().availableProcessors()); //=> 8
        // create random object
        Random random = new Random();
        
        for (int i=0; i<arraySize; i++) {
            // get next next boolean value 
            feld[i] = random.nextBoolean();
        }
        Thread []threads = new Thread[n];
        // create Threads
        for (int i=0; i<n; i++) { 
            ThreadBool counter = new ThreadBool(i*(arraySize/n),(i+1)*(arraySize/n));
            threads[i] = new Thread(counter);
            threads[i].start();
        }        
        // wait at all threads
        for (int i=0; i<n; i++) {
            try {
                threads[i].join();
            } catch(Exception e) {
                e.printStackTrace();
            }
        }
        for (int i=0; i<arraySize; i++) {
            if(feld[i]) trueNumLoop++;
        }
        
        System.out.println("result tatsaechlich:" + trueNumLoop);
        System.out.println("result from all:" + trueNum);
    }
    
    
    @Override
    public void run() {
        /*
        try {
            Thread.sleep(1000);
        } catch (Exception e) {
            e.printStackTrace(); 
        }
        */
        for(int i=startN; i<endN; i++)
        {
            if(feld[i]) result++;
        }
        trueNum += result;
    }
    
}
