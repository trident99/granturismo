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

#ifndef HTL_SPROCKET_H
#define HTL_SPROCKET_H

#include <modHtlBase.h>
#include <modHtlContainer.h>
#include <modHtlRandNumGen.h>

#include <modGtItemModel.h>

namespace HTL
{
	//HtlTestItem01 is a testing object for HtlBase serialization functions
	//It contains different NON container member variables
	//of base types with an enumerated type flag.
	class Sprocket : public HtlBase
	{
	public:
		//default constructor
		Sprocket(Sprocket * parent = NULL);
		//virtual destructor
		virtual ~Sprocket(void);

		Sprocket &	operator= ( Sprocket & ptrRHS );
		//!pointer to the parent Node
		HTLMEMVAR_BYREF_STYLE1(public, std::string, strName);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, bool, blnTest);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, short, shrtVar01);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, ushort, ushrtVar02);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, int, intVar03);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, uint, uintVar04);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, long, lngVar05);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, ulong, ulngVar06);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, float, sngVar07);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, double, dblVar08);
		//!Use the random number generator to populate this sprocket's data
		void GenerateData(void);
		//!Randomly Generate the Sprockets for this level
		void GenerateSprockets(int level, int levelMax);
		//!Delete all the sprockets from the sub collection
		void DeleteAllSprockets(void);

	public:
		//SERIALIZATION FUNCTIONS///////////////////////////////////////
		//Save member data to the current element node
		virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
		//Load member data from the current element node
		virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		Htl1DList<Sprocket*, HtlUnknownType> m_arrSprockets;

		void TreeLoadSprocket(GtTreeItemModel* ptrModel,GtTreeModelIndex * parent);


	protected:
		HtlUniform* GetRNGPtr(void);
		//pointer to the parent sprocket
		Sprocket* m_ptrParent;

		HtlUniform m_objRNG;

	};//end Sprocket class definition

};//end namspace Htl

#endif//HtlBASE_H


