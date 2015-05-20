using System;
using System.Web;
using System.Net;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Facebook_Connection;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace Test {
	public partial class TestForm : Form {
		private FacebookChatClient client;

		public TestForm() {
			InitializeComponent();
			
			// start of bot:
			client = new FacebookChatClient();
			client.OnLoginResult = success =>
				{
					appendLog("connection is " + (success ? "" : "un") + "successful");
				};
			client.OnMessageReceived = (msg, user) =>
				{
					if (msg.Body != null)
					{
						appendLog(user.name + ":" + msg.Body);
						string[] words = msg.Body.Split(' ');
						switch (words[0])
						{
							case "wiki":
								client.SendMessage(get_wiki(words[1]), user.name);
								break;
							default:
								client.SendMessage("bocsi, nem tudtam értelmezni :(", user.name);
								break;
						}
					}
				};
			client.Login("", "");
			tbxInput.KeyPress += new KeyPressEventHandler(tbxInput_KeyPress);
		}

		private string get_wiki(string word)
		{
			WebClient wc = new WebClient();
			wc.Encoding = Encoding.UTF8;

			string source = wc.DownloadString("http://hu.m.wikipedia.org/wiki/" + Uri.EscapeUriString(word));
			int from = source.IndexOf("<div id=\"content\"");
			if (from == -1) return "nem találtam meg a keresett lapot";

			source = source.Substring(from);
			source = Regex.Replace(source, @"<[^\<]+>", string.Empty);
			source = Regex.Replace(source, @"[\r\n]+[\w \,\-]{1,40}[\r\n]", string.Empty);
			source = Regex.Replace(source, @"[ \t\n\r]{2,}", string.Empty);
			source = source.Substring(0, 500);
			source += "...";

			appendLog("Server says: " + source);
			/*
			int limit = 500;
			int to = source.IndexOf("<div id=\"toc");
			if (to == -1 || to > from + limit) to = from + limit;
			source = source.Substring(from, to - from);
			source = Regex.Replace(source, "<[^\\<]+>", string.Empty);
			source += "...";
			appendLog("Server says: " + source);
			*/
			return source;
		}

		void tbxInput_KeyPress(object sender, KeyPressEventArgs e) {
			if (e.KeyChar == '\r' && !string.IsNullOrEmpty(tbxInput.Text) && lbxContacts.SelectedItem != null) {
				client.SendMessage(tbxInput.Text, (string)lbxContacts.Items[lbxContacts.SelectedIndex]);
				appendLog("You to " + (string)lbxContacts.Items[lbxContacts.SelectedIndex] + ": " + tbxInput.Text);
				tbxInput.ResetText();
			}
		}
		private void btnConnect_Click(object sender, EventArgs e) {
			if (!string.IsNullOrEmpty(tbxNick.Text) && !string.IsNullOrEmpty(tbxNick.Text))
				client.Login(tbxNick.Text, tbxPass.Text);
		}
		private void changeContactList(string userName, bool add) {
			if (this.InvokeRequired)
				this.Invoke(new MethodInvoker(delegate { this.changeContactList(userName, add); }));
			else if (add)
				lbxContacts.Items.Add(userName);
			else if (!add)
				for (int i = 0; i <= lbxContacts.Items.Count; i++)
					if (lbxContacts.Items[i].ToString() == userName) {
						lbxContacts.Items.RemoveAt(i);
						break;
					}
		}
		private void appendLog(string msg) {
			if (this.InvokeRequired)
				this.Invoke(new MethodInvoker(delegate { this.appendLog(msg); }));
			else {
				tbxLog.AppendText(msg + Environment.NewLine);
				tbxLog.SelectionStart = tbxLog.Text.Length;
				tbxLog.ScrollToCaret();
			}
		}
	}
}