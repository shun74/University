import java.net.*;
import java.io.*;

public class ChatClient extends Thread{
    Socket socket;
    BufferedReader br,stdin_br;
    PrintWriter pw;
    static int port = 25555;
    
    ChatClient(String server){
	try{
	    socket = new Socket(server,port);
	    br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
	    this.start();
	    while(true){
		System.out.println(br.readLine());
	    }
	}catch(IOException e){
	    e.printStackTrace();
	    System.exit(1);
	}
    }

    public void run(){
	try{
	    pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()),true);
	    stdin_br = new BufferedReader(new InputStreamReader(System.in));
	    while(true){
		String str = stdin_br.readLine();
		if(str.equals("quit")){
		    break;
		}
		pw.println(str);
	    }

	    socket.close();
	}catch(IOException e){
	    e.printStackTrace();
	}
    }

    public static void main(String args[]){
	if(args.length==3){
	    port =Integer.parseInt(args[1]);
	}
	new ChatClient(args[0]);
	
    }

}