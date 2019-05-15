package philosophenProblem;

import java.util.*;
import philosophenProblem.Philosoph;

public class Table {

    public static int FORK_NUMBER = 5;
    private boolean[] forkUsed;

    public Table() {
        // create and init untaken
        forkUsed = new boolean[FORK_NUMBER];
        for(int k=0; k < FORK_NUMBER; k++)
            forkUsed[k] = false;
    }
    
    public synchronized boolean takeFork(int number) {
        if(forkUsed[number]) return false;
        forkUsed[number] = true;
        return true;
    }
    
    public synchronized void putFork (int number) {
        forkUsed[number] = false;
    }
}
