import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.event.*;
import javax.swing.*;
import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class Presenter
{
    public static void main(String[] args) {
        int w = 600;
        int h = 400;
        Presenter p = new Presenter();
        Model m = new Model(w,h,p);
        ViewGUI v = new ViewGUI(w,h,m);
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
    int w,h;
    public boolean [][]imageArr; 
    
    public Model(int w, int h, Presenter p) {
        this.w = w;
        this.h = h;
        this.p = p;
    }
    
    private void calcImage() {
        imageArr = new int[w][h];
        int threadNumber = 8;
        //while(true) {
            calcImagePart(threadsNum);
        //}
    }    
    
    private void calcImagePart(int threadNumber) {
        Thread []threads = new Thread[threadNumber];
        // create Threads
        for (int i=0; i<threadNumber; i++) { 
            ThreadBool calcPart= new CalcImagePart(i*(h/n),(i+1)*(h/n),w,h,this);
            threads[i] = new Thread(calcPart);
            threads[i].start();
        }        
        // wait at all threads
        for (int i=0; i<n; i++) {
            try {
                threads[i].join();
            } catch(Exception e) {
                e.printStackTrace();
            }
        }
    }
    
    private void setParam(int w, int h) {
        this.w = w;
        this.h = h;
    }
}

class CalcImagePart implements Runnable {
    int yS,yE,w;
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
                m.imageArr[i][j] = iter(toMOTO(i),toMOTO(j));
            }
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
class ViewGUI extends JComponent {
    int w;
    int h;
    Model m;
    
    public ViewGUI(int w, int h, Model m) {
        JFrame frame = new JFrame("ColorPan");
        frame.getContentPane().add(new ColorPan());
        frame.setSize(w, h);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        this.w = w;
        this.h = h;
        this.m = m;
    }
    
    public void paint(Graphics g) {
        int width = getSize().width;
        int height = getSize().height;
        m.imageArr;
        int i = 0;
        for (int y = 0; y < height; y++) {
        int red = (y * 255) / (height - 1);
        for (int x = 0; x < width; x++) {
            int green = (x * 255) / (width - 1);
            int blue = 128;
            data[i++] = (red << 16) | (green << 8) | blue;
        }
        }
        BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        image.setRGB(0, 0, width, height, data, 0, width);
        g.drawImage(image, 0, 0, this);
    }

}