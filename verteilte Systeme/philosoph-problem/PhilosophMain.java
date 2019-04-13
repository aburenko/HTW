import java.util.*;
import philosophenProblem.*;

public class PhilosophMain {
    public static void main(String[] args) {
        Table t = new Table();
        
        Thread []threads = new Thread[t.FORK_NUMBER];
        // create Philosophs
        for (int i=0; i<t.FORK_NUMBER; i++) { 
            Philosoph phil = new Philosoph(t,i);
            threads[i] = new Thread(phil);
            threads[i].start();
        }
        
        // wait for all to eat
        for (int i=0; i<t.FORK_NUMBER; i++) {
            try {
                threads[i].join();
            } catch(Exception e) {
                e.printStackTrace();
            }
        }
        
        System.out.println("All Philosophs eaten");
    }
}
