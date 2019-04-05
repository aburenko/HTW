import java.awt.*;
import java.awt.event.*;

class CalculatorGB extends Panel
{
  // hier Referenzen fuer Komponenten 
  // (Buttons, Textfields, Panels) vereinbaren
  TextField tf;
  String buttons[][] = { {"M+", "7", "8", "9", "/"}, 
                       {"M-", "4", "5", "6", "*"}, 
                       {"MR", "1", "2", "3", "-"}, 
                       {"CE", "0", ".", "=", "+"}
                     };
  
  Button tmpB;
  GridBagConstraints C=new  GridBagConstraints();
  
  
  String op = new String("=");
  double val = 0;
  boolean clear = false;
    ActionListener nL = new ActionListener() 
    {
        @Override
        public void actionPerformed(ActionEvent e) {
            if(clear) {
                tf.setText("");
                clear = false;
            }
            tf.setText(tf.getText() + e.getActionCommand());
        }
    };

    ActionListener nCE = new ActionListener() 
    {
        @Override
        public void actionPerformed(ActionEvent e) {
            tf.setText("");
            val = 0;
            op = "";
        }
    };

    ActionListener nOp = new ActionListener() 
    {
        @Override
        public void actionPerformed(ActionEvent e) {
            double newVal = Double.parseDouble(tf.getText());
            String newOperation = e.getActionCommand();
            System.out.println(newOperation);
            System.out.println(String.valueOf(op));
            switch(op) {
            case "+" :
                val += newVal;
                break;
            case "-" :
                val -= newVal;
                break;
            case "*" :
                val *= newVal;
                break;
            case "/" :
                val /= newVal;
                break;
            case "=" :
                val = newVal;
            }
            clear = true;    
            op = newOperation;
            tf.setText(String.valueOf(val));
            System.out.println(String.valueOf(val));
            System.out.println(String.valueOf(newVal));
        }
    };

    
  ActionListener actionEvents [][] = { 
                        { nL,  nL, nL, nL,  nOp}, 
                        { nL,  nL, nL, nL,  nOp}, 
                        { nL,  nL, nL, nL,  nOp}, 
                        { nCE, nL, nL, nOp, nOp}
                };
  
  public CalculatorGB()
  {
    // Komponenten erzeugen und zu Oberflaeche zusammenbauen,
    // Listener verbinden
    setFont(new Font("System", Font.PLAIN, 24));
    setLayout(new GridBagLayout());
    C.fill=GridBagConstraints.BOTH;
    
    
    tf = new TextField(20);
    C.gridx=0; C.gridy=0;
    C.gridwidth=GridBagConstraints.REMAINDER;
    C.weightx=1.0;C.weighty=1.0;
    add(tf,C);
    C.gridwidth=1;
    
    
    
     C.weightx=1.0;C.weighty=1.0;
     for(int i = 0; i < buttons.length; i++) {
        for(int j = 0; j < buttons[i].length; j++) {
             C.gridx=j; C.gridy=i+1;
             tmpB = new Button(buttons[i][j]);
             tmpB.addActionListener(actionEvents[i][j]);
             add(tmpB,C);
        }
     }
     
//     add(keys, BorderLayout.CENTER);
    //addActionListener(...);
  }
  public static void main(String args[])
  {
      Frame F=new Frame();
      F.addWindowListener(new WindowAdapter() {
        public void windowClosing(WindowEvent we)
            { System.exit(0); }
      });
      CalculatorGB p = new CalculatorGB();
      F.add(p);
      F.pack();
      F.setVisible(true);
  }
}
