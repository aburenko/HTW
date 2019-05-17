import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.event.*;
import javax.swing.*;
import javax.imageio.ImageIO;
import javax.swing.JFrame;
import java.awt.Graphics;
import javax.swing.JComponent;
import javax.swing.JFrame;
import java.awt.image.WritableRaster;


public class Presenter
{
    public static void main(String[] args) {
        int w = 600;
        int h = 400;
        Presenter p = new Presenter();
        Model m = new Model(w,h,p);
        ViewGUI v = new ViewGUI(w,h,m);
        m.setView(v);
        m.calcImage();
        p.start();
    }
    
    Presenter() {
        
    }
    
    private void start() {
        
    }
    
    private void update() {
        
    }
    
    private void setZoom(double x) {
        
    }
    
    private void setDim(double x) {
        
    }
    
    
}

class Model {
    Presenter p;
    ViewGUI v;
    int w,h;
    public int [][]imageArr; 
    public void setView(ViewGUI v) {
        this.v = v;
    }
    public Model(int w, int h, Presenter p) {
        this.w = w;
        this.h = h;
        this.p = p;
    }
    
    public void calcImage() {
        imageArr = new int[w][h];
        int threadNumber = 8;
        //while(true) {
        System.out.println("let call part count");
            calcImagePart(threadNumber);
        //}
    }    
    
    private void calcImagePart(int threadNumber) {
        Thread []threads = new Thread[threadNumber];
        System.out.println("let count");
        // create Threads
        for (int i=0; i<threadNumber; i++) { 
            CalcImagePart calcPart= new CalcImagePart(i*(h/threadNumber),(i+1)*
            (h/threadNumber),w,h,this);
            threads[i] = new Thread(calcPart);
            threads[i].start();
        }        
        System.out.println("let wait");
        // wait at all threads
        for (int i=0; i<threadNumber; i++) {
            try {
                threads[i].join();
            } catch(Exception e) {
                e.printStackTrace();
            }
        }
        System.out.println("let repaint");
        v.paintComponent();
    }
    
    private void setParam(int w, int h) {
        this.w = w;
        this.h = h;
    }
    
    public Image getImageFromArray() {
        BufferedImage image = new BufferedImage(w, h,
            BufferedImage.TYPE_INT_ARGB);
        WritableRaster raster = (WritableRaster) image.getData();
        
        int i = 0;
        int []pixelsOne = new int[w*h];
        // turn two dem array to one dem array
        for (int[] sublist : imageArr) {
            for (int elem : sublist) {
                pixelsOne[i] = elem;
            }
        }
        
        
        raster.setPixels(0,0,w,h,pixelsOne);
        return image;
    }
}

class CalcImagePart implements Runnable {
    int yS,yE,w,h;
    Model m;
    public CalcImagePart(int yS,int yE, int w, int h, Model m) {
        this.yS = yS;
        this.yE = yE;
        this.w = w;
        this.h = h;
        this.m = m;
    }
    @Override
    public void run() {
        for(int i=yS; i<yE; i++) {
            for(int j=0; j<w; j++) {
                System.out.println("st");
                if( iter(toMOTO(i,yE),toMOTO(j,w)))
                    m.imageArr[i][j] = 1;
                else   
                    m.imageArr[i][j] = 0;
                System.out.println("end");
            }
                System.out.println("raus");
        }
    }
    // a,b = -1...0...1
    private boolean iter(double a,double b) {
        double x = 0.0;
        double y = 0.0;
        int iterations = 0;
        int max_iterations = 100;
        do {
            double xnew = x * x - y * y + a;
            double ynew = 2 * x * y + b;
            x = xnew;
            y = ynew;
            iterations++;
            if(iterations == max_iterations)
                return false;
        } while(x <= 2 && y <= 2);
        return true;
    }
    
    private double toMOTO(int x, int xMax) { // converts to minus one to one 
        return ((double)x) / ((double)xMax) * 2.0 - 1.0;
    }
}

//http://www.java2s.com/Tutorial/Java/0261__2D-Graphics/CreateBufferredImagewithcolorsbasedonintegerarray.htm
class ViewGUI extends JPanel {
    int w;
    int h;
    Model m;
    JFrame frame;
    JLabel jl;
    JButton jb;
    
    public ViewGUI(int w, int h, Model m) 
    {
        frame = new JFrame();
        frame.setSize(w, h);
        frame.getContentPane().setLayout(new FlowLayout());
        jl = new JLabel();
        frame.getContentPane().add(jl);
        JButton jb = new JButton("test");
        frame.getContentPane().add(jb);
        frame.pack();
        frame.setVisible(true);
        this.w = w;
        this.h = h;
        this.m = m;
    }
    
    public void paintComponent() {
        System.out.println("do repaint");
        frame = new JFrame();
        frame.getContentPane().setLayout(new FlowLayout());
        Image img = m.getImageFromArray();
        jl = new JLabel(new ImageIcon(img));
        frame.getContentPane().add(jl);
        JButton jb = new JButton("testABC");
        frame.getContentPane().add(jb);
        frame.pack();
        frame.setVisible(true);
    }

}