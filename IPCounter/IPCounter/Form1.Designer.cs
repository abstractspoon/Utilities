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
			this.SuspendLayout();
			// 
			// m_BrowseButton
			// 
			this.m_BrowseButton.AutoSize = true;
			this.m_BrowseButton.Location = new System.Drawing.Point(18, 18);
			this.m_BrowseButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.m_BrowseButton.Name = "m_BrowseButton";
			this.m_BrowseButton.Size = new System.Drawing.Size(159, 35);
			this.m_BrowseButton.TabIndex = 1;
			this.m_BrowseButton.Text = "Browse Log Files...";
			this.m_BrowseButton.UseVisualStyleBackColor = true;
			this.m_BrowseButton.Click += new System.EventHandler(this.OnBrowseLogFiles);
			// 
			// m_LogFileList
			// 
			this.m_LogFileList.FormattingEnabled = true;
			this.m_LogFileList.ItemHeight = 20;
			this.m_LogFileList.Location = new System.Drawing.Point(20, 65);
			this.m_LogFileList.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.m_LogFileList.Name = "m_LogFileList";
			this.m_LogFileList.Size = new System.Drawing.Size(426, 104);
			this.m_LogFileList.TabIndex = 2;
			// 
			// button1
			// 
			this.button1.AutoSize = true;
			this.button1.Location = new System.Drawing.Point(20, 200);
			this.button1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(148, 35);
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
			this.m_ProgressList.ItemHeight = 20;
			this.m_ProgressList.Location = new System.Drawing.Point(18, 277);
			this.m_ProgressList.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.m_ProgressList.Name = "m_ProgressList";
			this.m_ProgressList.Size = new System.Drawing.Size(427, 184);
			this.m_ProgressList.TabIndex = 2;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(15, 252);
			this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(72, 20);
			this.label1.TabIndex = 4;
			this.label1.Text = "Progress";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(464, 40);
			this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(63, 20);
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
			this.m_ResultsList.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
			this.m_ResultsList.Location = new System.Drawing.Point(468, 65);
			this.m_ResultsList.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.m_ResultsList.Name = "m_ResultsList";
			this.m_ResultsList.Size = new System.Drawing.Size(398, 396);
			this.m_ResultsList.TabIndex = 5;
			this.m_ResultsList.UseCompatibleStateImageBehavior = false;
			this.m_ResultsList.View = System.Windows.Forms.View.Details;
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
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(886, 478);
			this.Controls.Add(this.m_ResultsList);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.m_ProgressList);
			this.Controls.Add(this.m_LogFileList);
			this.Controls.Add(this.m_BrowseButton);
			this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "IP Address Counter";
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
	}
}

