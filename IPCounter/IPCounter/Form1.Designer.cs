namespace IPCounter
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
			Microsoft.Win32.RegistryKey key = Microsoft.Win32.Registry.CurrentUser.CreateSubKey(@"SOFTWARE\AbstractSpoon\IPCounter");
			key.SetValue("MyIPAddress", m_MyIPAddress.Text);
			
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
			this.m_BrowseButton = new System.Windows.Forms.Button();
			this.m_LogFileList = new System.Windows.Forms.ListBox();
			this.button1 = new System.Windows.Forms.Button();
			this.m_ProgressList = new System.Windows.Forms.ListBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.m_ResultsList = new System.Windows.Forms.ListView();
			this.IPAddress = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.IPCount = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.IPPercent = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.label3 = new System.Windows.Forms.Label();
			this.m_MyIPAddress = new System.Windows.Forms.TextBox();
			this.m_HttpCodes = new System.Windows.Forms.CheckedListBox();
			this.label4 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.m_MinCount = new System.Windows.Forms.NumericUpDown();
			this.m_FromDate = new System.Windows.Forms.DateTimePicker();
			this.label6 = new System.Windows.Forms.Label();
			this.m_ToDate = new System.Windows.Forms.DateTimePicker();
			this.label7 = new System.Windows.Forms.Label();
			this.CopyAllAsCsv = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.m_MinCount)).BeginInit();
			this.SuspendLayout();
			// 
			// m_BrowseButton
			// 
			this.m_BrowseButton.AutoSize = true;
			this.m_BrowseButton.Location = new System.Drawing.Point(12, 63);
			this.m_BrowseButton.Name = "m_BrowseButton";
			this.m_BrowseButton.Size = new System.Drawing.Size(106, 23);
			this.m_BrowseButton.TabIndex = 1;
			this.m_BrowseButton.Text = "Browse Log Files...";
			this.m_BrowseButton.UseVisualStyleBackColor = true;
			this.m_BrowseButton.Click += new System.EventHandler(this.OnBrowseLogFiles);
			// 
			// m_LogFileList
			// 
			this.m_LogFileList.FormattingEnabled = true;
			this.m_LogFileList.HorizontalScrollbar = true;
			this.m_LogFileList.Location = new System.Drawing.Point(13, 93);
			this.m_LogFileList.Name = "m_LogFileList";
			this.m_LogFileList.Size = new System.Drawing.Size(285, 69);
			this.m_LogFileList.TabIndex = 2;
			// 
			// button1
			// 
			this.button1.AutoSize = true;
			this.button1.Location = new System.Drawing.Point(13, 325);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(99, 23);
			this.button1.TabIndex = 3;
			this.button1.Text = "Analyse Log Files";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.OnAnalyseLogFiles);
			// 
			// m_ProgressList
			// 
			this.m_ProgressList.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
			this.m_ProgressList.FormattingEnabled = true;
			this.m_ProgressList.HorizontalScrollbar = true;
			this.m_ProgressList.IntegralHeight = false;
			this.m_ProgressList.Location = new System.Drawing.Point(15, 369);
			this.m_ProgressList.Name = "m_ProgressList";
			this.m_ProgressList.Size = new System.Drawing.Size(283, 106);
			this.m_ProgressList.TabIndex = 2;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 354);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(48, 13);
			this.label1.TabIndex = 4;
			this.label1.Text = "Progress";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(309, 14);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(42, 13);
			this.label2.TabIndex = 4;
			this.label2.Text = "Results";
			// 
			// m_ResultsList
			// 
			this.m_ResultsList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.m_ResultsList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.IPAddress,
            this.IPCount,
            this.IPPercent});
			this.m_ResultsList.FullRowSelect = true;
			this.m_ResultsList.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
			this.m_ResultsList.Location = new System.Drawing.Point(312, 30);
			this.m_ResultsList.MultiSelect = false;
			this.m_ResultsList.Name = "m_ResultsList";
			this.m_ResultsList.Size = new System.Drawing.Size(267, 445);
			this.m_ResultsList.TabIndex = 5;
			this.m_ResultsList.UseCompatibleStateImageBehavior = false;
			this.m_ResultsList.View = System.Windows.Forms.View.Details;
			this.m_ResultsList.DoubleClick += new System.EventHandler(this.OnDoubleClickResult);
			// 
			// IPAddress
			// 
			this.IPAddress.Text = "IP Address";
			this.IPAddress.Width = 127;
			// 
			// IPCount
			// 
			this.IPCount.Text = "Count";
			this.IPCount.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.IPCount.Width = 61;
			// 
			// IPPercent
			// 
			this.IPPercent.Text = "%";
			this.IPPercent.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.IPPercent.Width = 36;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(9, 14);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(121, 13);
			this.label3.TabIndex = 6;
			this.label3.Text = "My IP Address (optional)";
			// 
			// m_MyIPAddress
			// 
			this.m_MyIPAddress.Location = new System.Drawing.Point(13, 30);
			this.m_MyIPAddress.Name = "m_MyIPAddress";
			this.m_MyIPAddress.Size = new System.Drawing.Size(285, 20);
			this.m_MyIPAddress.TabIndex = 7;
			// 
			// m_HttpCodes
			// 
			this.m_HttpCodes.CheckOnClick = true;
			this.m_HttpCodes.FormattingEnabled = true;
			this.m_HttpCodes.Items.AddRange(new object[] {
            "100-199",
            "200-299",
            "300-399",
            "400-499",
            "500-599"});
			this.m_HttpCodes.Location = new System.Drawing.Point(149, 177);
			this.m_HttpCodes.Name = "m_HttpCodes";
			this.m_HttpCodes.Size = new System.Drawing.Size(149, 79);
			this.m_HttpCodes.TabIndex = 11;
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(12, 177);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(131, 13);
			this.label4.TabIndex = 10;
			this.label4.Text = "Count these HTTP codes:";
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(12, 300);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(112, 13);
			this.label5.TabIndex = 12;
			this.label5.Text = "Omit \'counts\' less than";
			// 
			// m_MinCount
			// 
			this.m_MinCount.Location = new System.Drawing.Point(149, 298);
			this.m_MinCount.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
			this.m_MinCount.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.m_MinCount.Name = "m_MinCount";
			this.m_MinCount.Size = new System.Drawing.Size(86, 20);
			this.m_MinCount.TabIndex = 13;
			this.m_MinCount.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
			this.m_MinCount.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.OnMinCountKeyPress);
			// 
			// m_FromDate
			// 
			this.m_FromDate.Checked = false;
			this.m_FromDate.Format = System.Windows.Forms.DateTimePickerFormat.Short;
			this.m_FromDate.Location = new System.Drawing.Point(46, 267);
			this.m_FromDate.Name = "m_FromDate";
			this.m_FromDate.ShowCheckBox = true;
			this.m_FromDate.Size = new System.Drawing.Size(97, 20);
			this.m_FromDate.TabIndex = 14;
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(10, 270);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(30, 13);
			this.label6.TabIndex = 15;
			this.label6.Text = "From";
			// 
			// m_ToDate
			// 
			this.m_ToDate.Checked = false;
			this.m_ToDate.Format = System.Windows.Forms.DateTimePickerFormat.Short;
			this.m_ToDate.Location = new System.Drawing.Point(197, 267);
			this.m_ToDate.Name = "m_ToDate";
			this.m_ToDate.ShowCheckBox = true;
			this.m_ToDate.Size = new System.Drawing.Size(101, 20);
			this.m_ToDate.TabIndex = 14;
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(171, 270);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(20, 13);
			this.label7.TabIndex = 15;
			this.label7.Text = "To";
			// 
			// CopyAllAsCsv
			// 
			this.CopyAllAsCsv.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.CopyAllAsCsv.AutoSize = true;
			this.CopyAllAsCsv.Location = new System.Drawing.Point(486, 1);
			this.CopyAllAsCsv.Name = "CopyAllAsCsv";
			this.CopyAllAsCsv.Size = new System.Drawing.Size(93, 23);
			this.CopyAllAsCsv.TabIndex = 16;
			this.CopyAllAsCsv.Text = "Copy All as CSV";
			this.CopyAllAsCsv.UseVisualStyleBackColor = true;
			this.CopyAllAsCsv.Click += new System.EventHandler(this.OnCopyAllAsCsv);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(591, 487);
			this.Controls.Add(this.CopyAllAsCsv);
			this.Controls.Add(this.label7);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.m_ToDate);
			this.Controls.Add(this.m_FromDate);
			this.Controls.Add(this.m_MinCount);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.m_HttpCodes);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.m_MyIPAddress);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.m_ResultsList);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.m_ProgressList);
			this.Controls.Add(this.m_LogFileList);
			this.Controls.Add(this.m_BrowseButton);
			this.MinimumSize = new System.Drawing.Size(600, 430);
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "IP Address Counter";
			((System.ComponentModel.ISupportInitialize)(this.m_MinCount)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion
		private System.Windows.Forms.Button m_BrowseButton;
		private System.Windows.Forms.ListBox m_LogFileList;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.ListBox m_ProgressList;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.ListView m_ResultsList;
		private System.Windows.Forms.ColumnHeader IPAddress;
		private System.Windows.Forms.ColumnHeader IPCount;
		private System.Windows.Forms.ColumnHeader IPPercent;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox m_MyIPAddress;
		private System.Windows.Forms.CheckedListBox m_HttpCodes;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.NumericUpDown m_MinCount;
		private System.Windows.Forms.DateTimePicker m_FromDate;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.DateTimePicker m_ToDate;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Button CopyAllAsCsv;
	}
}

