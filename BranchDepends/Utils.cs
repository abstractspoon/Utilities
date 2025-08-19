using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace BranchDepends
{
	public class CaseInsensitiveComparer : IEqualityComparer<string>
	{
		public virtual bool Equals(string x, string y)
		{
			return (string.Compare(x, y, true) == 0);
		}

		public virtual int GetHashCode(string obj)
		{
			return obj.ToLower().GetHashCode();
		}
	}

	class Utils
	{
		public readonly static CaseInsensitiveComparer CaseInsensitive = new CaseInsensitiveComparer();

		// --------------------------------------------------------

		public static void PrepareFileList(IList<string> fileList)
		{
			// Convert all .cpp file to their header equivalent
			// ie. If the .cpp file has been modified then all
			//     files which include its .h are potentially affected
			var fileSet = new HashSet<string>(fileList, Utils.CaseInsensitive);
			fileList.Clear();

			foreach (var file in fileSet)
			{
				string lowerExt = Path.GetExtension(file).ToLower();

				if (lowerExt == ".cpp")
				{
					string header = Path.ChangeExtension(file, ".h");

					if (!fileSet.Contains(header) && File.Exists(header))
						fileList.Add(header);
				}
				else if (lowerExt == ".h")
				{
					fileList.Add(file);
				}
			}
		}

		public static IDictionary<string, HashSet<string>> GetAllIncludes(string srcDir, IProgress<int> progress)
		{
			var allFiles = GetFilesByExtensions(new DirectoryInfo(srcDir), new string[] { ".h", ".cpp" });
			var allIncludes = new SortedDictionary<string, HashSet<string>>(StringComparer.OrdinalIgnoreCase);

			int iFile = 0, numFiles = allFiles.Count();

			foreach (var file in allFiles)
			{
				progress?.Report((++iFile * 100) / numFiles);

				allIncludes[file.FullName] = ReadIncludes(file.FullName);
			}

			return allIncludes;
		}

		public static IDictionary<string, HashSet<string>> BuildIncludedBy(IDictionary<string, HashSet<string>> fileIncludes, IProgress<int> progress)
		{
			var allIncludedBy = new SortedDictionary<string, HashSet<string>>(StringComparer.OrdinalIgnoreCase);

			int iFile = 0, numFiles = fileIncludes.Count();

			foreach (var file in fileIncludes)
			{
				progress?.Report((++iFile * 100) / numFiles);

				foreach (var include in file.Value)
				{
					var includedBy = GetValue(allIncludedBy, include, true);
					includedBy.Add(file.Key);
				}
			}

			return allIncludedBy;
		}

		public static IDictionary<string, HashSet<string>> GetDependents(IList<string> fileList, IDictionary<string, HashSet<string>> allIncludedBy, IProgress<int> progress)
		{
			var allDependents = new SortedDictionary<string, HashSet<string>>(StringComparer.OrdinalIgnoreCase);

			int iFile = 0, numFiles = fileList.Count();

			foreach (var file in fileList)
			{
				progress?.Report((++iFile * 100) / numFiles);

				GetFileDependents(file, true, allIncludedBy, allDependents);
			}

			return allDependents;
		}

		static IEnumerable<FileInfo> GetFilesByExtensions(DirectoryInfo dirInfo, params string[] extensions)
		{
			var allowedExtensions = new HashSet<string>(extensions, CaseInsensitive);

			return dirInfo.EnumerateFiles("*", System.IO.SearchOption.AllDirectories)
						  .Where(f => allowedExtensions.Contains(f.Extension));
		}

		static HashSet<string> ReadIncludes(string fullFilePath)
		{
			var includes = new HashSet<string>(CaseInsensitive);

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

					includes.Add(Path.GetFullPath(Path.Combine(fileDir, rest)));
				}
			}

			return includes;
		}

		static void GetFileDependents(string fullFilePath,
									  bool explicitInclude, 
									  IDictionary<string, HashSet<string>> allIncludedBy, 
									  IDictionary<string, HashSet<string>> dependents)
		{
			var includedBy = GetValue(allIncludedBy, fullFilePath, false);

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
				item = new HashSet<string>(CaseInsensitive);
				items[key] = item;
			}

			return item;
		}
	}
}
