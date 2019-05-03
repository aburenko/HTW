
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Clock
{
    private long startTime;
    private String currTime;

    public Clock()
    {
        reset();
    }

    public void getTime()
    {
        long elapsedTime;
        long minutes;
        long seconds;
        long milliSecs;
        
        elapsedTime = System.currentTimeMillis() - startTime;
        
        milliSecs = elapsedTime % 1000;
        seconds = (elapsedTime / 1000) % 60;
        minutes = (elapsedTime / 1000) / 60 % 60;
        
        currTime = minutes + ":" + seconds + ":" + milliSecs;
    }

    public void reset()
    {
        startTime = System.currentTimeMillis();
        currTime = "00:00:000";
    }
    
    public String getStrTime() {
        return currTime;
    }
}

class UpdateRequest implements Runnable
{
    private Clock clock;
    private ClockView v;

    public UpdateRequest(Clock clock, ClockView v) {
        this.clock = clock;
        this.v = v;
    }

    public void run() {
        clock.getTime();
        v.showTime();
    }
}

class Ticker extends Thread
{
    private final static long UPDATE_INTERVAL = 10; // Milliseconds
    private UpdateRequest updateReq;

    public Ticker(Clock clock, ClockView cv) {
        updateReq = new UpdateRequest(clock, cv);
    }

    public void run() {
        try {
            while(!isInterrupted()) {
                EventQueue.invokeLater(updateReq);
                Thread.sleep(UPDATE_INTERVAL);
            }
        }
        catch(InterruptedException e) { }
    }
}

class Presenter implements ActionListener
{
    private Clock clock;
    private Ticker ticker;
    private ClockView cv;

    public Presenter()  {
    
    }

    
    public void setTickerAndClock(Ticker t,Clock clock,ClockView cv) {
        this.ticker = t;
        this.clock = clock;
        this.cv = cv;
    }
    
    public void actionPerformed(ActionEvent e) {
        String s = e.getActionCommand();
        if(s == "start") {
            System.out.println("start gedruckt");
            start();
        } else if (s == "stop") {
            System.out.println("stop gedruckt");
            stop();
        } else if (s == "reset") {
            System.out.println("reset gedruckt");
            reset();
        }
    } 
    
    private void start() {
        if(ticker == null)
            ticker = new Ticker(clock,cv);
        ticker.start();
    }
    
    private void stop() {
        if(ticker != null) {
            ticker.interrupt();
            ticker = null;
        }
    }
    
    private void reset() {
        clock.reset();
        cv.showTime();
    }
}

class ClockView 
{
    JLabel ltime;
    Clock c;
    
    public ClockView(Clock c, Presenter p) {
        this.c = c;
    
        JFrame f = new JFrame("Clock");
        f.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        ltime = new JLabel("00:00:00");
        
        JButton bstart,bstop,br;
        bstart = new JButton("start");
        bstart.addActionListener(
            p
        );
        
        bstop = new JButton("stop");
        bstop.addActionListener(
            p
        );
        
        br = new JButton("reset");
        br.addActionListener(
            p
        );
        
        f.add(ltime, BorderLayout.NORTH);
        f.add(bstop, BorderLayout.EAST);
        f.add(br, BorderLayout.SOUTH);
        f.add(bstart, BorderLayout.CENTER);

        f.pack();
        f.setVisible(true);
    }
    
    public void showTime() {
        ltime.setText(c.getStrTime());
    }
}

public class ClockManager
{
    public static void main(String[] args) {
        
        Clock c;
        ClockView cv;
        Ticker t;   
        Presenter p;
        
        p = new Presenter();
        c = new Clock();
        cv = new ClockView(c,p);
        t = new Ticker(c,cv);
        p.setTickerAndClock(t,c,cv);
    }
}
