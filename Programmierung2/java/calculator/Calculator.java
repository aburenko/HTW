import java.awt.*;
import java.awt.event.*;

class Calculator extends Panel
{
  // hier Referenzen fuer Komponenten 
  // (Buttons, Textfields, Panels) vereinbaren
  TextField tf;
  String buttons[] = { "M+", "7", "8", "9", "/", 
                       "M-", "4", "5", "6", "*", 
                       "MR", "1", "2", "3", "-", 
                       "CE", "0", ".", "=", "+"
                     };
  
  Button tmpB;
  
  public Calculator()
  {
    // Komponenten erzeugen und zu Oberflaeche zusammenbauen,
    // Listener verbinden
    setFont(new Font("System", Font.PLAIN, 24));
    setLayout(new BorderLayout());
    tf = new TextField();
    Panel keys = new Panel(new GridLayout(4,5));
    add(tf, BorderLayout.NORTH);
    for(int i = 0; i < buttons.length; i++) {
            tmpB = new Button(buttons[i]);
            keys.add(tmpB);
    }
    add(keys, BorderLayout.CENTER);
    //addActionListener(...);
  }

  public static void main(String args[])
  {
      Frame F=new Frame();
      F.addWindowListener(new WindowAdapter() {
        public void windowClosing(WindowEvent we)
            { System.exit(0); }
      });
      Calculator p = new Calculator();
      F.add(p);
      F.pack();
      F.setVisible(true);
  }
}
