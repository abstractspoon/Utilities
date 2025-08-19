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
		public static IDictionary<string, HashSet<string>> GetAllIncludes(string srcDir)
		{
			var allFiles = GetFilesByExtensions(new DirectoryInfo(srcDir), new string[] { ".h", ".cpp" });
			var allIncludes = new SortedDictionary<string, HashSet<string>>();

			foreach (var file in allFiles)
				allIncludes[file.FullName.ToLower()] = ReadIncludes(file.FullName);

			return allIncludes;
		}

		public static IDictionary<string, HashSet<string>> BuildIncludedBy(IDictionary<string, HashSet<string>> fileIncludes)
		{
			var allIncludedBy = new SortedDictionary<string, HashSet<string>>();

			foreach (var file in fileIncludes)
			{
				foreach (var include in file.Value)
				{
					var includedBy = GetValue(allIncludedBy, include.ToLower(), true);
					includedBy.Add(file.Key);
				}
			}

			return allIncludedBy;
		}

		public static IDictionary<string, HashSet<string>> GetDependents(IList<string> fileList, IDictionary<string, HashSet<string>> allIncludedBy)
		{
			var allDependents = new SortedDictionary<string, HashSet<string>>();

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

					rest = rest.Substring(1, endOfInclude - 1);

					includes.Add(Path.GetFullPath(Path.Combine(fileDir, rest)).ToLower());
				}
			}

			return includes;
		}

		static void GetFileDependents(string fullFilePath,
									  bool explicitInclude, 
									  IDictionary<string, HashSet<string>> allIncludedBy, 
									  IDictionary<string, HashSet<string>> dependents)
		{
			var includedBy = GetValue(allIncludedBy, fullFilePath.ToLower(), false);

			if (includedBy != null)
			{
				foreach (var by in includedBy)
				{
					var includes = GetValue(dependents, by, true);
					includes.Add(fullFilePath);

					// also include this file's dependencies
					var depends = GetValue(dependents, fullFilePath, false);

					if (depends != null)
						includes.UnionWith(depends);

					GetFileDependents(by, false, allIncludedBy, dependents); // RECURSIVE CALL
				}
			}
		}

		internal static HashSet<string> GetValue(IDictionary<string, HashSet<string>> items, string key, bool autoAdd)
		{
			HashSet<string> item = null;

			if (!items.TryGetValue(key, out item) && autoAdd)
			{
				item = new HashSet<string>();
				items[key] = item;
			}

			return item;
		}
	}
}
