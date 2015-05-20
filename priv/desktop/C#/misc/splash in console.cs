using System;
using System.Linq;
class Screensaver {
	public byte WIDTH = 80, HEIGHT = 40;
	private byte pos_x, pos_y;
	private Random rnd = new Random();
	private ConsoleColor[] colors = Enum.GetValues(typeof(ConsoleColor)).Cast<ConsoleColor>().ToArray();
	private void move(byte offset) {
		if (offset==0) pos_y++;
		else if (offset==1) pos_y--;
		else if (offset==2) pos_x++;
		else pos_x--;
    }
	public void loop(){
		while (true) {
			move((byte)rnd.Next(0, 4));
			if (pos_x == 255 || pos_x == WIDTH || pos_y == 255 || pos_y == HEIGHT) {
				pos_x = (byte)(WIDTH / 2);
				pos_y = (byte)(HEIGHT / 2);
				Console.BackgroundColor = colors[rnd.Next(1, colors.Length - 1)];
			}
			Console.SetCursorPosition(pos_x, pos_y);
			Console.Write(" ");
		}
	}
	public Screensaver() {
		Console.BackgroundColor = colors[0];
		Console.BufferHeight = HEIGHT;
		Console.BufferWidth = WIDTH;
		Console.ForegroundColor = colors[colors.Length-2];
		Console.SetWindowSize(WIDTH, HEIGHT);
		Console.Title = "Pipes";
		Console.CursorVisible = false;
	}
}
class Program {
    static void Main() {
		Screensaver scr = new Screensaver();
		scr.loop();
    }
}