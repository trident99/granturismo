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


#ifndef GT_DIR_H
#define GT_DIR_H

#include "..\GtCoreLibRefs.h"
#include "..\GtCoreEnums.h"
#include <modHtlString.h>
#include <modHtlContainer.h>

using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		typedef Htl1DList<HtlString,HTL_STRING> HtlStringList;
		typedef std::vector<std::string> StlStringList;
		typedef std::vector<std::wstring> StlWStringList;

		/* WINDOWS STRINGS
		LPSTR = char*
		LPCSTR = const char*
		LPWSTR = wchar_t*
		LPCWSTR = const wchar_t*
		LPTSTR = char* or wchar_t* depending on _UNICODE
		LPCTSTR = const char* or const wchar_t* depending on _UNICODE
		*/



		class HTL_DLLAPI GtDir
		{
		public:
			//!Default Constructors
			GtDir(void);
			//copy constructor
			GtDir(GtDir & dir);

			//!Destructor
			~GtDir();

			//!Assignment Operator
			GtDir &	operator=(GtDir & dir);
			//!Equal Operator
			bool operator==(GtDir & dir) const;	
			//!Not Equal Operator
			bool operator!=(GtDir & dir) const;

			//!The full file path without the file name
			HTLMEMVAR_BYVAL_STYLE1(public, std::string, strDirPath);
			//!The 
			HTLMEMVAR_BYVAL_STYLE1(public, std::string, strFileName);
		
		public:
			//!Get the full path and file name in a single string
			std::string GetFilePathName(void);
			//Clears the Directory object
			void Clear(void);
		

			//!Does the directory path provided exist?
			bool DirExists(const std::string & name);
			//!Does the current directory path exist?
			bool DirExists(void);
			//!Does the provided file name exist?
			bool FileExists(const std::string & name);
			//!Does the current file name exist?
			bool FileExists(void);

			//!Gets the number of folders in the current location
			size_t FileCount() const;
			//!Gets the list of folders in the current location
			StlStringList FileList();
			//!Gets the file name in the list at pos
			std::string AtFile(size_t index);
			//!Clears the file list
			void ClearFileList(void);

			//!Gets the number of files in the current location
			size_t FolderCount() const;
			//!Gets the list of files in the current location
			StlStringList FolderList();
			//!Gets the folder name in the list at pos
			std::string AtFolder(size_t index);
			//!Clears the folder list
			void ClearFolderList(void);

			//COMMANDS for DOS like interface
			//!Change directory
			bool cd(const std::string & dirName);
			//!Change directory up one level
			bool cdUp();
			//!Make a directory
			bool mkdir(const std::string & dirName) const;
			//!Remove a directory
			bool rmdir(const std::string & dirName) const;	
			//!Remove a file
			bool rmfile(const std::string & fileName);
			//!Rename a file
			bool rename(const std::string & oldName,const std::string & newName);

		protected:
			//!Gets the list of folders in the current location
			StlStringList m_arrFiles;
			//!Gets the list of files in the current location
			StlStringList m_arrFolders;
			//!The list of file extension filters
			StlStringList m_arrFilters;

		};//end GtFile

	};//end namespace GtCore

};//end namespace GT

#endif//GT_IODEVICE_H