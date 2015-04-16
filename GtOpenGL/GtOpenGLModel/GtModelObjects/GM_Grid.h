/*
**	This file is part of the TridentCAD
**	This software was merged and developed by:
**	
**  Anthony Daniels
**
**  TridentCAD is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to TridentCAD.
**
**  TridentCAD is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with TridentCAD.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef GM_GRID_H
#define GM_GRID_H
#include "..\GtCadObject.h"

namespace GT{

	namespace GtOpenGL
	{

		class HTL_DLLAPI GM_Grid : public GtCadObject
		{

		public:
			GM_Grid();
			~GM_Grid();

			void Set_objPlane(GtPlaneType objPlane);
			GtPlaneType Get_objPlane(void) const;

			//Set and Get for the custom display plane
			void Set_objCustomPlane(GtPlane objPlane);
			GtPlane Get_objCustomPlane(void) const;

			//Set and Get for the dblSize 
			void Set_dblSize(double dblSize);
			double Get_dblSize(void) const;

			//Set and Get for the object render override 
			void Set_dblDelta(double dblDelta);
			double Get_dblDelta(void) const;

			//public slots:
			//render the model item in OpenGL
			virtual void RenderModelItem(const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode);
			virtual void RenderOverlay(const GtViewpoint & ptrCurrViewPoint);
		private:


			GtPlaneType m_objPlane;
			GtPlane m_objCustomPlane;
			double m_dblSize;
			double m_dblDelta;
			//draws the grid with a specific orientation
			void RenderGrid(GtPoint3DF objOrigin, GtPoint3DF objNormal, GtPoint3DF objUpDir);

		};//end class

	};//end namespace GtOpenGL

};//end namespace GT
#endif