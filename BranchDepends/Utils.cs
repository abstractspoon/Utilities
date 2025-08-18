using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace BranchDepends
{
	class Utils
	{
		public static IDictionary<string, HashSet<string>> BuildAllIncludedBy(string srcDir)
		{
			var allFiles = GetFilesByExtensions(new DirectoryInfo(srcDir), new string[] { ".h", ".cpp" });
			var allIncludedBy = new SortedDictionary<string, HashSet<string>>();

			// Build a dictionary mapping a file path to all
			// those files which explitly include it
			foreach (var file in allFiles)
			{
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

			return allIncludedBy;
		}

		public static IDictionary<string, HashSet<string>> GetDependents(IList<string> fileList, IDictionary<string, HashSet<string>> allIncludedBy)
		{
			var allDependents = new SortedDictionary<string, HashSet<string>>();

			foreach (var file in fileList)
				GetFileDependents(file, allIncludedBy, allDependents);

			return allDependents;
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

		static void GetFileDependents(string fullFilePath, 
									  IDictionary<string, HashSet<string>> allIncludedBy, 
									  IDictionary<string, HashSet<string>> dependents)
		{
			HashSet<string> includedBy = null;

			if (allIncludedBy.TryGetValue(fullFilePath.ToLower(), out includedBy))
			{
				foreach (var by in includedBy)
				{
					HashSet<string> includes = null;

					if (!dependents.TryGetValue(by, out includes))
					{
						includes = new HashSet<string>();
						dependents[by] = includes;
					}

					includes.Add(/*Path.GetFileName*/(fullFilePath));

					GetFileDependents(by, allIncludedBy, dependents); // RECURSIVE CALL
				}
			}
		}

	}
}
