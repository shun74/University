
/*     SendMailWindow.java
 * 
 *     t-matsu  5/28 2010
 */
 
import java.awt.event.*;
import javax.swing.*;

public class SendMailWindow extends JFrame{
    JTextField to,from,subject;
    JTextArea message;
    public static void main(String args[]){
	new SendMailWindow();
    }

    SendMailWindow(){
	
	super("MailClient");
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	setSize(500,400);
	
	// GUIコンポーネントの生成
	JLabel label1 = new JLabel("To:");
	JLabel label2 = new JLabel("From:");
	JLabel label3 = new JLabel("Subject:");
	message = new JTextArea(20,40);
	message.setLineWrap(true);
	to = new JTextField(20);
	from = new JTextField(20);
	subject = new JTextField(20);
	JButton send = new JButton("Send");
	
	send.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
		    //send ボタンが押された時の処理を書く
			
		    //とりあえず入力された文字を標準出力に出している
		    System.out.println(to.getText());
		    System.out.println(from.getText());
		    System.out.println(subject.getText());
		    System.out.println(message.getText());
		    
		    dispose();  //window破棄
		}
	    });

	GroupLayout layout = new GroupLayout(getContentPane());
	getContentPane().setLayout(layout);
	layout.setAutoCreateGaps(true);
	layout.setAutoCreateContainerGaps(true);

	//水平方向の並べ方指定
	layout.setHorizontalGroup(layout.createSequentialGroup()
				  .addGroup(layout.createParallelGroup()
					    .addComponent(label1)
					    .addComponent(label2)
					    .addComponent(label3)
					    .addComponent(send)
					    )
				  .addGroup(layout.createParallelGroup()
					    .addComponent(to)
					    .addComponent(from)
					    .addComponent(subject)
					    .addComponent(message)
					    )
				  );
				  
	//垂直方向の並べ方指定
	layout.setVerticalGroup(layout.createSequentialGroup()
				.addGroup(layout.createParallelGroup()
					  .addComponent(label1)
					  .addComponent(to)
					  )
				.addGroup(layout.createParallelGroup()
					  .addComponent(label2)
					  .addComponent(from)
					  )
				.addGroup(layout.createParallelGroup()
					  .addComponent(label3)
					  .addComponent(subject)
					  )
				.addGroup(layout.createParallelGroup()
					  .addComponent(send)
					  .addComponent(message)
					  )
				  );
				  
	setVisible(true);  //Window 表示
    }
}