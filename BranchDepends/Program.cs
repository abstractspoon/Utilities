using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace BranchDepends
{
	class Program
	{
		static void Main(string[] args)
		{
			if ((args.Count() < 2) || (args.Count() > 3))
			{
				// TODO
				return;
			}

			// Read commandline arguments
			var repoDir = args[0];
			var srcDir = args[1];

			var fileList = new List<string>();

			if (args.Count() == 3)
			{
				fileList.AddRange(File.ReadLines(args[2]));
			}
			else
			{
				string file = Console.ReadLine();

				while (file != null)
				{
					fileList.Add(file);
					file = Console.ReadLine();
				}
			}

			// Create 'Included By' lookup
			var allFiles = GetFilesByExtensions(new DirectoryInfo(srcDir), new string[] { ".h", ".cpp" });
			var allIncludedBy = new Dictionary<string, HashSet<string>>();

			foreach (var file in allFiles)
			{
				//Console.WriteLine(file.FullName);

				var includes = ReadIncludes(file.FullName);

				foreach (var include in includes)
				{
					HashSet<string> includedBy = null;
					var includeLower = include.ToLower();

					if (!allIncludedBy.TryGetValue(includeLower, out includedBy))
					{
						includedBy = new HashSet<string>();
						allIncludedBy[includeLower] = includedBy;
					}

					includedBy.Add(file.FullName);
				}
			}

			// Process file list
			var allDependents = new HashSet<string>();

			foreach (var file in fileList)
			{
				string fullFilePath = Path.GetFullPath(Path.Combine(repoDir, file));
				GetFileDependents(fullFilePath, allIncludedBy, allDependents);
			}

			// Convert to sorted list
			var sortedList = allDependents.ToList();
			sortedList.Sort();

			foreach (var dependent in sortedList)
			{
				Console.WriteLine(dependent);
			}
		}

		static IEnumerable<FileInfo> GetFilesByExtensions(DirectoryInfo dirInfo, params string[] extensions)
		{
			var allowedExtensions = new HashSet<string>(extensions, StringComparer.OrdinalIgnoreCase);

			return dirInfo.EnumerateFiles("*", System.IO.SearchOption.AllDirectories)
						  .Where(f => allowedExtensions.Contains(f.Extension));
		}

		static HashSet<string> ReadIncludes(string fullFilePath)
		{
			var includes = new HashSet<string>();

			if (File.Exists(fullFilePath))
			{
				string fileDir = Path.GetDirectoryName(fullFilePath);

				foreach (var line in File.ReadLines(fullFilePath))
				{
					string rest = line.TrimStart();

					if (!rest.StartsWith("#"))
						continue;

					rest = rest.Substring(1).TrimStart();

					if (!rest.StartsWith("include"))
						continue;

					rest = rest.Substring(7).TrimStart();

					if (rest.Count() == 0)
						continue;

					int endOfInclude = 0;

					switch (rest[0])
					{
					case '\"':
						endOfInclude = rest.IndexOf('\"', 1);
						break;

// 					case '<':
// 						endOfInclude = rest.IndexOf('>', 1);
// 						break;

					case '{':
						return includes;

					default:
						continue;
					}

					var include = rest.Substring(1, endOfInclude - 1);

					includes.Add(Path.GetFullPath(Path.Combine(fileDir, include)));
				}
			}

			return includes;
		}

		static void GetFileDependents(string fullFilePath, Dictionary<string, HashSet<string>> allIncludedBy, HashSet<string> dependents)
		{
			HashSet<string> includedBy = null;

			if (allIncludedBy.TryGetValue(fullFilePath.ToLower(), out includedBy))
			{
				foreach (var include in includedBy)
				{
					if (dependents.Contains(include))
						continue;

					dependents.Add(include);

					GetFileDependents(include, allIncludedBy, dependents); // RECURSIVE CALL
				}
			}
		}

	}
}
