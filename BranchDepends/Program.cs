using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace BranchDepends
{
	class Program
	{
		static void Main(string[] args)
		{
			if (args.Count() == 0)
				return;

			var dependsDir = args[0];
			var fileList = new List<string>();

			if (args.Count() == 2)
			{
				fileList.AddRange(File.ReadLines(args[1]));
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

			ProcessChangedFiles(dependsDir, fileList);
		}

		static void ProcessChangedFiles(string dependsDir, List<string> fileList)
		{
			// Convert source files to headers 
			// OR delete them if the header already exists
			int file = fileList.Count;

			while (file-- > 0)
			{
				var filePath = fileList[file];

				//Console.WriteLine(filePath);

				if (Path.GetExtension(filePath).ToLower() == ".cpp")
				{
					fileList.RemoveAt(file);

					var headerFile = Path.ChangeExtension(filePath, ".h");

					if (!fileList.Contains(headerFile))
						fileList.Add(headerFile);
				}
				else if (Path.GetExtension(filePath).ToLower() != ".h")
				{
					fileList.RemoveAt(file);
				}
			}

			foreach (var filePath in fileList)
			{
				var dotFile = FindDotFile(dependsDir, filePath.Replace('/', '\\'));

				if (dotFile != null)
				{
					Console.WriteLine(dotFile);
				}
				else
				{
					int breakpoint = 0;
				}
			}
		}

		static string FindDotFile(string dependsDir, string filePath)
		{
			// work our way from the full path down to the filename
			// seeing if the corresponding dot file exists
			bool exists = false;
			var paths = filePath.Split('\\').ToList();

			while (!exists && (paths.Count > 0))
			{
				var dotFilePath = ConvertFilePathToDotStyle(dependsDir, Path.Combine(paths.ToArray()));

				if (File.Exists(dotFilePath))
					return dotFilePath;

				// Trim leading folder
				paths.RemoveAt(0);
			}

			return null;
		}

		static string ConvertFilePathToDotStyle(string dependsDir, string filePath)
		{
			var dotFileName = new StringBuilder();

			foreach (var fchar in filePath)
			{
				switch (fchar)
				{
				case '.':
					dotFileName.Append("_8");
					break;

				case '\\':
				case '/':
					dotFileName.Append("_2");
					break;

				default:
					if (Char.IsUpper(fchar))
					{
						dotFileName.Append('_');
						dotFileName.Append(Char.ToLower(fchar));
					}
					else
					{
						dotFileName.Append(fchar);
					}
					break;
				}
			}

			return Path.Combine(dependsDir, dotFileName.ToString() + "__dep__incl.dot");
		}
	}
}
