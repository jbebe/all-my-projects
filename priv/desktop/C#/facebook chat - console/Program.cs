using System;
using System.Collections.Generic;
using System.Threading;
using Facebook_Connection;

namespace consoleChat {
	class Program {
		static byte WIDTH = 80;
		static byte HEIGHT_LOGIN = 25;
		static byte HEIGHT_CHAT = 35;

		static FacebookChatClient client;
		static List<FacebookUser> friends = new List<FacebookUser>();

		static bool whileLoop = true;

		static void Main() {
			client = new FacebookChatClient();
			client.OnLoginResult = (a) => whileLoop = false;
			client.OnUserAdded = user => {
				friends.Add(user);
				// csak akkor, ha entert ütöttél, különben bug lenne!!
				//updateContactList();
			};
			client.OnMessageReceived = (msg, user) => newMessage(msg,user);
			setupConsole();
			drawLogin();
		}

		static void setupConsole(){
			Console.SetBufferSize(WIDTH,HEIGHT_LOGIN);
			Console.SetWindowSize(WIDTH,HEIGHT_LOGIN);
			Console.Title = "Facebook Chat / Login";
		}

		static void drawLogin(){
			byte pos_x = 3,
				pos_y = 3,
				width = 20,
				height = (byte)(width*(2/3.0));
			Console.BackgroundColor = ConsoleColor.Gray;
			Console.ForegroundColor = ConsoleColor.White;
			Console.Clear();

			//fehér rész
			drawRectangle(26, HEIGHT_LOGIN, 0, 0, ConsoleColor.White, " ");
			// ikon
			drawRectangle(width, height, pos_x, pos_y, ConsoleColor.DarkBlue, " ");
			// árnyékok
			drawRectangle(1, 1, pos_x, pos_y, ConsoleColor.Blue, " ");
			drawRectangle(1, 1, pos_x+width-1, pos_y, ConsoleColor.Blue, " ");
			drawRectangle(1, 1, pos_x, pos_y+height-1, ConsoleColor.Blue, " ");
			drawRectangle(1, 1, pos_x+width-1, pos_y+height-1, ConsoleColor.Blue, " ");
			drawRectangle(width-2,2,pos_x+1,pos_y+height-3,ConsoleColor.Blue," ");
			// F
			drawRectangle(2,height-3,pos_x+(byte)(width/2.0),pos_y+2,ConsoleColor.White," ");
			drawRectangle(5, 2, pos_x + (byte)(width / 2.0), pos_y + 2, ConsoleColor.White, " ");
			drawRectangle(7, 2, pos_x + (byte)(width / 2.0)-2, pos_y + 6, ConsoleColor.White, " ");
			// árnyékok
			drawRectangle(1, 1, pos_x + (byte)(width / 2.0), pos_y + 2, ConsoleColor.Blue, " ");

			// Feliratok:
			Console.BackgroundColor = ConsoleColor.White;
			Console.ForegroundColor = ConsoleColor.DarkGray;
			Console.SetCursorPosition(7, 18);
			Console.Write("Facebook Chat");
			Console.SetCursorPosition(8, 19);
			Console.Write("for Windows");
			Console.SetCursorPosition(2, 21);
			Console.Write("______________________");
			Console.SetCursorPosition(7,23);
			Console.Write("made by bebe");

			// Input:
			Console.SetCursorPosition(33,4);
			Console.ForegroundColor = ConsoleColor.Black;
			Console.BackgroundColor = ConsoleColor.Gray;
			Console.Write("Facebook ID: (eg. john.smith.85)");
			drawRectangle(40,3,32,6,ConsoleColor.White," ");

			Console.SetCursorPosition(33, 4+7);
			Console.ForegroundColor = ConsoleColor.Black;
			Console.BackgroundColor = ConsoleColor.Gray;
			Console.Write("Password: (your facebook password)");
			drawRectangle(40, 3, 32, 6+7, ConsoleColor.White, " ");

			Console.ForegroundColor = ConsoleColor.Black;
			Console.BackgroundColor = ConsoleColor.White;
			Console.SetCursorPosition(45, 6 + 7 + 5);
			Console.Write("               ");
			Console.SetCursorPosition(45, 6 + 7 + 5 + 1);
			Console.Write("     Login     ");
			Console.SetCursorPosition(45, 6 + 7 + 5 + 2);
			Console.Write("               ");

			inputLogin();
		}

		static void inputLogin(){
			string	fbID = "",
					password = "";
	replay:
			Console.ForegroundColor = ConsoleColor.Black;
			Console.BackgroundColor = ConsoleColor.White;
			Console.SetCursorPosition(45, 6 + 7 + 5);
			Console.Write("               ");
			Console.SetCursorPosition(45, 6 + 7 + 5 + 1);
			Console.Write("     Login     ");
			Console.SetCursorPosition(45, 6 + 7 + 5 + 2);
			Console.Write("               ");
			Console.CursorVisible = true;
			Console.SetCursorPosition(33, 7);
			fbID = Console.ReadLine();
			Console.SetCursorPosition(33, 7 + 7);
			password = Console.ReadLine();

			Console.CursorVisible = false;
			Console.SetCursorPosition(45, 6 + 7 + 5);
			Console.Write("█▀▀▀▀▀▀▀▀▀▀▀▀▀█");
			Console.SetCursorPosition(45, 6 + 7 + 5 + 1);
			Console.Write("█    Login    █");
			Console.SetCursorPosition(45, 6 + 7 + 5 + 2);
			Console.Write("█▄▄▄▄▄▄▄▄▄▄▄▄▄█");

			if (Console.ReadKey().Key == ConsoleKey.Enter){
				if (!string.IsNullOrEmpty(fbID) && !string.IsNullOrEmpty(password)){
					Thread t = new Thread(new ThreadStart(loginAnimation));
					t.Start();
					client.Login(fbID, password);
				}
				else goto replay;
			}
			else goto replay;
		}

		private static void loginAnimation() {
			int offset = 0;
			bool isDirBack = false;
			string spaces = ""; for (int i = 0; i < 50; i++) spaces += " ";
			string bar = "█ █ █";

			drawRectangle(40, 17, 32, 4, ConsoleColor.Gray, " ");

			Console.SetCursorPosition(48, 15);
			Console.Write("Logging in...");

			drawRectangle(40, 3, 34, 8, ConsoleColor.White, " ");

			while (whileLoop) {
				Console.SetCursorPosition(35, 9);
				Console.Write(spaces.Substring(0, offset));
				Console.Write(bar);
				Console.Write(spaces.Substring(0, 38 - offset - bar.Length));
				if (isDirBack) offset--;
				else offset++;
				if (offset > 38 - bar.Length - 1 || offset < 1) {
					isDirBack = !isDirBack;
				}
				System.Threading.Thread.Sleep(50);
			}
			drawChat();
		}

		static void drawChat(){
			Console.SetBufferSize(WIDTH,HEIGHT_CHAT);
			Console.SetWindowSize(WIDTH,HEIGHT_CHAT);
			Console.ForegroundColor = ConsoleColor.Gray;
			Console.BackgroundColor = ConsoleColor.White;
			Console.Clear();
			// edge 
			drawRectangle(1, HEIGHT_CHAT - 9, 57, 4, ConsoleColor.White, "│");
			// text input
			drawRectangle(56, 1, 1, HEIGHT_CHAT - 5, ConsoleColor.White, "─");
			Console.Write("┘");
			// blue bar
			drawRectangle(WIDTH, 3, 0, 0, ConsoleColor.DarkBlue, " ");
			// info bar 
			drawRectangle(40, 2, 3, 1, ConsoleColor.White, " ");
			Console.SetCursorPosition(4,2);
			Console.ForegroundColor = ConsoleColor.Green;
			Console.Write("▀");
			Console.ForegroundColor = ConsoleColor.Black;
			Console.Write(" Gyurácz Kristóf - typing...");

			// update client information
			Console.Title = "Facebook Chat / Chat";

			startChat();
		}

		static void updateContactList(){
			Console.BackgroundColor = ConsoleColor.White;
			Console.ForegroundColor = ConsoleColor.DarkGray;
			for (int i = 0; i < (friends.ToArray().Length > 12 ? 12 : friends.ToArray().Length); i++) {
				Console.SetCursorPosition(59,4+2*i);
				Console.Write(("F" + (i + 1) + "").PadRight(4) + friends[i].name.Substring(0, (friends[i].name.Length > 16 ? 16 : friends[i].name.Length)));
			}
		}

		static void startChat(){
			string message = "";
			Console.CursorVisible = true;
			do {
				Console.ForegroundColor = ConsoleColor.DarkGray;
				Console.SetCursorPosition(2,HEIGHT_CHAT-3);
				message = Console.ReadLine();
				drawRectangle(WIDTH,2,0,HEIGHT_CHAT-3,ConsoleColor.White," ");
				Console.SetCursorPosition(3, 5);
				Console.Write("You: " + message);
				updateContactList();
			} while (true);
		}

		static void newMessage(agsXMPP.protocol.client.Message message, FacebookUser user){
			friends[friends.IndexOf(user)].messages.Add(message.Body);
		}

		static void sendMessage(string message) {
			if (!string.IsNullOrEmpty(message) /* && van kijelölt barát */ ) {
				//client.SendMessage(message, receiversname);
			}
		}

		static void drawRectangle(int width, int height, int pos_x, int pos_y, ConsoleColor color, string ch) {
			Console.BackgroundColor = color;
			for (byte h = 0; h < height; h++){
				for (byte w = 0; w < width; w++){
					if (Console.CursorLeft == WIDTH - 1 && Console.CursorTop == HEIGHT_LOGIN - 1) break;
					Console.SetCursorPosition(pos_x + w, pos_y + h);
					Console.Write(ch);
				}
			}
		}

	}
}
