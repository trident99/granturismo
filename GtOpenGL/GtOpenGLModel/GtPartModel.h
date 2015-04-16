/*
**	This file is part of the GT OpenGL Library.
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

#ifndef GT_PARTMODEL_H
#define GT_PARTMODEL_H

using namespace HTL;

#include "..\GtOpenGLStructs.h"

namespace GT
{
	namespace GtOpenGL
	{

		class GtCadObject;
		class GtCadLayer;

		class HTL_DLLAPI GtPartModel :  public GtObject
		{

		public:
			GtPartModel();
			~GtPartModel();

			//CAD OBJECT RELATED FUNCTIONS/////////////////////////
			GtCadObject* AtModelItem(int intIndex);
			size_t CountModelItems(void);

			//Add a Model Item to the scene
			int AddModelItem(GtCadObject* ptrNewItem);
			//Delete a Model Item from a Scene
			int DeleteModelItem(GtCadObject* ptrItem);
			int DeleteModelItem(int intIndex);
			int DeleteModelItem(HtlGUID128 objGUID);
			int DeleteAllModelItems(void);
			//Get a Model Item from a Scene
			GtCadObject* GetModelItem(int intIndex);
			GtCadObject* GetModelItem(HtlGUID128 objGUID);
			//
			int HideModelItem(int intIndex);
			int HideModelItem(HtlGUID128 objGUID);
			int HideAllModelItems(void);

			int ShowModelItem(int intIndex);
			int ShowModelItem(HtlGUID128 objGUID);
			int ShowAllModelItems(void);

			//Scene Selection
			int SelectHitTest(GtPoint3DF objOrigin, GtPoint3DF objDirection, size_t itemIndex, GtHitRecord & objHitFound);
			int SelectHitTest(GtPoint3DF objOrigin, GtPoint3DF objDirection, std::vector<GtCadObject*> & arrPtrRetHitList);
			int SelectModelItem(GtCadObject* ptrSelItem, bool blnAppend);
			int SelectModelItem(int intIndex, bool blnAppend);
			int SelectModelItem(HtlGUID128 objGUID, bool blnAppend);
			std::vector<GtCadObject*> GetSelectedModelItems(void);
			int ClearSelection(void);

			//get the bounding box of the scene
			GtAABox GetSceneBoundingBox(bool blnIncludeGrids);

			//CAD LAYER RELATED FUNCTIONS///////////////////////////////
			GtCadLayer* AtLayer(int intIndex);
			size_t CountLayers(void);

			//Add a Model Layer to the scene
			int AddLayer(GtCadLayer* ptrNewItem);
			//Delete a Model Layer from a Scene
			int DeleteLayer(GtCadLayer* ptrItem);
			int DeleteLayer(int intIndex);
			int DeleteLayer(HtlGUID128 objGUID);
			int DeleteAllLayers(void);
			//Get a Model Layer from a Scene
			GtCadLayer* GetLayer(int intIndex);
			GtCadLayer* GetLayer(HtlGUID128 objGUID);

			//public slots:
			int RenderScene(GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode);
			int RenderOverlay(GtViewpoint & ptrCurrViewPoint, GtPainter* painter = NULL);
			void UpdateScene(void);

			//signals:
			//void SceneModified(void);

		private:
			//!The collection of Model Items that are currently in the model (both visible and hidden)
			Htl1DList<GtCadLayer*,HTL_BASE_PTR> m_arrPtrCadLayers;
			//!The collection of Model Items that are currently in the model (both visible and hidden)
			Htl1DList<GtCadObject*,HTL_BASE_PTR> m_arrPtrCadObjects;
			//!The List of Model Items that returned positive on the last hit test (this is a temporary vector)
			std::vector<GtCadObject*> m_arrPtrHitItems;
			//!The List of Model Items that are currently selected
			std::vector<GtCadObject*> m_arrPtrSelectedItems;
			//private boolean flag for locking rendering during large numbers of changes 
			bool m_blnRenderLocked;
			//!boolean field for scene modified
			bool m_blnSceneModified;
			//!Current Scene Bounding Box
			GtAABox m_objSceneBoundingBox;

		};//end class definition

	};//end namespace GtOpenGL

};//end namespace GT
#endif // GT_PARTMODEL_H
