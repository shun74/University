
/* NetworkInterfaceInformation.java 
 * java 1.6 t-matsu 4/23 2010
 */
import java.net.*;
import java.util.*;

public class NetworkInterfaceInformation {
    NetworkInterfaceInformation(){ 
	try{
	    Enumeration <NetworkInterface>  nifs = NetworkInterface.getNetworkInterfaces();
	    while(nifs.hasMoreElements()) {
		showInformation(nifs.nextElement());
	    }
	}catch(SocketException e){
	    e.printStackTrace();
	}
    }
    
    void showInformation(NetworkInterface nif)throws SocketException {
	System.out.println("IF Name: "+nif.getName());
	System.out.println("IF Display Name: "+nif.getDisplayName());
        System.out.println("UP: "+ (nif.isUp()?"YES":"NO")); 
        List<InterfaceAddress> iaddrs = nif.getInterfaceAddresses();
        for (InterfaceAddress addr: iaddrs) {
            System.out.println(" IP Addr: "+addr.getAddress());
            System.out.println(" Broadcast Addr: "+addr.getBroadcast());
            System.out.println(" Prefix Len: "+addr.getNetworkPrefixLength());
        }
        byte haddr[] = nif.getHardwareAddress();
        if (haddr != null) {
            System.out.print("MAC Address: ");
            for (int i=0;i<haddr.length;i++) {
                System.out.printf("%02x", haddr[i]);
		if(i!=haddr.length-1)System.out.print(":");
            }
            System.out.println();
        }
	System.out.println("MTU: " + nif.getMTU());
	System.out.println("Loopback: "+(nif.isLoopback()?"YES":"NO"));
	System.out.println("Multicast Support:　" 
			   +(nif.supportsMulticast()?"YES":"NO"));
	System.out.println("Virtual Interface: "+(nif.isVirtual()?"YES":"NO"));
        System.out.println();
    }

    public static void main(String[] args) {
	new NetworkInterfaceInformation();
    }
}
