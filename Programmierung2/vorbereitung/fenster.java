import java.awt.*;
import java.awt.event.*;

class fenster extends Panel{

    public fenster() {
        setFont(new Font("System", Font.PLAIN, 24));
        setLayout(new BorderLayout());
        TextField tf = new TextField(40);
        this.add(tf, BorderLayout.CENTER);
    }

    public static void main(String args[]) 
    {
        Frame F = new Frame();
        F.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent we)
            { System.exit(0);}
        });
        fenster p = new fenster();
        F.add(p);
        F.pack();
        F.setVisible(true);
    }
}