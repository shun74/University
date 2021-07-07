import java.net.*;
import java.io.*;
import java.util.*;

class TcpClient {
    public static void main(String args[]) {
	int c;
	Socket s;
	InputStream sIn;
	OutputStream sOut;
	BufferedReader br;
	PrintWriter pw;
	String str;
	StringTokenizer stn;
	if (args.length != 1) {
	    System.out.println("No hostname given");
	    System.exit(1);
	}
	
	try {
	    s = new Socket(args[0], 4321);
	    
	    sIn = s.getInputStream();
	    sOut = s.getOutputStream();	
	    br = new BufferedReader(new InputStreamReader(sIn));
	    pw = new PrintWriter(new OutputStreamWriter(sOut),true);

	    pw.println("hello");
	    str = br.readLine();
	    System.out.println(str);
	    stn = new StringTokenizer(str," ",false);
	    if(!stn.nextToken().equals("ack")){
		System.exit(1);
	    }
	    pw.println("4");
	    str = br.readLine();
	    System.out.println(str);
	    stn = new StringTokenizer(str," ",false);
	    if(!stn.nextToken().equals("ack")){
		System.exit(1);
	    }

	    pw.println("5");
	    str = br.readLine();
	    System.out.println(str);
	    sIn.close();
	    sOut.close();
	    s.close();
	} catch (IOException e) {
	    System.err.println("Caught IOException");
	    System.exit(1);
	}
    }
}
