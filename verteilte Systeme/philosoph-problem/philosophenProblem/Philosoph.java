package philosophenProblem;

import java.util.*;
import philosophenProblem.Table;

public class Philosoph implements Runnable {

    public static String[] philosophNames = {
        "Peter", "Boris", "Angela", "Mia", "Plati"
    };
    private int place;
    private boolean leftFork, rightFork;
    private int leftForkIndex, rightForkIndex;
    private Table table;
    private String myName;
    
    public Philosoph (Table t, int index) {
        table = t;
        place = index;
        myName = philosophNames[place];
        leftForkIndex = place;
        rightForkIndex = (place + 1) % t.FORK_NUMBER;
    }
    
    private boolean takeFork(int number) {
        return table.takeFork(number);
    }
    
    private void putFork (int number) {
        table.putFork(number);
    }
    
    private void think() {
        int ss = sleepRandom();
        System.out.println(myName + " was thinking " + ss + "s");
    }
    
    private boolean eat() {
        int ss = sleepRandom();
        System.out.println(myName + " was eating " + ss + "s");
        if(leftFork && rightFork) return true;
        return false;
    }
    
    private int sleepRandom() {
        Random random = new Random();
        int secondsNumber = random.nextInt(21);
        try {
            Thread.sleep(secondsNumber * 1000);
        } catch (Exception e) {
            e.printStackTrace(); 
        }
        return secondsNumber;
    }
    
    // Ablauf: think - takeFork - eat - putFork
    @Override
    public void run() {
        boolean ate = false;
        while(true) {
            think();
            
            leftFork = takeFork(leftForkIndex);
            rightFork = takeFork(rightForkIndex);
            
            ate = eat();
            
            if(leftFork) putFork(leftForkIndex);
            if(rightFork) putFork(rightForkIndex);
            
            if(ate) break;
        }
        System.out.println(myName + " ate :) .");
    }
    
}
