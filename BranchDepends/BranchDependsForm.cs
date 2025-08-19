using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Diagnostics;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

using Microsoft.Win32;

namespace BranchDepends
{
	public partial class BranchDependsForm : Form, IProgress<int>
	{
		string m_CurrentRepository = string.Empty;
		string m_CurrentBranch = string.Empty;
		string m_CurrentSourceFolder = string.Empty;

		int m_ProgressBase = 0;

		IDictionary<string, HashSet<string>> m_AllIncludes; // for Results drawing

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

		public virtual void Report(int percent)
		{
			m_Progress.Value = (m_ProgressBase + percent);
			m_Progress.Update();
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
						MessageBox.Show("Not a Git repository", "Branch Dependencies");
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

			ClearChangedFileUI();
			ClearAffectedFileUI();

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
			var newBranch = m_Branches.SelectedItem?.ToString();

			if (newBranch == m_CurrentBranch)
				return;

			ClearChangedFileUI();
			ClearAffectedFileUI();

			if (string.IsNullOrEmpty(newBranch))
			{
				// Shouldn't be possible
				Debug.Assert(false);
				return;
			}

			Cursor = Cursors.WaitCursor;

			if (!GitUtils.SelectBranch(m_CurrentRepository, newBranch))
				return;

			m_CurrentBranch = newBranch;

			Cursor = Cursors.Default;

			RefreshChangedFileUI();
		}

		private void OnRefreshChangedFiles(object sender, EventArgs e)
		{
			Cursor = Cursors.WaitCursor;

			RefreshChangedFileUI();

			Cursor = Cursors.Default;
		}

		private void RefreshChangedFileUI()
		{
			ClearChangedFileUI();
			ClearAffectedFileUI();

			var changedFiles = Utils.GetChangedFiles(m_CurrentRepository);

			foreach (var file in changedFiles)
				m_ChangedFiles.Items.Add(file, true);

			m_NumChangedFilesLabel.Text = string.Format("({0})", changedFiles.Count);
		}

		private void ClearChangedFileUI()
		{
			m_ChangedFiles.Items.Clear();
			m_NumChangedFilesLabel.Text = string.Empty;
		}

		private void ClearAffectedFileUI()
		{
			m_AffectedFiles.Items.Clear();
			m_NumAffectedFilesLabel.Text = string.Empty;
		}

		private void OnSourceFolderChanged(object sender, EventArgs e)
		{
			ClearAffectedFileUI();

			if (m_SourceFolders.SelectedItem == null)
				m_CurrentSourceFolder = string.Empty;
			else
				m_CurrentSourceFolder = m_SourceFolders.SelectedItem.ToString();
		}

		private void OnAnalyseChangedFiles(object sender, EventArgs e)
		{
			if (string.IsNullOrEmpty(m_CurrentRepository) ||
				string.IsNullOrEmpty(m_CurrentBranch) ||
				string.IsNullOrEmpty(m_CurrentSourceFolder))
			{
				return;
			}

			Cursor = Cursors.WaitCursor;

			// Build list of files to analyse
			var fileList = m_ChangedFiles.CheckedItems.Cast<string>().ToList();
			fileList = fileList.ConvertAll(f => Path.GetFullPath(Path.Combine(m_CurrentRepository, f)));

			// Create 'Includes' lookup
			m_ProgressBase = 0;
			m_AllIncludes = Utils.GetAllIncludes(m_CurrentSourceFolder, this);

			// Create 'Included By' lookup
			m_ProgressBase = 100;
			var allIncludedBy = Utils.BuildIncludedBy(m_AllIncludes, this);
			
			// Generate map of dependents
			m_ProgressBase = 200;
			var allDependents = Utils.GetDependents(fileList, allIncludedBy, this);

			// Output to results list
			m_ProgressBase = 300;

			m_AffectedFiles.Items.Clear();
			m_NumAffectedFilesLabel.Text = string.Empty;

			int iFile = 0, numFiles = allDependents.Count;

			foreach (var dependent in allDependents)
			{
				Report((++iFile * 100) / numFiles);

				var lvi = new ListViewItem(dependent.Key) { Tag = dependent.Value };
				lvi.SubItems.Add("."); // dummy text to trigger subitem ownerdraw

				m_AffectedFiles.Items.Add(lvi);
			}

			m_NumAffectedFilesLabel.Text = string.Format("({0})", allDependents.Count);
			m_Progress.Value = 0;

			Cursor = Cursors.Default;
		}

		private void OnDrawResultColumnHeader(object sender, DrawListViewColumnHeaderEventArgs e)
		{
			e.DrawDefault = true;
		}

		private void OnDrawResult(object sender, DrawListViewItemEventArgs e)
		{
			// Do it all in OnDrawResultSubItem
		}

		private void OnDrawResultSubItem(object sender, DrawListViewSubItemEventArgs e)
		{
			Brush backBrush = (e.Item.Selected ? SystemBrushes.Highlight : SystemBrushes.Window);
			e.Graphics.FillRectangle(backBrush, e.Bounds);

			e.DrawFocusRectangle(e.Item.Bounds);

			Brush textBrush = (e.Item.Selected ? SystemBrushes.HighlightText : SystemBrushes.WindowText);
			var format = new StringFormat() { LineAlignment = StringAlignment.Center, FormatFlags = StringFormatFlags.NoWrap };

			switch (e.ColumnIndex)
			{
			case 0:
				{
					var text = e.Item.Text.Replace(m_CurrentRepository, "").TrimStart(new[] { '\\'});
					e.Graphics.DrawString(text, m_AffectedFiles.Font, textBrush, e.Bounds, format);
				}
				break;

			case 1:
				{
					var depends = (e.Item.Tag as HashSet<string>);

					if (depends != null)
					{
						HashSet<string> includes = Utils.GetValue(m_AllIncludes, e.Item.Text, false);

						RectangleF textRect = e.Bounds;
						bool first = true;

						foreach (var depend in depends)
						{
							DrawSubItemTextAndAdvance(depend, includes, first, e, format, ref textRect);
							first = false;
						}
					}
				}
				break;
			}
		}

		private void DrawSubItemTextAndAdvance(string depend, HashSet<string> includes, bool first, DrawListViewSubItemEventArgs e, StringFormat format, ref RectangleF rect)
		{
			var textBrush = (e.Item.Selected ? SystemBrushes.HighlightText : SystemBrushes.WindowText);

			var font = m_AffectedFiles.Font;

			if (!first)
			{
				e.Graphics.DrawString(", ", font, textBrush, rect, format);
				rect.Offset(e.Graphics.MeasureString(", ", font).Width, 0);
			}

 			if ((includes != null) && includes.Contains(depend))
 				font = new Font(font, FontStyle.Underline);

			var text = Path.GetFileName(depend);

			e.Graphics.DrawString(text, font, textBrush, rect, format);
			rect.Offset(e.Graphics.MeasureString(text, font).Width, 0);
		}
	}
}
