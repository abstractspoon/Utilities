using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BranchDepends
{
	public partial class BranchDependsForm : Form
	{
		public BranchDependsForm()
		{
			InitializeComponent();

			var repoDir = String.Empty; // TODO
			var srcDir = String.Empty; // TODO

			var fileList = new List<string>(); // TODO

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
