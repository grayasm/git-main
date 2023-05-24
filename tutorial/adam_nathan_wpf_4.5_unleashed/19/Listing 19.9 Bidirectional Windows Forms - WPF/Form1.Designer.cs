namespace WindowsFormsHostingWPF
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.elementHost = new System.Windows.Forms.Integration.ElementHost();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // elementHost
            // 
            this.elementHost.BackColor = System.Drawing.Color.Yellow;
            this.elementHost.BackColorTransparent = false;
            this.elementHost.Child = null;
            this.elementHost.Dock = System.Windows.Forms.DockStyle.Left;
            this.elementHost.Location = new System.Drawing.Point(0, 0);
            this.elementHost.Name = "elementHost";
            this.elementHost.Size = new System.Drawing.Size(230, 383);
            this.elementHost.TabIndex = 0;
            this.elementHost.TabStop = false;
            this.elementHost.Text = "elementHost1";
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(241, 77);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(273, 146);
            this.label1.TabIndex = 1;
            this.label1.Text = "The WPF Expander is docked to the left.";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(522, 383);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.elementHost);
            this.Name = "Form1";
            this.Text = "Hosting a WPF Expander in Windows Forms";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Integration.ElementHost elementHost;
        private System.Windows.Forms.Label label1;
    }
}

