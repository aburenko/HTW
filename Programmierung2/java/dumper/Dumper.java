import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.io.*;

class Dumper extends Panel
{
    TextField tf;
    HexArea ha;
    
    
    class HexArea extends TextArea 
    {
        TextField tf;
        
        HexArea(TextField a) {
            tf = a;
        }
        
        void setHexDump() {
            try
            {
                URL url =new URL(tf.getText());
                InputStream i= url.openStream();
                HexDump h = new HexDump(i);
                this.setText(h.getHexString());
            }
            catch (MalformedURLException ex)
                {System.out.println(ex);System.exit(1);}
            catch(IOException ex)
                {System.out.println(ex);System.exit(1);}
        }
    }
    
    KeyListener enterListener = new KeyListener() {
        @Override
        public void keyPressed(KeyEvent e)
        {
            if(e.getKeyCode() == 10)
            {
               ha.setHexDump();
            }
        }
        public void keyReleased(KeyEvent e){}
        public void keyTyped(KeyEvent e){}
    };

    Dumper() 
    {
        setFont(new Font("System", Font.PLAIN, 24));
        setLayout(new BorderLayout());
        tf = new TextField(40);
        Label tfl = new Label("Enter File"); 
        
        ha = new HexArea(tf);
        ha.setFont(new Font("Courier", Font.PLAIN, 14));
        ha.setEditable(false);
        
        tf.addKeyListener(enterListener);
        
        //panel for north
        Panel northPanel = new Panel();
        northPanel.add(tfl);
        northPanel.add(tf);
        
        add(northPanel, BorderLayout.NORTH);
        add(ha, BorderLayout.CENTER);
    }
    
    public static void main(String args[])
    {
        Frame F=new Frame();
        F.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent we)
                { System.exit(0); }
        });
        Dumper p = new Dumper();
        F.add(p);
        F.pack();
        F.setVisible(true);
    }
}
