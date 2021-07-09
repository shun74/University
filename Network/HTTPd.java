/*     HTTPd.java
 * 
 *     t-matsu  4/29 2010
 */

import java.io.*;
import java.net.*;
import java.util.*;

class HTTPd {
    private final String dir ="C:/work/network/";
    HTTPd(){
	try{
	    ServerSocket ss = new ServerSocket(8000);
	    while(true){
		Socket socket = ss.accept();
		System.out.println("Connect From : "+
				   (socket.getInetAddress()).getHostName());
		BufferedReader br = new BufferedReader
		    (new InputStreamReader(socket.getInputStream()));
		OutputStream os = socket.getOutputStream();

		String buffer = br.readLine();
		br.readLine();
		StringTokenizer stn = new StringTokenizer(buffer," ",false);
		String msg = stn.nextToken();
		String file = stn.nextToken();
		if(!msg.equals("GET")){
		    continue;
		}
		System.out.println("file ="+file);
		if(file.equals("/")){
		    file="/index.html";
		}
		System.out.println(dir+file);
		
		FileInputStream fis;
		try{
		    fis = new FileInputStream(dir+""+file);
		}catch(FileNotFoundException fnfe){
		    System.out.println("file not found: "+file);
		    os.write("HTTP/1.1 404 Not Found\r\n".getBytes());
		    fis = new FileInputStream("404notfound.html");
		}
		byte[] buf = new byte[1024];
		while(true){
		    int n = fis.read(buf);
		    System.out.println("read "+n+" bytes");
		    if(n==-1)break;
		    os.write(buf,0,n);
		}
		socket.close();
		fis.close();
	    }
	    
	}catch(IOException e){
	    e.printStackTrace();
	    System.exit(1);
	}
    }
    public static void main(String args[]){
	new HTTPd();
    }
}