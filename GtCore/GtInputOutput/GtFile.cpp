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

#include ".\GtFile.h"

namespace GT
{
	namespace GtCore
	{

		//!Default Constructor
		GtFile::GtFile()
		{
			//do nothing
		};

		//!Destructor
		GtFile::~GtFile()
		{

			m_strFileName.clear();

			if(m_objFile.is_open())
			{
				m_objFile.close();
			};

			m_objBuffer.clear();
		};

		//check to see if the file is open
		bool GtFile::IsOpen() const
		{
			return m_objFile.is_open();

		};
		//check to see if the file is readable
		bool GtFile::IsReadable() const
		{
			return ((m_objMode == ReadOnly)||(m_objMode == ReadWrite));
		};
		//!check to see if the file is writeable
		bool GtFile::IsWritable() const
		{
			return ((m_objMode == WriteOnly)||(m_objMode == ReadWrite));
		};
		//open the file
		bool GtFile::Open(void)
		{
			m_objFile.open(this->m_strFileName.c_str());
			return m_objFile.is_open();
		};
		//!close the file
		void GtFile::Close(void)
		{
			m_objFile.close();
		};

		//!get the file cursor position
		GtInt64 GtFile::Pos()
		{
			return (GtInt64)m_objFile.tellg();
		};
		//!get the size of the file
		GtInt64 GtFile::Size()
		{
			std::ifstream in(m_strFileName.c_str(), std::ifstream::in | std::ifstream::binary);
			in.seekg(0, std::ifstream::end);
			return in.tellg(); 
		};
		//!move the cursor to the desired location
		bool GtFile::Seek(GtInt64 pos)
		{
			m_objFile.seekg((streamoff)pos);
			m_objFile.seekp((streamoff)pos);
			return true;
		};
		//!is the cursor at the end of file
		bool GtFile::AtEnd()
		{
			return m_objFile.eof();
		};
		//!reset the cursor position to the beginning of the file
		bool GtFile::Reset()
		{
			m_objFile.seekg(0);
			m_objFile.seekp(0);
			return true;
		};

		//!READ methods
		GtInt64 GtFile::Read(char *data, GtInt64 maxlen)
		{
			m_objFile.read(data,(streamsize)maxlen);
			return m_objFile.tellg();
		};

		GtByteArray & GtFile::Read(GtInt64 maxlen)
		{
			m_objBuffer.clear();
			if(maxlen > 2048)//practical limit
			{
				//requested buffer too large
				return m_objBuffer;
			}
			char chrLineBuf[2048];
			memset(chrLineBuf,'\0',2048);
			m_objFile.read((char*)chrLineBuf,(streamoff)maxlen);
			m_objBuffer.append(&chrLineBuf[0]);
			return m_objBuffer;
		};
		GtByteArray & GtFile::ReadAll()
		{
			m_objBuffer.clear();
			char chrLineBuf[256];
			memset(chrLineBuf,'\0',256);
			m_objFile.seekg(0);
			while(!m_objFile.eof())
			{
				m_objFile.read((char*)chrLineBuf,256);
				m_objBuffer.append(&chrLineBuf[0]);
			}
			return m_objBuffer;
		};
		GtInt64 GtFile::ReadLine(char *data, GtInt64 maxlen)
		{
			m_objFile.getline(data,(streamsize)maxlen);
			return m_objFile.tellg();

		};
		GtByteArray GtFile::ReadLine(GtInt64 maxlen)
		{
			m_objBuffer.clear();
			if(maxlen > 2048)//practical limit
			{
				//requested buffer too large
				return m_objBuffer;
			}

			char chrLineBuf[2048];
			m_objFile.getline((char*)chrLineBuf,(streamsize)maxlen);
			m_objBuffer.append(&chrLineBuf[0]);
			return m_objBuffer;
		};

		//!WRITE methods
		GtInt64 GtFile::Write(const char *data, GtInt64 len)
		{
			m_objFile.write(data,(streamsize)len);
			return 1;
		};
		GtInt64 GtFile::Write(const char *data)
		{
			size_t intLen = strlen(data);
			m_objFile.write(data,(streamsize)intLen);
			return 1;
		};
		GtInt64 GtFile::Write(const GtByteArray &data)
		{

			m_objFile.write(data.charString(),(streamsize)data.size());
			return 1;
		};

		//!PEEK methods
		GtInt64 GtFile::Peek(char *data, GtInt64 maxlen)
		{
			std::ifstream in(m_strFileName.c_str());
			in.seekg(m_objFile.tellg());
			in.read(data,(streamsize)maxlen);
			return 0;
		};
		GtByteArray GtFile::Peek(GtInt64 maxlen)
		{
			m_objBuffer.clear();
			char chrBuf[2048];
			memset(chrBuf,'\0',2048);
			if(maxlen > 2048)//practical limit
				return m_objBuffer;
			std::ifstream in(m_strFileName.c_str());
			in.seekg(m_objFile.tellg());
			in.read(chrBuf,(streamsize)maxlen);
			m_objBuffer.append(&chrBuf[0]);
			return m_objBuffer;
		};

		//!Sleep in milliseconds
		bool GtFile::Wait(int msecs)
		{
			Sleep(msecs);
			return true;
		};

	};//end namespace GtCore

};//end namespace GT