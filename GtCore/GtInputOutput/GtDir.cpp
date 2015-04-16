/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT by Nokia
**
**  GT is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to GT.
**
**  GT is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with GT.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)
#include <locale>
#include <codecvt>
#include <string>

#include ".\GtDir.h"

namespace GT
{
	namespace GtCore
	{

		int StringToWString(std::wstring &ws, const std::string &s)
		{
			std::wstring wsTmp(s.begin(), s.end());

			ws = wsTmp;

			return 0;
		}

		//!Default Constructors
		GtDir::GtDir(void)
		{


		};
		//copy constructor
		GtDir::GtDir(GtDir & dir)
		{
			this->m_strDirPath = dir.Get_strDirPath();
			this->m_strFileName = dir.Get_strFileName();
		};

		//!Destructor
		GtDir::~GtDir()
		{
			this->Clear();
		};

		//!Assignment Operator
		GtDir &	GtDir::operator=(GtDir & dir)
		{
			this->m_strDirPath = dir.Get_strDirPath();
			this->m_strFileName = dir.Get_strFileName();
			return *this;
		};
		//!Equal Operator
		bool GtDir::operator==(GtDir & dir) const
		{
			if((m_strDirPath == dir.Get_strDirPath()) &&
				(m_strFileName == dir.Get_strFileName()))
			{
				return true;
			}else{
				return false;
			}
			return false;
		};	
		//!Not Equal Operator
		bool GtDir::operator!=(GtDir & dir) const
		{
			if((m_strDirPath == dir.Get_strDirPath()) &&
				(m_strFileName == dir.Get_strFileName()) )
			{
				return false;
			}else{
				return true;
			}
			return true;
		};

		//!Get the full path and file name in a single string
		std::string GtDir::GetFilePathName(void)
		{
			return (m_strDirPath + "\\" + m_strFileName);
		};

		//!Clears the Directory object
		void GtDir::Clear(void)
		{
			this->m_arrFiles.clear();
			this->m_arrFolders.clear();
			this->m_arrFolders.clear();
			this->m_strDirPath.clear();
			this->m_strFileName.clear();
		};

		//!Does the directory path provided exist?
		bool GtDir::DirExists(const std::string & name)
		{
			DWORD ftyp = GetFileAttributesA(name.c_str());
			if (ftyp == INVALID_FILE_ATTRIBUTES)
				return false;  //something is wrong with your path!

			if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
				return true;   // this is a directory!

			return false;    // this is not a directory!

		};
		//!Does the current directory path exist?
		bool GtDir::DirExists(void)
		{
			return DirExists(m_strDirPath);
		};
		//!Does the provided file name exist?
		bool GtDir::FileExists(const std::string & name)
		{

			std::ifstream dllfile(name.c_str(), std::ios::binary);
			if(!dllfile)
			{
				//... DLL doesn't exist...
				return false;
			}else{
				return true;
			}
		};
		//!Does the current file name exist?
		bool GtDir::FileExists(void)
		{
			return FileExists(GetFilePathName());
		};

		//!Gets the number of folders in the current location
		size_t GtDir::FileCount() const
		{
			return m_arrFiles.size();
		};
		//!Gets the list of folders in the current location
		StlStringList GtDir::FileList()
		{
			m_arrFiles.clear();
			WIN32_FIND_DATA data;
		    LARGE_INTEGER filesize;
			std::wstring path;
			std::wstring name;
			StringToWString(path,this->m_strDirPath);
			HANDLE hFile = FindFirstFile((LPCSTR)path.c_str(), &data);

			if  (hFile == INVALID_HANDLE_VALUE)
				return m_arrFiles;

			while(FindNextFile(hFile, &data) != 0 || GetLastError() != ERROR_NO_MORE_FILES)
			{

				if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					//directory
				}
				else
				{
					filesize.LowPart = data.nFileSizeLow;
					filesize.HighPart = data.nFileSizeHigh;
					//mbstowcs(wchar_t* dst, const char* src, std::size_t len)
					std::string strName = data.cFileName;

					std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
					//std::string narrow = converter.to_bytes(wide_utf16_source_string);
					std::wstring wide = converter.from_bytes(strName);

					this->m_arrFiles.push_back(strName);
				}	
			}
			return m_arrFiles;

			FindClose(hFile);

		};
		//!Gets the file name in the list at pos
		std::string GtDir::AtFile(size_t index)
		{
			if((index >= 0) && (index < m_arrFiles.size()))
			{
				return m_arrFiles.at(index);
			}
			std::string strNull;
			return strNull;

		};
		//!Clears the file list
		void GtDir::ClearFileList(void)
		{
			m_arrFiles.clear();
		};

		//!Gets the number of files in the current location
		size_t GtDir::FolderCount() const
		{
			return m_arrFolders.size();
		};
		//!Gets the list of files in the current location
		StlStringList GtDir::FolderList()
		{
			m_arrFolders.clear();
			WIN32_FIND_DATA data;
			std::wstring path;
			std::wstring name;
			StringToWString(path,this->m_strDirPath);
			HANDLE hFile = FindFirstFile((LPCSTR)path.c_str(), &data);

			if  (hFile == INVALID_HANDLE_VALUE)
				return m_arrFolders;

			while(FindNextFile(hFile, &data) != 0 || GetLastError() != ERROR_NO_MORE_FILES)
			{

				if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					std::string name = data.cFileName;
					this->m_arrFolders.push_back(name);
				}

				std::string str = data.cFileName;
				this->m_arrFolders.push_back(str);
			}
			
			FindClose(hFile);
			return m_arrFolders;
		};
		//!Gets the folder name in the list at pos
		std::string GtDir::AtFolder(size_t index)
		{
			if((index >= 0) && (index < m_arrFolders.size()))
			{
				return m_arrFolders.at(index);
			}
			std::string strNull;
			return strNull;
		};
		//!Clears the folder list
		void GtDir::ClearFolderList(void)
		{
			m_arrFolders.clear();
		};

		//COMMANDS for DOS like interface
		//!Change directory
		bool GtDir::cd(const std::string & dirName)
		{
			m_strDirPath = dirName;
			return false;
		};
		//!Change directory up one level
		bool GtDir::cdUp()
		{

			return false;
		};
		//!Make a directory
		bool GtDir::mkdir(const std::string & dirName) const
		{
			std::wstring strDir;
			StringToWString(strDir,dirName);
			CreateDirectory((LPCSTR)strDir.c_str(),NULL);
			return false;
		};
		//!Remove a directory
		bool GtDir::rmdir(const std::string & dirName) const
		{
			std::wstring strDir;
			StringToWString(strDir,dirName);
			RemoveDirectory((LPCSTR)strDir.c_str());
			return false;
		};	
		//!Remove a file
		bool GtDir::rmfile(const std::string & fileName)
		{
			std::wstring strName;
			StringToWString(strName,fileName);
			DeleteFile((LPCSTR)strName.c_str());
			return false;
		};
		//!Rename a file
		bool GtDir::rename(const std::string & oldName,const std::string & newName)
		{
			std::wstring strOld,strNew;
			StringToWString(strOld,oldName);
			StringToWString(strNew,newName);
			MoveFile((LPCSTR)strOld.c_str(), (LPCSTR)strNew.c_str());
			return false;
		};

	};//end namespace GtCore

};//end namespace GT