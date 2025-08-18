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

		private void OnRepositoryChanged(object sender, EventArgs e)
		{
			if (m_Repositories.SelectedItem.Equals(m_CurrentRepository))
				return;

			m_CurrentRepository = m_Repositories.SelectedItem.ToString();

			var branches = GitUtils.GetBranches(m_CurrentRepository);
			
			m_Branches.Items.Clear();
			m_Branches.Items.AddRange(branches.ToArray());

			m_Branches.SelectedItem = GitUtils.GetActiveBranch(m_CurrentRepository);
		}

		private void OnBranchChanged(object sender, EventArgs e)
		{

		}
	}
}
