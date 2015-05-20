using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;
using System.Windows.Threading;
using System.IO;
using System.Diagnostics;
using Facebook_Connection;

namespace musicPlayer {
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {

		System.Timers.Timer timer = new System.Timers.Timer(1000);
		public delegate void Action();
		Regex regexObj = new Regex(@"\<\/?title\>|\t");
		private PerformanceCounter theCPUCounter = new PerformanceCounter("Processor", "% Processor Time", "_Total");
		string cpuperc;
		private FacebookChatClient client;
		List<string> facebook_names = new List<string>();
		string[] facebook_data = new string[2];

		public MainWindow() {
			InitializeComponent();

			client = new FacebookChatClient();

			client.OnUserAdded = user => {
				facebook_names.Add(user.first_name);
				this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() => {
					wdgFB.Text = string.Join(", ", facebook_names.ToArray());
				}));
			};
			client.OnUserRemoved = user => {
				facebook_names.RemoveAt(facebook_names.IndexOf(user.first_name));
				this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() => {
					wdgFB.Text = string.Join(", ", facebook_names.ToArray());
				}));
			};
			client.Login("", "");

			var scrWidth = System.Windows.SystemParameters.PrimaryScreenWidth;
			var scrHeight = System.Windows.SystemParameters.PrimaryScreenHeight;
			var wndHeight = 20.0;

			Width = scrWidth;
			Background = new SolidColorBrush(Colors.Black);
			Height = wndHeight;

			Top = scrHeight - wndHeight;
			Left = 0;

			wdgTime.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
			wdgTime.Text = DateTime.Now.ToString("yyyy/MM/dd  [ HH:mm:ss ]");

			timer.Elapsed += new System.Timers.ElapsedEventHandler(timer_Elapsed);
			timer.Enabled = true;
		}

		void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e) {
			this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() => {
				cpuperc = ((int)theCPUCounter.NextValue()).ToString();
				try {
					string[] xml_rows = File.ReadAllLines(@"C:\Program Files (x86)\Windows Media Player\plugins\Now Playing\now_playing.xml", Encoding.UTF8);
					wdgTime.Text = "► " + regexObj.Replace(xml_rows[3], "") + " | " + "CPU: " + cpuperc.PadLeft(2, ' ') + "% | " + DateTime.Now.ToString("yyyy/MM/dd [ HH:mm:ss ]");
				}
				catch {
					wdgTime.Text = "CPU: " + cpuperc.PadLeft(2, ' ') + "% | " + DateTime.Now.ToString("yyyy/MM/dd [ HH:mm:ss ]");
				}
			}));
		}

		private void Window_Loaded_1(object sender, RoutedEventArgs e) {

		}
	}
}
