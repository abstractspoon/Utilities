using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

using Microsoft.Win32;

namespace BranchDepends
{
	public partial class BranchDependsForm : Form
	{
		string m_CurrentRepository = string.Empty;
		string m_CurrentBranch = string.Empty;
		string m_CurrentSourceFolder = string.Empty;

		public BranchDependsForm()
		{
			InitializeComponent();

			var repostories = Registry.CurrentUser.GetValue("Repositories")?.ToString();

			if (repostories != null)
			{
				m_Repositories.Items.AddRange(repostories.Split(new char[] { '|' }, StringSplitOptions.RemoveEmptyEntries));

				var currentRepo = Registry.CurrentUser.GetValue("CurrentRepository")?.ToString();
				m_Repositories.SelectedItem = currentRepo;

				var currentSrcFolder = Registry.CurrentUser.GetValue("CurrentSourceFolder")?.ToString();
				m_SourceFolders.SelectedItem = currentSrcFolder;
			}
		}

		protected override void OnFormClosed(FormClosedEventArgs e)
		{
			base.OnFormClosed(e);

			Registry.CurrentUser.SetValue("Repositories", string.Join("|", m_Repositories.Items.Cast<string>()));
			Registry.CurrentUser.SetValue("CurrentRepository", m_CurrentRepository);
			Registry.CurrentUser.SetValue("CurrentSourceFolder", m_CurrentSourceFolder);
		}

		private void OnBrowseRepositories(object sender, EventArgs e)
		{
			string folderPath = "";

			using (var dialog = new FolderBrowserDialog())
			{
				dialog.ShowNewFolderButton = false;
				dialog.SelectedPath = m_CurrentRepository;

				while (dialog.ShowDialog() == DialogResult.OK)
				{
					folderPath = dialog.SelectedPath;

					if (!Directory.Exists(Path.Combine(folderPath, ".git")))
					{
						MessageBox.Show("Not a Git repository");
					}
					else
					{
						if (m_Repositories.Items.IndexOf(folderPath) == -1)
							m_Repositories.Items.Add(folderPath);

						m_Repositories.SelectedItem = folderPath;
						return;
					}
				}
			}
		}

		private void OnRepositoryChanged(object sender, EventArgs e)
		{
			if (m_Repositories.SelectedItem.Equals(m_CurrentRepository))
				return;

			m_CurrentRepository = m_Repositories.SelectedItem.ToString();

			var branches = GitUtils.GetBranches(m_CurrentRepository);
			
			m_Branches.Items.Clear();
			m_Branches.Items.AddRange(branches.ToArray());

			m_Branches.SelectedItem = GitUtils.GetActiveBranch(m_CurrentRepository);

			var srcFolders = Directory.GetDirectories(m_CurrentRepository).Where(d => !d.Contains(".git")).ToList();

			m_SourceFolders.Items.Clear();
			m_SourceFolders.Items.AddRange(srcFolders.ToArray());

			m_SourceFolders.SelectedItem = srcFolders.FirstOrDefault();
		}

		private void OnBranchChanged(object sender, EventArgs e)
		{
			if (m_Branches.SelectedItem == null)
			{
				m_ChangedFiles.Items.Clear();
				return;
			}

			var newBranch = m_Branches.SelectedItem.ToString();

			if (newBranch == m_CurrentBranch)
				return;

			Cursor = Cursors.WaitCursor;

			if (!string.IsNullOrEmpty(m_CurrentBranch))
			{
				if (!GitUtils.SelectBranch(m_CurrentRepository, newBranch))
					return;
			}

			m_CurrentBranch = newBranch;

			Cursor = Cursors.Default;

			RefreshChangedFiles();
		}

		private void OnRefreshChangedFiles(object sender, EventArgs e)
		{
			RefreshChangedFiles();
		}

		private void RefreshChangedFiles()
		{
			Cursor = Cursors.WaitCursor;

			var changedFiles = GitUtils.GetChangedFiles(m_CurrentRepository);

			m_ChangedFiles.Items.Clear();
			m_AffectedFiles.Items.Clear();

			foreach (var file in changedFiles)
				m_ChangedFiles.Items.Add(file, true);

			Cursor = Cursors.Default;
		}

		private void OnSourceFolderChanged(object sender, EventArgs e)
		{
			m_AffectedFiles.Items.Clear();

			if (m_SourceFolders.SelectedItem == null)
				m_CurrentSourceFolder = string.Empty;
			else
				m_CurrentSourceFolder = m_SourceFolders.SelectedItem.ToString();
		}

		private void OnProcessChangedFiles(object sender, EventArgs e)
		{
			if (string.IsNullOrEmpty(m_CurrentRepository) ||
				string.IsNullOrEmpty(m_CurrentBranch) ||
				string.IsNullOrEmpty(m_CurrentSourceFolder))
			{
				return;
			}

			Cursor = Cursors.WaitCursor;

			var fileList = m_ChangedFiles.CheckedItems.Cast<string>().ToList();
			fileList = fileList.ConvertAll(file => Path.GetFullPath(Path.Combine(m_CurrentRepository, file)));
			
			// Create 'Included By' lookup
			var allIncludedBy = Utils.BuildAllIncludedBy(m_CurrentSourceFolder);
			
			// Process file list
			var allDependents = Utils.GetDependents(fileList, allIncludedBy);

			// Output
			m_AffectedFiles.Items.Clear();

			foreach (var dependent in allDependents)
			{
				var filePath = dependent.Key
										.Replace(m_CurrentRepository, "")
										.TrimStart(new char[] { '\\' });

				var item = m_AffectedFiles.Items.Add(filePath);
				item.SubItems.Add(string.Join(", ", dependent.Value.Select(f => Path.GetFileName(f))));
			}

			Cursor = Cursors.Default;
		}
	}
}
