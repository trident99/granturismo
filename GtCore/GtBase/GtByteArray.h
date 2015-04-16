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

#ifndef GT_BYTEARRAY_H
#define GT_BYTEARRAY_H

#include <modHtlGlobal.h>
#include <modHtlString.h>
using namespace HTL;

#include <string>
using namespace std;

namespace GT{

	namespace GtCore
	{
		//!GtByteArray is a character container class for holding strings
		/*!
		GtByteArray is a character container class for holding strings. 
		It is based off of the QT and STL string classes.  The goal of this class is to provide the 
		basic container manipulation.  All string Algorithms are held as functions external to the class
		definition to keep the code footprint size down.  The string Algorithms are in GtByteArrayAlgorithms.h.
		*/
#define CHR_NULL '\0'


		class HTL_DLLAPI GtByteArray{


		public:
			//!HTL String Constructors
			GtByteArray(void);
			GtByteArray(const char *unicode, int size);
			GtByteArray(char c);
			GtByteArray(const std::string & strInput);
			GtByteArray(const GtByteArray & strInput);
			//!HTL String Destructors
			~GtByteArray();

			//HTL String Operator Overloads
			//!Assignment Operators
			GtByteArray & operator=(char c);
			GtByteArray & operator=(const char * ptrRHS);
			GtByteArray & operator=(const unsigned char * ptrRHS);
			GtByteArray & operator=(const std::string & ptrRHS);
			GtByteArray & operator=(const GtByteArray & ptrRHS);
			//!Compound Add Assignment Operator // A += B
			GtByteArray & operator += (char c); 
			GtByteArray & operator += (const char * ptrRHS); 
			GtByteArray & operator += (const std::string & ptrRHS); 
			GtByteArray & operator += (const GtByteArray & ptrRHS);
			//!Streaming Assignment Operators
			GtByteArray & operator <<= (char c);
			GtByteArray & operator <<= (char * ptrRHS);
			GtByteArray & operator <<= (const std::string & ptrRHS);
			GtByteArray & operator <<= (const GtByteArray & ptrRHS);

			GtByteArray & operator << (char c);
			GtByteArray & operator << (const char * ptrRHS);
			GtByteArray & operator << (const std::string & ptrRHS);
			GtByteArray & operator << (const GtByteArray & ptrRHS);


			//!Boolean Logic Operators (GtByteArray only)
			//std::string operators are for conversion into native format only
			bool operator == (const char* ptrRHS) const;
			bool operator != (const char* ptrRHS) const;
			bool operator < (const char* ptrRHS) const;
			bool operator > (const char* ptrRHS) const;
			bool operator <= (const char* ptrRHS) const;
			bool operator >= (const char* ptrRHS) const;

			bool operator == (const GtByteArray & ptrRHS) const;
			bool operator != (const GtByteArray & ptrRHS) const;
			bool operator < (const GtByteArray & ptrRHS) const;
			bool operator > (const GtByteArray & ptrRHS) const;
			bool operator <= (const GtByteArray & ptrRHS) const;
			bool operator >= (const GtByteArray & ptrRHS) const;

			//!HTL String Resizing Functions
			//!This reserves the memory for a string of intSize length, this calls the clean slate memalloc
			void reserve(size_t intSize);
			//!This resizes the memory for a string of intSize length, this calls the clean slate memReAlloc
			void resize(size_t intSize);
			//!This performs a left trim operation on the string 
			void leftTrim(size_t intNumChar);
			//!This performs a right trim operation on the string
			void rightTrim(size_t intNumChar);
			//!This performs a right trim operation on the string
			void truncate(int pos){resize(pos);};



			//!This performs a fill operation on the string of character c
			void fill(char c);
			//!This clears the current string contents and frees the memory
			void clear();
			//!ReAllocates the memory of the string and its contents
			void realloc();


			//!HTL String Append Functions
			GtByteArray & append(char c);
			GtByteArray & append(const char* ptrRHS);
			GtByteArray & append(const std::string & ptrRHS);
			GtByteArray & append(const GtByteArray & ptrRHS);
			//!HTL String Prepend Functions
			GtByteArray & prepend(char c);
			GtByteArray & prepend(const char* ptrRHS);
			GtByteArray & prepend(const std::string & ptrRHS);
			GtByteArray & prepend(const GtByteArray & ptrRHS);
			//!HTL Container Accessors
			const char & at(size_t i) const;
			char & at(size_t i);

			const char & operator[](size_t i) const;
			char & operator[](size_t i);

			//!Sub String Accessors
			void subString(GtByteArray & ptrString, size_t intStart, size_t intLength);

			//!HTL Container Analyzers
			//!Returns the size of the string
			size_t size(void) const;
			//!Returns the size of the string
			size_t count(void) const;
			//!Returns the size of the string forces a full recount
			void recount(void);
			//!Returns true if the string is empty
			bool isEmpty(void) const;
			//!Returns the current capacity of the string allocated memory
			size_t capacity(void) const;

			//!HTL String direct character array accessors
			inline const char *unicode(void) const
			{
				//return the pointer to the first character
				return &m_ptrData->m_arrChar[0];
			};
			//!HTL String direct character array accessors
			inline const char *charString(void) const
			{
				//return the pointer to the first character
				return &m_ptrData->m_arrChar[0];
			};
			//!HTL String direct character array accessors
			inline const ChrNode *data(void) 
			{
				return m_ptrData;
			};


		private:

			//!THIS IS THE POINTER TO THE ACTUAL CHARACTER DATA THAT IS BEING MANAGED
			ChrNode * m_ptrData;
			//!shared null character
			ChrNode m_objSharedNull;
			//!null character constant
			char m_chrNull;
			//!This grows the string by int characters
			void grow(size_t intSize);
			//!This shrinks the string by int characters, or completely if intSize > intCurrentSize
			void shrink(size_t intSize);


		};//end GtByteArray Class Definition

	};//end GtCore namespace

};//end GT namespace

#endif