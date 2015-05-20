using MouseKeyboardActivityMonitor;
using MouseKeyboardActivityMonitor.WinApi;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace KeyboardLock
{
	public partial class Form1 : Form
	{
		static private bool ON = true;
		static private bool OFF = false;
		private bool button1_state;

		private readonly KeyboardHookListener KeyboardHookManager;

		public Form1()
		{
			InitializeComponent();
			KeyboardHookManager = new KeyboardHookListener(new GlobalHooker());
			KeyboardHookManager.Enabled = true;
			button1_state = OFF;
		}

		private void button1_MouseClick(object sender, MouseEventArgs e)
		{
			if (button1_state == OFF)
			{
				button1.Text = "Disabled";
				button1_state = ON;
				button1.BackColor = Color.DarkSalmon;

				KeyboardHookManager.KeyDown	+= hookSuppressUpDown;
				KeyboardHookManager.KeyUp	+= hookSuppressUpDown;
				KeyboardHookManager.KeyPress+= hookSuppressPress;
			}
			else
			{
				button1.Text = "Enabled";
				button1_state = OFF;
				button1.BackColor = Color.Gainsboro;
				
				KeyboardHookManager.KeyDown	-= hookSuppressUpDown;
				KeyboardHookManager.KeyUp	-= hookSuppressUpDown;
				KeyboardHookManager.KeyPress-= hookSuppressPress;
			}
		}

		private void hookSuppressPress(object sender, KeyPressEventArgs e)
		{
			e.Handled = true;
		}

		private void hookSuppressUpDown(object sender, KeyEventArgs e)
		{
			e.Handled = true;
		}
	}
}
