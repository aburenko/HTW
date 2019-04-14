import java.util.*;
import java.io.*;
import java.lang.*;

class PPWaitNotifyWay{

    public static void print( String m ){
        System.out.println( m );
    }
    
    public static class Table{
        public boolean []forksUsed = new boolean[5];
        
        Table(){
            for( int i = 0; i < forksUsed.length; i++ )
                forksUsed[i] = false;
        }
        
        public synchronized void takeFork( String name, int number ) {
            while( true )
                if( forksUsed[ number ] || forksUsed[ (number + 1) % 5 ] ){
                    try{
                        wait();
                    }catch( InterruptedException e ){} 
                }
                else
                    break;
            
            print( name + " " + number + " nimmt sich Gabel " + number + " und Gabel " + (number +1) % 5 );
            forksUsed[ number ] = true;
            forksUsed[ (number + 1) % 5 ] = true;
        }
        
        public synchronized void putFork( int number ){
            forksUsed[ number ] = false;
            forksUsed[ (number + 1) % 5 ] = false;
            notifyAll();
        }
    }
    
    
    
    public static class Philosopher implements Runnable {      
    /*Threadklasse. Diese besitzt also auch run()*/
        public Table table;
        public int seatNumber;
        public String name;
        
        Philosopher( Table t, int sN, String n ){
            table = t;
            seatNumber = sN;
            name = n;
        }
        
        public void run(){
            while( true ){
                try{
                    Random random = new Random();
                    //think
                    print( name + " " + seatNumber + " denkt.");
                    Thread.sleep( random.nextInt(21) * 1000 );
                    //take Fork
                    table.takeFork( name, seatNumber );
                    //eat
                    print( name + " " + seatNumber + " isst... oder isst nicht.");
                    Thread.sleep( random.nextInt(21) * 1000 );
                    //put fork
                    table.putFork( seatNumber );
                }catch( InterruptedException e ){}
            }
        }
    }
    
    

    public static void main( String[] args ) throws Exception {
        Table t = new Table();
        String name[] = {"Jeremy", "Tony", "Adolf Friedrich", "Johanson", "Bob"};
        for( int i = 0; i < 5; i++ )
            new Thread( new Philosopher( t, i, name[i] ) ).start();  
    }   
    /*Dem Threadobjekt wird das Philosophenobjekt übergeben, welches Runnable implementiert*/ 
}
