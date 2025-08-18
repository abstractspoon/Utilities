namespace BranchDepends
{
	partial class BranchDependsForm
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
			this.m_RepoLabel = new System.Windows.Forms.Label();
			this.m_Repositories = new System.Windows.Forms.ComboBox();
			this.m_BrowseRepo = new System.Windows.Forms.Button();
			this.m_BranchLabel = new System.Windows.Forms.Label();
			this.m_Branches = new System.Windows.Forms.ComboBox();
			this.m_ChangedFiles = new System.Windows.Forms.CheckedListBox();
			this.m_ChangedFilesLabel = new System.Windows.Forms.Label();
			this.m_AffectedFiles = new System.Windows.Forms.ListView();
			this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.m_AffectedFilesLabel = new System.Windows.Forms.Label();
			this.m_AnalyseChanges = new System.Windows.Forms.Button();
			this.m_SourceFolderLabel = new System.Windows.Forms.Label();
			this.m_SourceFolders = new System.Windows.Forms.ComboBox();
			this.m_RefreshChangeFiles = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// m_RepoLabel
			// 
			this.m_RepoLabel.AutoSize = true;
			this.m_RepoLabel.Location = new System.Drawing.Point(13, 15);
			this.m_RepoLabel.Name = "m_RepoLabel";
			this.m_RepoLabel.Size = new System.Drawing.Size(57, 13);
			this.m_RepoLabel.TabIndex = 0;
			this.m_RepoLabel.Text = "Repository";
			// 
			// m_Repositories
			// 
			this.m_Repositories.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.m_Repositories.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.m_Repositories.FormattingEnabled = true;
			this.m_Repositories.Location = new System.Drawing.Point(96, 12);
			this.m_Repositories.Name = "m_Repositories";
			this.m_Repositories.Size = new System.Drawing.Size(429, 21);
			this.m_Repositories.Sorted = true;
			this.m_Repositories.TabIndex = 1;
			this.m_Repositories.SelectedIndexChanged += new System.EventHandler(this.OnRepositoryChanged);
			// 
			// m_BrowseRepo
			// 
			this.m_BrowseRepo.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.m_BrowseRepo.Location = new System.Drawing.Point(531, 10);
			this.m_BrowseRepo.Name = "m_BrowseRepo";
			this.m_BrowseRepo.Size = new System.Drawing.Size(75, 23);
			this.m_BrowseRepo.TabIndex = 2;
			this.m_BrowseRepo.Text = "Browse...";
			this.m_BrowseRepo.UseVisualStyleBackColor = true;
			this.m_BrowseRepo.Click += new System.EventHandler(this.OnBrowseRepositories);
			// 
			// m_BranchLabel
			// 
			this.m_BranchLabel.AutoSize = true;
			this.m_BranchLabel.Location = new System.Drawing.Point(13, 46);
			this.m_BranchLabel.Name = "m_BranchLabel";
			this.m_BranchLabel.Size = new System.Drawing.Size(41, 13);
			this.m_BranchLabel.TabIndex = 0;
			this.m_BranchLabel.Text = "Branch";
			// 
			// m_Branches
			// 
			this.m_Branches.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.m_Branches.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.m_Branches.FormattingEnabled = true;
			this.m_Branches.Location = new System.Drawing.Point(96, 43);
			this.m_Branches.Name = "m_Branches";
			this.m_Branches.Size = new System.Drawing.Size(429, 21);
			this.m_Branches.Sorted = true;
			this.m_Branches.TabIndex = 1;
			this.m_Branches.SelectedIndexChanged += new System.EventHandler(this.OnBranchChanged);
			// 
			// m_ChangedFiles
			// 
			this.m_ChangedFiles.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.m_ChangedFiles.CheckOnClick = true;
			this.m_ChangedFiles.FormattingEnabled = true;
			this.m_ChangedFiles.Location = new System.Drawing.Point(96, 75);
			this.m_ChangedFiles.Name = "m_ChangedFiles";
			this.m_ChangedFiles.Size = new System.Drawing.Size(429, 124);
			this.m_ChangedFiles.Sorted = true;
			this.m_ChangedFiles.TabIndex = 3;
			// 
			// m_ChangedFilesLabel
			// 
			this.m_ChangedFilesLabel.AutoSize = true;
			this.m_ChangedFilesLabel.Location = new System.Drawing.Point(13, 79);
			this.m_ChangedFilesLabel.Name = "m_ChangedFilesLabel";
			this.m_ChangedFilesLabel.Size = new System.Drawing.Size(74, 13);
			this.m_ChangedFilesLabel.TabIndex = 4;
			this.m_ChangedFilesLabel.Text = "Changed Files";
			// 
			// m_AffectedFiles
			// 
			this.m_AffectedFiles.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.m_AffectedFiles.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
			this.m_AffectedFiles.FullRowSelect = true;
			this.m_AffectedFiles.HideSelection = false;
			this.m_AffectedFiles.Location = new System.Drawing.Point(96, 240);
			this.m_AffectedFiles.Name = "m_AffectedFiles";
			this.m_AffectedFiles.Size = new System.Drawing.Size(510, 207);
			this.m_AffectedFiles.Sorting = System.Windows.Forms.SortOrder.Ascending;
			this.m_AffectedFiles.TabIndex = 5;
			this.m_AffectedFiles.UseCompatibleStateImageBehavior = false;
			this.m_AffectedFiles.View = System.Windows.Forms.View.Details;
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "Filename";
			this.columnHeader1.Width = 246;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "Affected By";
			this.columnHeader2.Width = 2400;
			// 
			// m_AffectedFilesLabel
			// 
			this.m_AffectedFilesLabel.Location = new System.Drawing.Point(13, 240);
			this.m_AffectedFilesLabel.Name = "m_AffectedFilesLabel";
			this.m_AffectedFilesLabel.Size = new System.Drawing.Size(77, 35);
			this.m_AffectedFilesLabel.TabIndex = 6;
			this.m_AffectedFilesLabel.Text = "Files affected by changes";
			// 
			// m_AnalyseChanges
			// 
			this.m_AnalyseChanges.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.m_AnalyseChanges.Location = new System.Drawing.Point(531, 208);
			this.m_AnalyseChanges.Name = "m_AnalyseChanges";
			this.m_AnalyseChanges.Size = new System.Drawing.Size(75, 23);
			this.m_AnalyseChanges.TabIndex = 7;
			this.m_AnalyseChanges.Text = "Analyse";
			this.m_AnalyseChanges.UseVisualStyleBackColor = true;
			this.m_AnalyseChanges.Click += new System.EventHandler(this.OnAnalyseChangedFiles);
			// 
			// m_SourceFolderLabel
			// 
			this.m_SourceFolderLabel.AutoSize = true;
			this.m_SourceFolderLabel.Location = new System.Drawing.Point(13, 211);
			this.m_SourceFolderLabel.Name = "m_SourceFolderLabel";
			this.m_SourceFolderLabel.Size = new System.Drawing.Size(73, 13);
			this.m_SourceFolderLabel.TabIndex = 0;
			this.m_SourceFolderLabel.Text = "Source Folder";
			// 
			// m_SourceFolders
			// 
			this.m_SourceFolders.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.m_SourceFolders.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.m_SourceFolders.FormattingEnabled = true;
			this.m_SourceFolders.Location = new System.Drawing.Point(96, 208);
			this.m_SourceFolders.Name = "m_SourceFolders";
			this.m_SourceFolders.Size = new System.Drawing.Size(429, 21);
			this.m_SourceFolders.Sorted = true;
			this.m_SourceFolders.TabIndex = 1;
			this.m_SourceFolders.SelectedIndexChanged += new System.EventHandler(this.OnSourceFolderChanged);
			// 
			// m_RefreshChangeFiles
			// 
			this.m_RefreshChangeFiles.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.m_RefreshChangeFiles.Location = new System.Drawing.Point(531, 176);
			this.m_RefreshChangeFiles.Name = "m_RefreshChangeFiles";
			this.m_RefreshChangeFiles.Size = new System.Drawing.Size(75, 23);
			this.m_RefreshChangeFiles.TabIndex = 7;
			this.m_RefreshChangeFiles.Text = "Refresh";
			this.m_RefreshChangeFiles.UseVisualStyleBackColor = true;
			this.m_RefreshChangeFiles.Click += new System.EventHandler(this.OnRefreshChangedFiles);
			// 
			// BranchDependsForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(618, 459);
			this.Controls.Add(this.m_RepoLabel);
			this.Controls.Add(this.m_Repositories);
			this.Controls.Add(this.m_BrowseRepo);
			this.Controls.Add(this.m_BranchLabel);
			this.Controls.Add(this.m_Branches);
			this.Controls.Add(this.m_ChangedFilesLabel);
			this.Controls.Add(this.m_ChangedFiles);
			this.Controls.Add(this.m_RefreshChangeFiles);
			this.Controls.Add(this.m_SourceFolderLabel);
			this.Controls.Add(this.m_SourceFolders);
			this.Controls.Add(this.m_AnalyseChanges);
			this.Controls.Add(this.m_AffectedFilesLabel);
			this.Controls.Add(this.m_AffectedFiles);
			this.MinimumSize = new System.Drawing.Size(634, 498);
			this.Name = "BranchDependsForm";
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Branch Dependencies";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label m_RepoLabel;
		private System.Windows.Forms.ComboBox m_Repositories;
		private System.Windows.Forms.Button m_BrowseRepo;
		private System.Windows.Forms.Label m_BranchLabel;
		private System.Windows.Forms.ComboBox m_Branches;
		private System.Windows.Forms.CheckedListBox m_ChangedFiles;
		private System.Windows.Forms.Label m_ChangedFilesLabel;
		private System.Windows.Forms.ListView m_AffectedFiles;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.Label m_AffectedFilesLabel;
		private System.Windows.Forms.Button m_AnalyseChanges;
		private System.Windows.Forms.Label m_SourceFolderLabel;
		private System.Windows.Forms.ComboBox m_SourceFolders;
		private System.Windows.Forms.Button m_RefreshChangeFiles;
	}
}

