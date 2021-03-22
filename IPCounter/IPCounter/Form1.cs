using System;
using System.IO;
using System.IO.Compression;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;

using Microsoft.Win32;

namespace IPCounter
{
	struct LogEntry
	{
		public LogEntry(string logLine)
		{
			IpAddress = string.Empty;
			Date = DateTime.MinValue;
			HttpCode = -1;

			var values = Regex.Matches(logLine, @"[\""].+?[\""]|[^ ]+")
								.Cast<Match>()
								.Select(m => m.Value)
								.ToList();

			if (values.Count() >= 10)
			{
				IpAddress = values[0];

				var date = values[3].Substring(1); // trim off '['
				date = date.Substring(0, date.IndexOf(':')); // trim off time
				date = date.Replace('/', ' ');

				DateTime.TryParse(date, out Date);

				int.TryParse(values[values.Count - 4], out HttpCode);
			}
			else
			{
				IpAddress = logLine.Substring(0, logLine.IndexOf(' '));
			}

		}

		public bool Matches(List<Tuple<int, int>> httpRanges)
		{
			if (HttpCode < 0)
				return true;

			foreach (var range in httpRanges)
			{
				if ((HttpCode >= range.Item1) && (HttpCode < range.Item2))
					return true;
			}

			return false;
		}

		public bool Matches(DateTimePicker from, DateTimePicker to)
		{
			if (Date == DateTime.MinValue)
				return true; // couldn't figure out the date

			if (from.Checked && (Date < from.Value))
				return false;

			if (to.Checked && (Date > to.Value))
				return false;

			return true;
		}

		public bool IsValid { get { return !string.IsNullOrWhiteSpace(IpAddress); } }

		public string IpAddress;
		public DateTime Date;
		public int HttpCode;
	}

	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();

			RestoreLastState();
		}

		protected override void OnClosed(EventArgs e)
		{
			SaveCurrentState();

			base.OnClosed(e);
		}

		private void RestoreLastState()
		{
			RegistryKey key = Registry.CurrentUser.OpenSubKey(@"SOFTWARE\AbstractSpoon\IPCounter");

			if (key != null)
			{
				m_MyIPAddress.Text = key.GetValue("MyIPAddress", "").ToString();
				m_MinCount.Text = key.GetValue("MinCount", "10").ToString();

				DateTime date;

				if (DateTime.TryParse(key.GetValue("FromDate", "").ToString(), out date))
				{
					m_FromDate.Value = date;
					m_FromDate.Checked = true;
				}
				else
				{
					m_FromDate.Checked = false;
				}

				if (DateTime.TryParse(key.GetValue("ToDate", "").ToString(), out date))
				{
					m_ToDate.Value = date;
					m_ToDate.Checked = true;
				}
				else
				{
					m_ToDate.Checked = false;
				}

				int numZips = 0;
				int.TryParse(key.GetValue("NumZipFiles", "0").ToString(), out numZips);

				for (int i = 0; i < numZips; i++)
					m_LogFileList.Items.Add(key.GetValue(String.Format("ZipFile{0}", i), "").ToString());

				for (int i = 0; i < m_HttpCodes.Items.Count; i++)
				{
					bool check = true;
					bool.TryParse(key.GetValue(String.Format("HttpCodeChecked{0}", i), true).ToString(), out check);

					m_HttpCodes.SetItemChecked(i, check);
				}
			}
			else
			{
				for (int i = 0; i < m_HttpCodes.Items.Count; i++)
					m_HttpCodes.SetItemChecked(i, true);
			}
		}

		private void SaveCurrentState()
		{
			RegistryKey key = Registry.CurrentUser.CreateSubKey(@"SOFTWARE\AbstractSpoon\IPCounter");

			key.SetValue("MyIPAddress", m_MyIPAddress.Text);
			key.SetValue("NumZipFiles", m_LogFileList.Items.Count);
			key.SetValue("MinCount", m_MinCount.Value);

			if (m_FromDate.Checked)
				key.SetValue("FromDate", m_FromDate.Value.ToShortDateString());
			else
				key.DeleteValue("FromDate", false);

			if (m_ToDate.Checked)
				key.SetValue("ToDate", m_ToDate.Value.ToShortDateString());
			else
				key.DeleteValue("ToDate", false);

			for (int i = 0; i < m_LogFileList.Items.Count; i++)
				key.SetValue(String.Format("ZipFile{0}", i), m_LogFileList.Items[i]);

			for (int i = 0; i < m_HttpCodes.Items.Count; i++)
				key.SetValue(String.Format("HttpCodeChecked{0}", i), m_HttpCodes.GetItemChecked(i));
		}

		private void OnBrowseLogFiles(object sender, EventArgs e)
		{
			var dlg = new OpenFileDialog
			{
				Title = "Select Compressed Apache Logs",

				AutoUpgradeEnabled = true,
				CheckFileExists = true,
				CheckPathExists = true,
				Multiselect = true,

				InitialDirectory = "D:\\Downloads",
				Filter = "Compressed Logs (*.gz)|abstractspoon.com-*.gz||",
				RestoreDirectory = true,

				ShowReadOnly = true
			};

			if (dlg.ShowDialog() == DialogResult.OK)
			{
				m_LogFileList.Items.Clear();
				m_ProgressList.Items.Clear();
				m_ResultsList.Items.Clear();

				foreach (var logPath in dlg.FileNames)
				{
					m_LogFileList.Items.Add(logPath);
				}
			}
		}

		private void OnAnalyseLogFiles(object sender, EventArgs e)
		{
			Cursor = Cursors.WaitCursor;

			m_ProgressList.Items.Clear();
			m_ResultsList.Items.Clear();

			var ipCounts = new Dictionary<string, int>();
			int totalCount = 0;

			foreach (var logPath in m_LogFileList.Items)
			{
				m_ProgressList.Items.Add(string.Format("Unzipping '{0}'", logPath.ToString()));
				m_ProgressList.Update();

				var tempPath = UnzipLogFile(logPath.ToString());

				if (!string.IsNullOrEmpty(tempPath))
				{
					m_ProgressList.Items.Add(string.Format("Analysing '{0}'", logPath.ToString()));
					m_ProgressList.Update();
					
					totalCount = AnalyseLogFile(tempPath, ipCounts);
				}
			}

			// Sort and write results 
			ipCounts = ipCounts.OrderByDescending(i => i.Value).ToDictionary(i => i.Key, i => i.Value);

			m_ResultsList.SuspendLayout();

			bool foundMyIP = false;
			int count = 0;

			foreach (var ip in ipCounts)
			{
				if (ip.Value < m_MinCount.Value)
					break;

				var lvItem = new ListViewItem(ip.Key);

				lvItem.SubItems.Add(ip.Value.ToString());
				lvItem.SubItems.Add(string.Format("{0:F1}", ((ip.Value * 100.0) / totalCount)));

				if (!String.IsNullOrWhiteSpace(m_MyIPAddress.Text))
				{
					if (ip.Key == m_MyIPAddress.Text)
					{
						lvItem.ForeColor = Color.White;
						lvItem.BackColor = Color.Blue;
						foundMyIP = true;
					}
					else if (!foundMyIP)
					{
						lvItem.ForeColor = Color.White;
						lvItem.BackColor = Color.Red;
					}
				}

				m_ResultsList.Items.Add(lvItem);

				if (++count == 50)
					m_ResultsList.Update();
			}

			m_ResultsList.ResumeLayout();

			if (m_ResultsList.Items.Count > 0)
				m_ResultsList.TopItem = m_ResultsList.Items[0];

			Cursor = Cursors.Default;
		}

		private int AnalyseLogFile(string logPath, Dictionary<string, int> ipCounts)
		{
			var httpRanges = GetHttpRanges();
			int numLines = 0;

			try
			{
				var file = new System.IO.StreamReader(logPath);
				string line;

				while ((line = file.ReadLine()) != null)
				{
					numLines++;

					var logEntry = new LogEntry(line);

					if (!logEntry.IsValid)
						continue;

					if (!logEntry.Matches(httpRanges))
						continue;

					if (!logEntry.Matches(m_FromDate, m_ToDate))
						continue;

					if (!ipCounts.ContainsKey(logEntry.IpAddress))
						ipCounts[logEntry.IpAddress] = 0;

					ipCounts[logEntry.IpAddress]++;
				}
			}
			catch (Exception)
			{
				ipCounts.Clear();
				numLines = 0;
			}

			return numLines;
		}

		//////////////////////////////////////////////////////////////////////////////////////
		// Decompressing Apache logs containing multiple chunks courtesy of:
		// https://bamcisnetworks.wordpress.com/2017/05/22/decompressing-concatenated-gzip-files-in-c-received-from-aws-cloudwatch-logs/
		//////////////////////////////////////////////////////////////////////////////////////

		private static string UnzipLogFile(string logPath)
		{
			// Get the bytes of the file
			byte[] FileBytes = File.ReadAllBytes(logPath);

			List<int> StartIndexes = new List<int>();

			/*
			* This pattern indicates the start of a GZip file as found from looking at the files
			* The file header is 10 bytes in size
			* 0-1 Signature 0x1F, 0x8B
			* 2 Compression Method - 0x08 is for DEFLATE, 0-7 are reserved
			* 3 Flags
			* 4-7 Last Modification Time
			* 8 Compression Flags
			* 9 Operating System
			*/

			byte[] StartOfFilePattern = new byte[] { 0x1F, 0x8B, 0x08 };

			//This will limit the last byte we check to make sure it doesn't exceed the end of the file
			//If the file is 100 bytes and the file pattern is 10 bytes, the last byte we want to check is
			//90 -> i.e. we will check index 90, 91, 92, 93, 94, 95, 96, 97, 98, 99 and index 99 is the last
			//index in the file bytes
			int TraversableLength = FileBytes.Length - StartOfFilePattern.Length;

			for (int i = 0; i <= TraversableLength; i++)
			{
				bool Match = true;

				//Test the next run of characters to see if they match
				for (int j = 0; j < StartOfFilePattern.Length; j++)
				{
					//If the character doesn't match, break out
					//We're making sure that i + j doesn't exceed the length as part
					//of the loop bounds
					if (FileBytes[i + j] != StartOfFilePattern[j])
					{
						Match = false;
						break;
					}
				}

				//If we did find a run of
				if (Match == true)
				{
					StartIndexes.Add(i);
					i += StartOfFilePattern.Length;
				}
			}

			//In case the pattern doesn't match, just start from the beginning of the file
			if (!StartIndexes.Any())
			{
				StartIndexes.Add(0);
			}

			List<byte[]> Chunks = new List<byte[]>();

			for (int i = 0; i < StartIndexes.Count; i++)
			{
				int Start = StartIndexes.ElementAt(i);
				int Length = 0;

				if (i + 1 == StartIndexes.Count)
				{
					Length = FileBytes.Length - Start;
				}
				else
				{
					Length = StartIndexes.ElementAt(i + 1) - i;
				}

				Chunks.Add(FileBytes.Skip(Start).Take(Length).ToArray());
			}

			string tempFileName = Path.GetTempFileName();

			using (FileStream decompressedFileStream = File.Create(tempFileName))
			{
				foreach (byte[] Chunk in Chunks)
				{
					using (MemoryStream MStream = new MemoryStream(Chunk))
					{
						using (GZipStream GZStream = new GZipStream(MStream, CompressionMode.Decompress))
						{
							try
							{
								GZStream.CopyTo(decompressedFileStream);
							}
							catch (Exception)
							{
#if DEBUG
								int breakpoint = 0;
#endif
							}
						}
					}
				}
			}

			return tempFileName;
		}

		private void OnDoubleClickResult(object sender, EventArgs e)
		{
			if (m_ResultsList.SelectedItems.Count > 0)
				Clipboard.SetData(DataFormats.Text, m_ResultsList.SelectedItems[0].Text);
		}

		private List<Tuple<int, int>> GetHttpRanges()
		{
			var httpRanges = new List<Tuple<int, int>>();

			if (m_HttpCodes.CheckedItems.Contains("100-199"))
				httpRanges.Add(new Tuple<int, int>(100, 199));

			if (m_HttpCodes.CheckedItems.Contains("200-299"))
				httpRanges.Add(new Tuple<int, int>(200, 299));

			if (m_HttpCodes.CheckedItems.Contains("300-399"))
				httpRanges.Add(new Tuple<int, int>(300, 399));

			if (m_HttpCodes.CheckedItems.Contains("400-499"))
				httpRanges.Add(new Tuple<int, int>(400, 499));

			if (m_HttpCodes.CheckedItems.Contains("500-599"))
				httpRanges.Add(new Tuple<int, int>(500, 599));

			return httpRanges;
		}

		private void OnMinCountKeyPress(object sender, KeyPressEventArgs e)
		{
			// Native control does not prevent decimals 
			// or negatives being typed
			e.Handled = ((e.KeyChar == '.') || (e.KeyChar == ',') || (e.KeyChar == '-'));
		}
	}
}
