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


#ifndef GT_FILE_H
#define GT_FILE_H

#include "..\GtCoreLibRefs.h"
#include "..\GtCoreEnums.h"
#include "..\GtBase\GtByteArray.h"
//#include ".\GtFileInOutStream.h"


namespace GT
{
	namespace GtCore
	{

		class HTL_DLLAPI GtFile
		{
		public:
			//!Default Constructor
			GtFile();

			//!Destructor
			~GtFile();

			//!pointer to the parent Node
			HTLMEMVAR_BYVAL_STYLE1(public, std::string, strFileName);
			//!pointer to the parent Node
			HTLMEMVAR_BYVAL_STYLE1(public, GtOpenModeFlag, objMode);
			//!pointer to the parent Node
			HTLMEMVAR_BYVAL_STYLE1(public, GtInt64, intCurrPos);

			//check to see if the file is open
			bool IsOpen() const;
			//check to see if the file is readable
			bool IsReadable() const;
			//!check to see if the file is writeable
			bool IsWritable() const;
			//open the file
			bool Open(void);
			//!close the file
			void Close(void);

			//!get the file cursor position
			GtInt64 Pos();
			//!get the size of the file
			GtInt64 Size();
			//!move the cursor to the desired location
			bool Seek(GtInt64 pos);
			//!is the cursor at the end of file
			bool AtEnd();
			//!reset the cursor position to the beginning of the file
			bool Reset();

			//!READ methods
			GtInt64 Read(char *data, GtInt64 maxlen);
			GtByteArray & Read(GtInt64 maxlen);
			GtByteArray & ReadAll();
			GtInt64 ReadLine(char *data, GtInt64 maxlen);
			GtByteArray ReadLine(GtInt64 maxlen = 0);

			//!WRITE methods
			GtInt64 Write(const char *data, GtInt64 len);
			GtInt64 Write(const char *data);
			GtInt64 Write(const GtByteArray &data);

			//!PEEK methods
			GtInt64 Peek(char *data, GtInt64 maxlen);
			GtByteArray Peek(GtInt64 maxlen);

			//!Sleep in milliseconds
			bool Wait(int msecs);

		protected:

			//!The actual character buffer array
			GtByteArray m_objBuffer;
			//Pointer to the file
			fstream m_objFile;

		};//end GtFile

	};//end namespace GtCore

};//end namespace GT

#endif//GT_FILE_H