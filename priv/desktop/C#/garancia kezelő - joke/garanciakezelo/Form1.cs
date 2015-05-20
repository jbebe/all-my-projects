using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace garanciakezelo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void in_gari_bool_CheckedChanged(object sender, EventArgs e)
        {
            if (in_gari_bool.Checked)
            {
                in_gari_gyariszam.ReadOnly = false;
                in_gari_gjegyszam.ReadOnly = false;
                in_gari_szlaszam.ReadOnly = false;
                in_gari_vasarlasdatum.ReadOnly = false;
                in_javitas.Enabled = true;
                in_csere.Enabled = true;

            }
            if (in_gari_bool.Checked == false)
            {
                in_gari_gyariszam.ReadOnly = true;
                in_gari_gjegyszam.ReadOnly = true;
                in_gari_szlaszam.ReadOnly = true;
                in_gari_vasarlasdatum.ReadOnly = true;
                in_javitas.Enabled = false;
                in_csere.Enabled = false;
            }
        }

        private void in_submit_Click(object sender, EventArgs e)
        {
            string var_in_name = in_name.Text;
            string var_in_irsz = in_irsz.Text;
            DBConnect conn = new DBConnect();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            DialogResult result;
            result = MessageBox.Show("Confirm you wish to make the following change:\nCHANGE_RECOMPUTE_BASE_ENCRYPTION_KEY_HASH\nNote: This requires all authentication tokens based on this Hash Key to be reset. Which will probably take all fucking week. Have fun.", "Confirm Change", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
            if (result.ToString() == "OK")
            {
                Form f2 = new Form();
                System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
                f2.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
                f2.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
                f2.ClientSize = new System.Drawing.Size(375, 274);
                f2.ControlBox = false;
                f2.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
                f2.MaximizeBox = false;
                f2.MinimizeBox = false;
                f2.Name = "Form1";
                f2.Text = "Recomputing...";
                f2.UseWaitCursor = true;
                f2.Controls.Add(new System.Windows.Forms.Label()
                {
                    AutoSize = true,
                    Font = new System.Drawing.Font("Verdana", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238))),
                    Location = new System.Drawing.Point(90, 12),
                    Name = "label1",
                    Size = new System.Drawing.Size(257, 25),
                    Text = "Recomputing Hash..."
                });
                f2.Controls.Add(new System.Windows.Forms.Label()
                {
                    Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238))),
                    Location = new System.Drawing.Point(40, 165),
                    Name = "label2",
                    Size = new System.Drawing.Size(289, 61),
                    TabIndex = 2,
                    Text = "                  This may take forever.                   Do not interrupt the h" +
                        "ash recompute or you may be required to re-license all your products. Don\'t beli" +
                        "ve us? Try it.",
                    TextAlign = System.Drawing.ContentAlignment.TopCenter
                });
                f2.Controls.Add(new System.Windows.Forms.Button()
                {
                    Enabled = false,
                    Location = new System.Drawing.Point(150, 239),
                    Name = "button1",
                    Size = new System.Drawing.Size(75, 23),
                    TabIndex = 3,
                    Text = "Cancel",
                    UseVisualStyleBackColor = true
                });
                f2.Controls.Add(new System.Windows.Forms.PictureBox()
                {
                    Image = ((System.Drawing.Image)(resources.GetObject("alert"))),
                    Location = new System.Drawing.Point(8, 9),
                    Name = "pictureBox1",
                    Size = new System.Drawing.Size(33, 35),
                    UseWaitCursor = true
                });

                f2.Controls.Add(new System.Windows.Forms.PictureBox()
                {
                    Image = ((System.Drawing.Image)(resources.GetObject("loading"))),
                    Location = new System.Drawing.Point(100, 52),
                    Name = "pictureBox2",
                    Size = new System.Drawing.Size(194, 110),
                    TabIndex = 4,
                    TabStop = false,
                });
                f2.TopMost = true;
                f2.StartPosition = FormStartPosition.CenterScreen;
                f2.ShowDialog();
            }
        }
    }
}
