import java.net.*;
import java.io.*;
import javax.net.ssl.*;
import java.util.Base64;

/*
 * This example demostrates how to use a SSLSocket as client to
 * send a HTTP request and get response from an HTTPS server.
 * It assumes that the client is not behind a firewall
 */

public class SSLClient {

    public static void main(String[] args) throws Exception {
        try {
            
            String adresse = "www2.htw-dresden.de";
            String filepath = "/~jvogt/it1/test.pdf";
            String login = "it1:VLIT1";
            int port = 443; //443
        
            String codiertLogin = Base64.getEncoder().encodeToString(login.getBytes("utf-8"));
        
            SSLSocketFactory factory =
                (SSLSocketFactory)SSLSocketFactory.getDefault();
            SSLSocket socket =
                (SSLSocket)factory.createSocket(adresse, 443);

            /*
             * send http request
             *
             * Before any application data is sent or received, the
             * SSL socket will do SSL handshaking first to set up
             * the security attributes.
             *
             * SSL handshaking can be initiated by either flushing data
             * down the pipe, or by starting the handshaking by hand.
             *
             * Handshaking is started manually in this example because
             * PrintWriter catches all IOExceptions (including
             * SSLExceptions), sets an internal error flag, and then
             * returns without rethrowing the exception.
             *
             * Unfortunately, this means any error messages are lost,
             * which caused lots of confusion for others using this
             * code.  The only way to tell there was an error is to call
             * PrintWriter.checkError().
             */
            socket.startHandshake();

            PrintWriter out = new PrintWriter(
                                  new BufferedWriter(
                                  new OutputStreamWriter(
                                  socket.getOutputStream())));

            out.printf("GET %s HTTP/1.1\r\n", filepath);
            out.printf("Host:%s\r\n", adresse);
            out.printf("Authorization: Basic %s\r\n\r\n", codiertLogin);
            //out.printf("Authorization: Basic aXQxOlZMSVQx\r\n\r\n", codiertLogin);
            out.flush();

            /*
             * Make sure there were no surprises
             */
            if (out.checkError())
                System.out.println(
                    "SSLSocketClient:  java.io.PrintWriter error");

            /* read response */
            BufferedReader in = new BufferedReader(
                                    new InputStreamReader(
                                    socket.getInputStream()));

            String inputLine;
            while ((inputLine = in.readLine()) != null)
                System.out.println(inputLine);

            in.close();
            out.close();
            socket.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
