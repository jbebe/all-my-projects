import System;
import System.Collections.Generic;
import System.Windows.Forms;
import System.Runtime.InteropServices;
import System.Drawing;
import System.ComponentModel;
import Accessibility;

package JScript_Form {
	class Form1 extends Form {
		private var components: IContainer;
		private var textBox1: TextBox;
		private var label1: Label;
		private var button1: Button;
		private var label2: Label;
		public function Form1()
		{
			components = null;
			
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.button1 = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
			this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.textBox1.ForeColor = System.Drawing.Color.White;
			this.textBox1.Location = new System.Drawing.Point(12, 28);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(212, 13);
			this.textBox1.TabIndex = 0;
			this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.ForeColor = System.Drawing.Color.Lime;
			this.label1.Location = new System.Drawing.Point(99, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(45, 13);
			this.label1.TabIndex = 1;
			this.label1.Text = "KeyGen";
			// 
			// button1
			// 
			this.button1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
			this.button1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
			this.button1.FlatAppearance.BorderSize = 0;
			this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.button1.ForeColor = System.Drawing.Color.Lime;
			this.button1.Location = new System.Drawing.Point(149, 54);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 2;
			this.button1.Text = "Generate";
			this.button1.UseVisualStyleBackColor = false;
			//this.button1.Click += new System.EventHandler(this.button1_Click);
			this.button1.add_Click(this.button1_Click);  
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.ForeColor = System.Drawing.Color.Lime;
			this.label2.Location = new System.Drawing.Point(216, 2);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(20, 13);
			this.label2.TabIndex = 3;
			this.label2.Text = "[X]";
			//this.label2.Click += new System.EventHandler(this.label2_Click);
			this.label2.add_Click(this.label2_Click);
			// 
			// Form1
			// 
			//this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.Color.Black;
			this.ClientSize = new System.Drawing.Size(236, 84);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.textBox1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.Name = "Form1";
			this.Text = "Form1";
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private function button1_Click(sender: Object, e: EventArgs)
		{
			var serial: String = "";
			var letters: char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789".ToCharArray();
			var r: Random = new Random();
			for (var i = 0; i < 5; i++)
			{
				for (var j = 0; j < 4; j++)
				{
					serial += letters[r.Next(0, letters.Length - 1)];
				}
				if (i != 5 - 1) serial += '-';
			}
			textBox1.Text = serial;
		}
		private function label2_Click(sender: Object, e: EventArgs) { Application.Exit(); }
	}
}
/*
Application.EnableVisualStyles();
Application.SetCompatibleTextRenderingDefault(false);
*/
Application.Run(new JScript_Form.Form1());