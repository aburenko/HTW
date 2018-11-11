import java.io.*;

class taxi {

    public static void main(String args[]) {
        try {
            FileInputStream fis = new       FileInputStream("Taxigeschichten.txt");
            int availibleBytes = fis.available();
            byte [] byteArr = new byte [availibleBytes];
            fis.read(byteArr, 0, availibleBytes);
            System.out.println(new String(byteArr));
        } catch (Exception e) {
            System.out.println("error: " + e);
        }
        
    }

};