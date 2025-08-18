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
			}
		}

		protected override void OnFormClosed(FormClosedEventArgs e)
		{
			base.OnFormClosed(e);

			Registry.CurrentUser.SetValue("Repositories", string.Join("|", m_Repositories.Items.Cast<string>()));
			Registry.CurrentUser.SetValue("CurrentRepository", m_CurrentRepository);
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

			if (!string.IsNullOrEmpty(m_CurrentBranch))
			{
				if (!GitUtils.SelectBranch(m_CurrentRepository, newBranch))
					return;
			}

			var changedFiles = GitUtils.GetChangedFiles(m_CurrentRepository);

			m_ChangedFiles.Items.Clear();
			m_ChangedFiles.Items.AddRange(changedFiles.ToArray());

			m_CurrentBranch = newBranch;
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
			// 			var repoDir = String.Empty; // TODO
			// 			var srcDir = String.Empty; // TODO
			// 
			// 			var fileList = new List<string>(); // TODO
			// 
			// 			if (args.Count() == 3)
			// 			{
			// 				fileList.AddRange(File.ReadLines(args[2]));
			// 			}
			// 			else
			// 			{
			// 				var branchList = new List<string>();
			// 				GetBranchesFromGit(repoDir, branchList);
			// 
			// 				GetFilesFromGit(repoDir, fileList);
			// 			}
			// 
			// 			fileList = fileList.ConvertAll(file => Path.GetFullPath(Path.Combine(repoDir, file)));
			// 
			// 			// Create 'Included By' lookup
			// 			var allIncludedBy = BuildAllIncludedBy(srcDir);
			// 
			// 			// Process file list
			// 			var allDependents = GetDependents(fileList, allIncludedBy);
			// 
			// 			// Output
			// 			foreach (var dependent in allDependents)
			// 			{
			// 				Console.WriteLine("{0} ({1})", dependent.Key, string.Join(", ", dependent.Value.ToArray()));
			// 			}

		}
	}
}
