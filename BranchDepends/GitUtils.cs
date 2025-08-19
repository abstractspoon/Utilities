using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace BranchDepends
{
	class GitUtils
	{
		public static IList<string> GetBranches(string repoDir)
		{
			var branches = RunGitCommand("branch --all", repoDir);

			branches = branches.Where(b => !b.Contains("master"))
							   .Where(b => b.StartsWith("remotes/origin/"))
							   .Select(b => b.Replace("remotes/origin/", ""))
							   .ToList();

			return branches;
		}

		public static string GetActiveBranch(string repoDir)
		{
			var branches = RunGitCommand("branch", repoDir);

			branches = branches.Where(b => !b.Contains("master"))
							   .Where(b => b.StartsWith("* "))
							   .Select(b => b.Substring(2))
							   .ToList();

			return branches.FirstOrDefault();
		}

		public static bool SelectBranch(string repoDir, string branch)
		{
			var result = RunGitCommand(string.Format("checkout {0}", branch), repoDir);

			return true;
		}

		public static IList<string> GetChangedFiles(string repoDir, params string[] extensions)
		{
			var files = RunGitCommand("diff master --name-only", repoDir);

			if (extensions.Count() != 0)
			{
				var allowedExtensions = new HashSet<string>(extensions, Utils.CaseInsensitive);

				files = files.Where(f => allowedExtensions.Contains(Path.GetExtension(f))).ToList();
			}

			return files.Select(f => f.Replace('/', '\\')).ToList();
		}

		static IList<string> RunGitCommand(string command, string repoDir)
		{
			var results = new List<string>();

			using (var process = new Process())
			{
				process.StartInfo.FileName = "cmd.exe";
				process.StartInfo.WorkingDirectory = repoDir;
				process.StartInfo.Arguments = "/c git " + command;

				process.StartInfo.CreateNoWindow = true;
				process.StartInfo.UseShellExecute = false;
				process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;

				process.StartInfo.RedirectStandardOutput = true;
				process.OutputDataReceived += (s, e) =>
				{
					if (e.Data != null)
						results.Add(e.Data.Trim());
				};

				process.Start();
				process.BeginOutputReadLine();
				process.WaitForExit();
			}

			return results;
		}
	}
}
