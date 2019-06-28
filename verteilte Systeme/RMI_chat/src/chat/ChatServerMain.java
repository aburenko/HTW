package chat;

import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ChatServerMain
{
    public static void main(String[] args)
    {
        // create Server
        try {
            ChatServerImpl csi = new ChatServerImpl();
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost/ChatServer", csi);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
