using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace BranchDepends
{
	class IncludeFile
	{
		public IncludeFile(string fullPath, bool explicitInclude = true)
		{
			FullPath = fullPath;
			Explicit = explicitInclude;
		}

		public string FullPath;
		public bool Explicit = false;

		public override string ToString() {	return FullPath; }
		public string ToLower() { return FullPath.ToLower(); }
	}

	class Utils
	{
		public static IDictionary<string, HashSet<IncludeFile>> BuildAllIncludedBy(string srcDir)
		{
			var allFiles = GetFilesByExtensions(new DirectoryInfo(srcDir), new string[] { ".h", ".cpp" });
			var allIncludedBy = new SortedDictionary<string, HashSet<IncludeFile>>();

			// Build a dictionary mapping a file path to all
			// those files which explitly include it
			foreach (var file in allFiles)
			{
				var includes = ReadIncludes(file.FullName);

				foreach (var include in includes)
				{
					var includedBy = GetValue(allIncludedBy, include.ToLower(), true);
					includedBy.Add(new IncludeFile(file.FullName, true));
				}
			}

			return allIncludedBy;
		}

		public static IDictionary<string, HashSet<IncludeFile>> GetDependents(IList<string> fileList, IDictionary<string, HashSet<IncludeFile>> allIncludedBy)
		{
			var allDependents = new SortedDictionary<string, HashSet<IncludeFile>>();

			foreach (var file in fileList)
				GetFileDependents(file, true, allIncludedBy, allDependents);

			return allDependents;
		}

		static IEnumerable<FileInfo> GetFilesByExtensions(DirectoryInfo dirInfo, params string[] extensions)
		{
			var allowedExtensions = new HashSet<string>(extensions, StringComparer.OrdinalIgnoreCase);

			return dirInfo.EnumerateFiles("*", System.IO.SearchOption.AllDirectories)
						  .Where(f => allowedExtensions.Contains(f.Extension));
		}

		static HashSet<IncludeFile> ReadIncludes(string fullFilePath)
		{
			var includes = new HashSet<IncludeFile>();

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

					rest = rest.Substring(1, endOfInclude - 1);

					includes.Add(new IncludeFile(Path.GetFullPath(Path.Combine(fileDir, rest))));
				}
			}

			return includes;
		}

		static void GetFileDependents(string fullFilePath,
									  bool explicitInclude, 
									  IDictionary<string, HashSet<IncludeFile>> allIncludedBy, 
									  IDictionary<string, HashSet<IncludeFile>> dependents)
		{
			var includedBy = GetValue(allIncludedBy, fullFilePath.ToLower(), false);

			if (includedBy != null)
			{
				foreach (var by in includedBy)
				{
					var includes = GetValue(dependents, by.FullPath, true);
					includes.Add(new IncludeFile(fullFilePath, explicitInclude));

					// also include this file's dependencies
					var depends = GetValue(dependents, fullFilePath, false);

					if (depends != null)
						includes.UnionWith(depends);

					GetFileDependents(by.FullPath, false, allIncludedBy, dependents); // RECURSIVE CALL
				}
			}
		}

		static HashSet<IncludeFile> GetValue(IDictionary<string, HashSet<IncludeFile>> items, string key, bool autoAdd)
		{
			HashSet<IncludeFile> item = null;

			if (!items.TryGetValue(key, out item) && autoAdd)
			{
				item = new HashSet<IncludeFile>();
				items[key] = item;
			}

			return item;
		}
	}
}
