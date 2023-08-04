namespace DLLTester
{
    partial class Form
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
            this.mandelfashPicture = new System.Windows.Forms.PictureBox();
            this.execute = new System.Windows.Forms.Button();
            this.counterBox = new System.Windows.Forms.TextBox();
            this.startBox = new System.Windows.Forms.TextBox();
            this.endBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.deactivateBlackBypass = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.loopLimitBox = new System.Windows.Forms.TextBox();
            this.deactivateMultithreading = new System.Windows.Forms.CheckBox();
            this.benchmarking = new System.Windows.Forms.CheckBox();
            this.blackLoop = new System.Windows.Forms.CheckBox();
            this.invertRGB = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.mandelfashPicture)).BeginInit();
            this.SuspendLayout();
            // 
            // mandelfashPicture
            // 
            this.mandelfashPicture.Location = new System.Drawing.Point(12, 12);
            this.mandelfashPicture.Name = "mandelfashPicture";
            this.mandelfashPicture.Size = new System.Drawing.Size(1000, 1000);
            this.mandelfashPicture.TabIndex = 0;
            this.mandelfashPicture.TabStop = false;
            // 
            // execute
            // 
            this.execute.Location = new System.Drawing.Point(1051, 319);
            this.execute.Name = "execute";
            this.execute.Size = new System.Drawing.Size(75, 23);
            this.execute.TabIndex = 1;
            this.execute.Text = "Execute";
            this.execute.UseVisualStyleBackColor = true;
            this.execute.Click += new System.EventHandler(this.execute_Click);
            // 
            // counterBox
            // 
            this.counterBox.Location = new System.Drawing.Point(1051, 28);
            this.counterBox.Name = "counterBox";
            this.counterBox.ReadOnly = true;
            this.counterBox.Size = new System.Drawing.Size(162, 20);
            this.counterBox.TabIndex = 2;
            // 
            // startBox
            // 
            this.startBox.Location = new System.Drawing.Point(1051, 78);
            this.startBox.Name = "startBox";
            this.startBox.ReadOnly = true;
            this.startBox.Size = new System.Drawing.Size(162, 20);
            this.startBox.TabIndex = 3;
            // 
            // endBox
            // 
            this.endBox.Location = new System.Drawing.Point(1051, 127);
            this.endBox.Name = "endBox";
            this.endBox.ReadOnly = true;
            this.endBox.Size = new System.Drawing.Size(162, 20);
            this.endBox.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1051, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Counter";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(1051, 62);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(52, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "StartTime";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(1048, 111);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Elapsed Time";
            // 
            // deactivateBlackBypass
            // 
            this.deactivateBlackBypass.AutoSize = true;
            this.deactivateBlackBypass.Location = new System.Drawing.Point(1051, 204);
            this.deactivateBlackBypass.Name = "deactivateBlackBypass";
            this.deactivateBlackBypass.Size = new System.Drawing.Size(145, 17);
            this.deactivateBlackBypass.TabIndex = 8;
            this.deactivateBlackBypass.Text = "Deactivate Black Bypass";
            this.deactivateBlackBypass.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(1048, 162);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(93, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Custom Loop Limit";
            // 
            // loopLimitBox
            // 
            this.loopLimitBox.Location = new System.Drawing.Point(1051, 178);
            this.loopLimitBox.Name = "loopLimitBox";
            this.loopLimitBox.Size = new System.Drawing.Size(162, 20);
            this.loopLimitBox.TabIndex = 9;
            // 
            // deactivateMultithreading
            // 
            this.deactivateMultithreading.AutoSize = true;
            this.deactivateMultithreading.Location = new System.Drawing.Point(1051, 227);
            this.deactivateMultithreading.Name = "deactivateMultithreading";
            this.deactivateMultithreading.Size = new System.Drawing.Size(147, 17);
            this.deactivateMultithreading.TabIndex = 11;
            this.deactivateMultithreading.Text = "Deactivate Multithreading";
            this.deactivateMultithreading.UseVisualStyleBackColor = true;
            // 
            // benchmarking
            // 
            this.benchmarking.AutoSize = true;
            this.benchmarking.Location = new System.Drawing.Point(1051, 250);
            this.benchmarking.Name = "benchmarking";
            this.benchmarking.Size = new System.Drawing.Size(170, 17);
            this.benchmarking.TabIndex = 12;
            this.benchmarking.Text = "Activate Benchmarking on File";
            this.benchmarking.UseVisualStyleBackColor = true;
            // 
            // blackLoop
            // 
            this.blackLoop.AutoSize = true;
            this.blackLoop.Location = new System.Drawing.Point(1051, 273);
            this.blackLoop.Name = "blackLoop";
            this.blackLoop.Size = new System.Drawing.Size(122, 17);
            this.blackLoop.TabIndex = 13;
            this.blackLoop.Text = "Activate Black Loop";
            this.blackLoop.UseVisualStyleBackColor = true;
            // 
            // invertRGB
            // 
            this.invertRGB.AutoSize = true;
            this.invertRGB.Location = new System.Drawing.Point(1051, 296);
            this.invertRGB.Name = "invertRGB";
            this.invertRGB.Size = new System.Drawing.Size(121, 17);
            this.invertRGB.TabIndex = 14;
            this.invertRGB.Text = "Invert Red and Blue";
            this.invertRGB.UseVisualStyleBackColor = true;
            // 
            // Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1225, 900);
            this.Controls.Add(this.invertRGB);
            this.Controls.Add(this.blackLoop);
            this.Controls.Add(this.benchmarking);
            this.Controls.Add(this.deactivateMultithreading);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.loopLimitBox);
            this.Controls.Add(this.deactivateBlackBypass);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.endBox);
            this.Controls.Add(this.startBox);
            this.Controls.Add(this.counterBox);
            this.Controls.Add(this.execute);
            this.Controls.Add(this.mandelfashPicture);
            this.Name = "Form";
            this.Text = "Mandelfash DLL Tester";
            ((System.ComponentModel.ISupportInitialize)(this.mandelfashPicture)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox mandelfashPicture;
        private System.Windows.Forms.Button execute;
        private System.Windows.Forms.TextBox counterBox;
        private System.Windows.Forms.TextBox startBox;
        private System.Windows.Forms.TextBox endBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox deactivateBlackBypass;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox loopLimitBox;
        private System.Windows.Forms.CheckBox deactivateMultithreading;
        private System.Windows.Forms.CheckBox benchmarking;
        private System.Windows.Forms.CheckBox blackLoop;
        private System.Windows.Forms.CheckBox invertRGB;
    }
}

