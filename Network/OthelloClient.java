import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

class OthelloClient {
	final static int WHITE = -1;
	final static int BLACK = 1;
	Socket s;
	InputStream sIn;
	OutputStream sOut;
	BufferedReader br;
	PrintWriter pw;
	String str;
	StringTokenizer stn;
	int my_color = 1;

	public OthelloClient(String hostname, String port){
		int[] board_state = new int[64];
		board_state = new int[]{
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 1,-1, 0, 0, 0,
			0, 0, 0,-1, 1, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0
		};
		ArrayList<ArrayList<Integer>> available_list = new ArrayList<ArrayList<Integer>>();
		available_list = available_check_and_count(convert_board_type(board_state),my_color);

		try {
			s = new Socket(hostname,Integer.parseInt(port));
			sIn = s.getInputStream();
			sOut = s.getOutputStream();
			br = new BufferedReader(new InputStreamReader(sIn));
			pw = new PrintWriter(new OutputStreamWriter(sOut),true);
		} catch (IOException e) {
			System.err.println("Caught IOException");
			System.exit(1);
		}
		while(true){
			try {
				str = br.readLine();
				// System.out.println(str);
				String[] str_splited = str.split(" ");
				if(str_splited.length < 1) continue;
				if(str_splited[0].equals("START")){
					if(str_splited[1].equals("-1")){
						my_color = WHITE;
					} else {
						my_color = BLACK;
					}
					sendMessage("NICK 6319050");
					sendMessage("SAY hello");
				} else if(str_splited[0].equals("END")){
					System.out.println("GG");
					break;
				} else if(str_splited[0].equals("TURN")){
					if(Integer.parseInt(str_splited[1]) == my_color){
						available_list = available_check_and_count(convert_board_type(board_state),my_color);
						int[] won_sum = new int[available_list.size()];
						int[] count = new int[available_list.size()];
						for(int i=0;i<won_sum.length;i++){
							won_sum[i] = 0;
							count[i] = 0;
						}
						long start = System.currentTimeMillis();
						System.out.println("Searching...");
						while(System.currentTimeMillis()-start < (long)1000){
							Random r = new Random();
							int index = r.nextInt(available_list.size());
							int[][] pre_board = convert_board_type(board_state);
							pre_board = flip_stones(pre_board,available_list.get(index).get(0),available_list.get(index).get(1),my_color);
							won_sum[index] += game_agent(pre_board,my_color*(-1));
							count[index]++;
						}
						float max_won = 0;
						int max_index = 0;
						for(int i=0;i<won_sum.length;i++){
							if(max_won<(float)won_sum[i]/(float)count[i]){
								max_index = i;
								max_won = (float)won_sum[i]/(float)count[i];
							}
							System.out.println(available_list.get(i).get(0)+","+available_list.get(i).get(1)+" "+((float)(won_sum[i])/(float)(count[i]))+"%");
						}

						int x = available_list.get(max_index).get(0);
						int y = available_list.get(max_index).get(1);

						System.out.println("PUT"+available_list.get(max_index).get(0)+","+available_list.get(max_index).get(1));
						put_stone(x,y);
					} else {
						continue;
					}
				} else if(str_splited[0].equals("BOARD")){
					for(int i=0;i<64;i++){
						board_state[i] = Integer.parseInt(str_splited[1+i]);
					}
				} else if(str_splited[0].equals("ERROR")){
						Random rand1 = new Random();
						Random rand2 = new Random();
						int x = rand1.nextInt(8);
						int y = rand2.nextInt(8);
						put_stone(x,y);
				} else if(str_splited[0].equals("CLOSE")) {
					System.out.println("Enemy DC");
					break;
				}
			} catch (IOException e) {
				System.err.println("Caught IOException");
				System.exit(1);
			}
		}
	}
	public static void main(String args[]) {
		if (args.length < 1) {
			System.out.println("No hostname or port given");
			System.exit(1);
		}

		new OthelloClient(args[0],args[1]);
    }

	void sendMessage(String str){
		pw.print(str+"\r\n");
		pw.flush();
	}

	void put_stone(int x, int y){
		sendMessage("PUT " + x + " " + y);
	}

	int[][] convert_board_type(int[] board){
		int[][] new_board = new int[8][8];
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				new_board[j][i] = board[8*j+i];
			}
		}
		return new_board;
	}

	int[][] flip_color(int[][] board){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				board[i][j] = board[i][j]*(-1);
			}
		}
		return board;
	}

	ArrayList<ArrayList<Integer>> available_check_and_count(int[][] board, int turn){
		// Your stone is 1,enemy stone is -1
		if(turn==WHITE) {
			board = flip_color(board);
		}
		ArrayList<ArrayList<Integer>> available_list = new ArrayList<ArrayList<Integer>>();
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				int count = 0;
				boolean flag = false;
				if(board[i][j]!=0) continue;
				// ←left
				if(i>=2){
					if(board[i-1][j]==-1){
						for(int k=i-2;k>=0&&board[k][j]!=0;k--){
							if(board[k][j]==1) flag = true;
						}
						if(flag){
							for(int k=i-1;board[k][j]!=1;k--){
								count++;
							}
						}
						flag = false;
					}
				}
				// →right
				if(i<=5){
					if(board[i+1][j]==-1){
						for(int k=i+2;k<=7&&board[k][j]!=0;k++){
							if(board[k][j]==1) flag = true;
						}
						if(flag){
							for(int k=i+1;board[k][j]!=1;k++){
								count++;
							}
						}
						flag = false;
					}
				}
				//↑upper
				if(j>=2){
					if(board[i][j-1]==-1){
						for(int k=j-2;k>=0&&board[i][k]!=0;k--){
							if(board[i][k]==1) flag = true;
						}
						if(flag){
							for(int k=j-1;board[i][k]!=1;k--){
								count++;
							}
						}
						flag = false;
					}
				}
				//↓lower
				if(j<=5){
					if(board[i][j+1]==-1){
						for(int k=j+2;k<=7&&board[i][k]!=0;k++){
							if(board[i][k]==1) flag = true;
						}
						if(flag){
							for(int k=j+1;board[i][k]!=1;k++){
								count++;
							}
						}
						flag = false;
					}
				}
				//←↑ upper left
				if(i>=2&&j>=2){
					if(board[i-1][j-1]==-1){
						for(int k=i-2,l=j-2;k>=0&&l>=0&&board[k][l]!=0;k--,l--){
							if(board[k][l]==1) flag = true;
						}
						if(flag){
							for(int k=i-1,l=j-1;board[k][l]!=1;k--,l--){
								count++;
							}
						}
						flag = false;
					}
				}
				// →↓lower right
				if(i<=5&&j<=5){
					if(board[i+1][j+1]==-1){
						for(int k=i+2,l=j+2;k<=7&&l<=7&&board[k][l]!=0;k++,l++){
							if(board[k][l]==1) flag = true;
						}
						if(flag){
							for(int k=i+1,l=j+1;board[k][l]!=1;k++,l++){
								count++;
							}
							flag = false;
						}
					}
				}
				// →↑upper right
				if(i<=5&&j>=2){
					if(board[i+1][j-1]==-1){
						for(int k=i+2,l=j-2;k<=7&&l>=0&&board[k][l]!=0;k++,l--){
							if(board[k][l]==1) flag = true;
						}
						if(flag){
							for(int k=i+1,l=j-1;board[k][l]!=1;k++,l--){
								count++;
							}
							flag = false;
						}
					}
				}
				// ←↓lower left
				if(i>=2&&j<=5){
					if(board[i-1][j+1]==-1){
						for(int k=i-2,l=j+2;k>=0&&l<=7&&board[k][l]!=0;k--,l++){
							if(board[k][l]==1) flag = true;
						}
						if(flag){
							for(int k=i-1,l=j+1;board[k][l]!=1;k--,l++){
								count++;
							}
							flag = false;
						}
					}
				}
				if(count>0){
					ArrayList<Integer> tmp = new ArrayList<Integer>();
					tmp.add(i);
					tmp.add(j);
					tmp.add(count);
					available_list.add(tmp);
				}
			}
		}
		if(turn==WHITE) {
			board = flip_color(board);
		}
		return available_list;
	}

	int[][] flip_stones(int[][] board,int x, int y, int turn){
		if(turn==WHITE){
			board = flip_color(board);
		}
		boolean flag = false;
		if(board[x][y]!=0) return board;
		board[x][y] = 1;
		// ←left
		if(x>=2){
			if(board[x-1][y]==-1){
				for(int k=x-2;k>=0&&board[k][y]!=0;k--){
					if(board[k][y]==1) flag = true;
				}
				if(flag){
					for(int k=x-1;board[k][y]!=1;k--){
						board[k][y] = 1;
					}
				}
				flag = false;
			}
		}
		// →right
		if(x<=5){
			if(board[x+1][y]==-1){
				for(int k=x+2;k<=7&&board[k][y]!=0;k++){
					if(board[k][y]==1) flag = true;
				}
				if(flag){
					for(int k=x+1;board[k][y]!=1;k++){
						board[k][y] = 1;
					}
				}
				flag = false;
			}
		}
		//↑upper
		if(y>=2){
			if(board[x][y-1]==-1){
				for(int k=y-2;k>=0&&board[x][k]!=0;k--){
					if(board[x][k]==1) flag = true;
				}
				if(flag){
					for(int k=y-1;board[x][k]!=1;k--){
						board[x][k] = 1;
					}
				}
				flag = false;
			}
		}
		//↓lower
		if(y<=5){
			if(board[x][y+1]==-1){
				for(int k=y+2;k<=7&&board[x][k]!=0;k++){
					if(board[x][k]==1) flag = true;
				}
				if(flag){
					for(int k=y+1;board[x][k]!=1;k++){
						board[x][k] = 1;
					}
				}
				flag = false;
			}
		}
		//←↑ upper left
		if(x>=2&&y>=2){
			if(board[x-1][y-1]==-1){
				for(int k=x-2,l=y-2;k>=0&&l>=0&&board[k][l]!=0;k--,l--){
					if(board[k][l]==1) flag = true;
				}
				if(flag){
					for(int k=x-1,l=y-1;board[k][l]!=1;k--,l--){
						board[k][l] = 1;
					}
				}
				flag = false;
			}
		}
		// →↓lower right
		if(x<=5&&y<=5){
			if(board[x+1][y+1]==-1){
				for(int k=x+2,l=y+2;k<=7&&l<=7&&board[k][l]!=0;k++,l++){
					if(board[k][l]==1) flag = true;
				}
				if(flag){
					for(int k=x+1,l=y+1;board[k][l]!=1;k++,l++){
						board[k][l] = 1;
					}
					flag = false;
				}
			}
		}
		// →↑upper right
		if(x<=5&&y>=2){
			if(board[x+1][y-1]==-1){
				for(int k=x+2,l=y-2;k<=7&&l>=0&&board[k][l]!=0;k++,l--){
					if(board[k][l]==1) flag = true;
				}
				if(flag){
					for(int k=x+1,l=y-1;board[k][l]!=1;k++,l--){
						board[k][l] = 1;
					}
					flag = false;
				}
			}
		}
		// ←↓lower left
		if(x>=2&&y<=5){
			if(board[x-1][y+1]==-1){
				for(int k=x-2,l=y+2;k>=0&&l<=7&&board[k][l]!=0;k--,l++){
					if(board[k][l]==1) flag = true;
				}
				if(flag){
					for(int k=x-1,l=y+1;board[k][l]!=1;k--,l++){
						board[k][l] = 1;
					}
					flag = false;
				}
			}
		}
		if(turn==WHITE){
			board = flip_color(board);
		}
		return board;
	}

	int game_agent(int[][] board, int turn){
		int rest = 64;
		int pass = 0;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(board[i][j]!=0) rest--;
			}
		}

		while(rest>0&&pass<2){
			Random r = new Random();
			ArrayList<ArrayList<Integer>> available_list = available_check_and_count(board,turn);
			if(available_list.size()>0){
				int i = r.nextInt(available_list.size());
				board = flip_stones(board, available_list.get(i).get(0), available_list.get(i).get(1), turn);
				rest--;
				pass=0;
			} else {
				pass++;
			}
			turn = turn*(-1);
		}

		int black=0,white=0;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(board[i][j]==WHITE) white++;
				if(board[i][j]==BLACK) black++;
			}
		}
		// if(white+black<64) return 0;
		if(my_color==WHITE&&white>=black) return 1;
		if(my_color==BLACK&&black>=white) return 1;
		else return 0;
	}

	void show_board(int[][] board){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(board[j][i]==-1) System.out.print(board[j][i]);
				else System.out.print(" "+board[j][i]);
			}
			System.out.println("");
		}
		System.out.println("");
	}
}
