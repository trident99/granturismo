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

#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include "..\GtOpenGLMath.h"
#include ".\GtPartModel.h"
#include ".\GtCadObject.h"
#include ".\GtCadLayer.h"
#include ".\GtModelObjects\GM_Grid.h"


namespace GT
{
	namespace GtOpenGL
	{
		GtPartModel::GtPartModel() : GtObject()

		{
			m_blnRenderLocked = false;
			m_blnSceneModified = true;
		}

		GtPartModel::~GtPartModel()
		{

		}

		//Add a Model Item to the scene
		int GtPartModel::AddModelItem(GtCadObject* ptrNewItem)
		{
			if(ptrNewItem)
			{
				this->m_arrPtrCadObjects.push_back(ptrNewItem);
				//connect(ptrNewItem,SIGNAL(ModelItemModified()),this,SLOT(UpdateScene()));
				m_blnSceneModified = true;
				return 1;

			}
			//else nothing to add
			return 0;
		};
		//Delete a Model Item from a Scene
		int GtPartModel::DeleteModelItem(GtCadObject* ptrItem)
		{
			if(ptrItem)
			{
				size_t i, numItems;
				numItems = m_arrPtrCadObjects.size();
				if(numItems <= 0){return 0;};
				for(i = 0; i < numItems; i++)
				{
					GtCadObject* ptrCurr = m_arrPtrCadObjects.at(i);
					if(ptrCurr)
					{
						if(ptrCurr == ptrItem)
						{
							//match
							delete ptrCurr;
							m_arrPtrCadObjects.erase(i);
							return 1;

						}

					}//endn pointer check

				}//end loop through model items

			}//end incoming item check
			//otherwise failed to delete
			return 0;
		};

		int GtPartModel::DeleteModelItem(int intIndex)
		{
			int intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();
			if((intIndex >= 0) && (intIndex < intUboundI))
			{
				//then a valid index to delete

				delete this->m_arrPtrCadObjects.at(intIndex);
				this->m_arrPtrCadObjects.erase(intIndex);
				m_blnSceneModified = true;
				return 1;
			}
			//otherwise invalid index
			return 0;
		};

		int GtPartModel::DeleteModelItem(HtlGUID128 objGUID)
		{
			int i, intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();

			for(i = 0; i < intUboundI;i++)
			{
				if(this->m_arrPtrCadObjects.at(i)->Get_objGUID() == objGUID)
				{//then match found
					//disconnect before deleting
					//disconnect((this->m_arrPtrCadObjects.at(i)),SIGNAL(ModelItemModified()),this,SLOT(UpdateScene()));
					delete this->m_arrPtrCadObjects.at(i);
					this->m_arrPtrCadObjects.erase(i);
					m_blnSceneModified = true;
					return 1;
				}//end if match check

			}//end for loop through model items
			//otherwise invalid index
			return 0;
		};

		int GtPartModel::DeleteAllModelItems(void)
		{
			int i, intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();

			for(i = 0; i < intUboundI;i++)
			{
				//disconnect before deleting
				//disconnect((this->m_arrPtrCadObjects.at(i)),SIGNAL(ModelItemModified()),this,SLOT(UpdateScene()));
				delete this->m_arrPtrCadObjects.at(i);
			}//end for loop through model items
			this->m_arrPtrCadObjects.clear();
			this->m_arrPtrHitItems.clear();
			this->m_arrPtrSelectedItems.clear();
			m_blnSceneModified = true;
			//otherwise invalid index
			return 1;
		};

		GtCadObject* GtPartModel::AtModelItem(int intIndex)
		{
			int intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();
			if((intIndex >= 0) && (intIndex < intUboundI))
			{//then a valid index to delete
				return this->m_arrPtrCadObjects.at(intIndex);
			}
			//otherwise invalid index
			return NULL;
		};

		size_t GtPartModel::CountModelItems(void)
		{
			return this->m_arrPtrCadObjects.size();
		};

		//Get a Model Item from a Scene
		GtCadObject* GtPartModel::GetModelItem(int intIndex)
		{
			int intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();
			if((intIndex >= 0) && (intIndex < intUboundI))
			{//then a valid index to delete
				return this->m_arrPtrCadObjects.at(intIndex);
			}
			//otherwise invalid index
			return NULL;
		};

		GtCadObject* GtPartModel::GetModelItem(HtlGUID128 objGUID)
		{
			int i, intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();

			for(i = 0; i < intUboundI;i++)
			{
				if(this->m_arrPtrCadObjects.at(i)->Get_objGUID() == objGUID)
				{//then match found
					return this->m_arrPtrCadObjects.at(i);
				}//end if match check
			}//end for loop through model items
			//otherwise invalid index
			return NULL;
		};

		//
		int GtPartModel::HideModelItem(int intIndex)
		{
			int intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();
			if((intIndex >= 0) && (intIndex < intUboundI))
			{//then a valid index to delete
				this->m_arrPtrCadObjects.at(intIndex)->Set_blnVisible(false);
				return 1;
			}
			//otherwise invalid index
			return NULL;
		};

		int GtPartModel::HideModelItem(HtlGUID128 objGUID)
		{
			int i, intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();

			for(i = 0; i < intUboundI;i++)
			{
				if(this->m_arrPtrCadObjects.at(i)->Get_objGUID() == objGUID)
				{//then match found
					this->m_arrPtrCadObjects.at(i)->Set_blnVisible(false);
				}//end if match check
			}//end for loop through model items
			//otherwise invalid index
			return NULL;
		};

		int GtPartModel::HideAllModelItems(void)
		{
			int i, intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();

			for(i = 0; i < intUboundI;i++)
			{
				this->m_arrPtrCadObjects.at(i)->Set_blnVisible(false);
			}//end for loop through model items
			//otherwise invalid index
			return 1;
		};

		int GtPartModel::ShowModelItem(int intIndex)
		{
			int intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();
			if((intIndex >= 0) && (intIndex < intUboundI))
			{//then a valid index to delete
				this->m_arrPtrCadObjects.at(intIndex)->Set_blnVisible(true);
				return 1;
			}
			//otherwise invalid index
			return NULL;
		};

		int GtPartModel::ShowModelItem(HtlGUID128 objGUID)
		{
			int i, intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();

			for(i = 0; i < intUboundI;i++)
			{
				if(this->m_arrPtrCadObjects.at(i)->Get_objGUID() == objGUID)
				{//then match found
					this->m_arrPtrCadObjects.at(i)->Set_blnVisible(true);
				}//end if match check
			}//end for loop through model items
			//otherwise invalid index
			return NULL;
		};

		int GtPartModel::ShowAllModelItems(void)
		{
			int i, intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();

			for(i = 0; i < intUboundI;i++)
			{
				this->m_arrPtrCadObjects.at(i)->Set_blnVisible(true);
			}//end for loop through model items
			//otherwise invalid index
			return 1;
		};

		int GtPartModel::SelectHitTest(GtPoint3DF objOrigin, GtPoint3DF objDirection,size_t itemIndex, GtHitRecord & objHitFound)
		{

			//get the item pointer
			GtCadObject* ptrItem = this->AtModelItem(itemIndex);
			if(ptrItem)
			{
				GtAABox objSelBox = ptrItem->GetSelectionBox();
				objHitFound = RayIntersectAABB(objOrigin,objDirection,objSelBox);
				objHitFound.m_intSelIndex = itemIndex;
				return 1;
			};
			//bad pointer
			objHitFound.m_blnHit = false;
			return 0;
		};



		//Scene selection hit ray trace test
		int GtPartModel::SelectHitTest(GtPoint3DF objOrigin, GtPoint3DF objDirection, std::vector<GtCadObject*> & arrPtrRetHitList)
		{
			return 1;
		};
		//single model item selection
		int GtPartModel::SelectModelItem(GtCadObject* ptrSelItem, bool blnAppend)
		{
			if(ptrSelItem)
			{

				if(blnAppend)
				{
					ptrSelItem->Set_blnSelected(true);
					this->m_arrPtrSelectedItems.push_back(ptrSelItem);
					return 1;
				}else{
					//clear the list and add this one
					this->ClearSelection();
					ptrSelItem->Set_blnSelected(true);
					this->m_arrPtrSelectedItems.push_back(ptrSelItem);
					return 1;
				}//end if append check

			}//end valid pointer check
			//otherwise failed to delete
			//emit SceneModified();
			return NULL;
		};
		//single model item selection
		int GtPartModel::SelectModelItem(int intIndex, bool blnAppend)
		{
			int intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();
			if((intIndex >= 0) && (intIndex < intUboundI))
			{//then a valid index to delete
				if(blnAppend)
				{
					this->m_arrPtrCadObjects.at(intIndex)->Set_blnSelected(true);
					this->m_arrPtrSelectedItems.push_back(this->m_arrPtrCadObjects.at(intIndex));
					return 1;
				}else{
					//clear the list and add this one
					this->ClearSelection();
					this->m_arrPtrCadObjects.at(intIndex)->Set_blnSelected(true);
					this->m_arrPtrSelectedItems.push_back(this->m_arrPtrCadObjects.at(intIndex));
					return 1;
				}//end if append check
			}
			//emit SceneModified();
			//otherwise invalid index
			return NULL;
		};
		//single model item selection
		int GtPartModel::SelectModelItem(HtlGUID128 objGUID, bool blnAppend)
		{
			int i, intUboundI;
			intUboundI = this->m_arrPtrCadObjects.size();

			for(i = 0; i < intUboundI;i++)
			{
				if(this->m_arrPtrCadObjects.at(i)->Get_objGUID() == objGUID)
				{//then match found
					if(blnAppend)
					{
						this->m_arrPtrCadObjects.at(i)->Set_blnSelected(true);
						this->m_arrPtrSelectedItems.push_back(this->m_arrPtrCadObjects.at(i));
						return 1;
					}else{
						//clear the list and add this one
						this->ClearSelection();
						this->m_arrPtrCadObjects.at(i)->Set_blnSelected(true);
						this->m_arrPtrSelectedItems.push_back(this->m_arrPtrCadObjects.at(i));
						return 1;
					}//end if append check
				}//end if match check
			}//end for loop through model items
			//otherwise invalid index
			//emit SceneModified();
			return NULL;
		};
		//get the vector of currently selected items
		std::vector<GtCadObject*> GtPartModel::GetSelectedModelItems(void)
		{
			return m_arrPtrSelectedItems;
		};
		//clear the model selection list
		int GtPartModel::ClearSelection(void)
		{	
			int i, intUboundI;
			this->m_arrPtrHitItems.clear();
			this->m_arrPtrSelectedItems.clear();
			intUboundI = this->m_arrPtrCadObjects.size();
			//LOCK RENDERING before clearing the selection
			this->m_blnRenderLocked = true;

			for(i = 0; i < intUboundI;i++)
			{
				this->m_arrPtrCadObjects.at(i)->Set_blnSelected(false);
			}
			//UNLOCK RENDERING
			this->m_blnRenderLocked = false;
			//trigger the scene re-render
			//emit SceneModified(); 
			return 1;
		};


		//CAD LAYER RELATED FUNCTIONS
		GtCadLayer* GtPartModel::AtLayer(int intIndex)
		{
			return NULL;
		};
		size_t GtPartModel::CountLayers(void)
		{
			return m_arrPtrCadLayers.size();	
		};

		//Add a Model Layer to the scene
		int GtPartModel::AddLayer(GtCadLayer* ptrNewItem)
		{
			return 0;	
		};
		//Delete a Model Layer from a Scene
		int GtPartModel::DeleteLayer(GtCadLayer* ptrItem)
		{
			return 0;	
		};
		int GtPartModel::DeleteLayer(int intIndex)
		{
			return 0;	
		};
		int GtPartModel::DeleteLayer(HtlGUID128 objGUID)
		{
			return 0;
		};
		int GtPartModel::DeleteAllLayers(void)
		{
			return 0;
		};
		//Get a Model Layer from a Scene
		GtCadLayer* GtPartModel::GetLayer(int intIndex)
		{
			return NULL;	
		};
		GtCadLayer* GtPartModel::GetLayer(HtlGUID128 objGUID)
		{
			return NULL;

		};



		//render the current scene model
		int GtPartModel::RenderScene(GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode)
		{
			int i, intUboundI;
			if(this->m_blnRenderLocked == false)
			{
				intUboundI = this->m_arrPtrCadObjects.size();
				for(i = 0; i < intUboundI;i++)
				{
					if(this->m_arrPtrCadObjects.at(i))
					{
						this->m_arrPtrCadObjects.at(i)->RenderItem(ptrCurrViewPoint,enumRenderMode);
					};
				};
				return 1;
			}else{
				return NULL;
			};
			return NULL;
		};
		//render the current scene model
		int GtPartModel::RenderOverlay(GtViewpoint & ptrCurrViewPoint, GtPainter* painter)
		{
			int i, intUboundI;
			if(this->m_blnRenderLocked == false)
			{
				intUboundI = this->m_arrPtrCadObjects.size();
				for(i = 0; i < intUboundI;i++)
				{
					if(this->m_arrPtrCadObjects.at(i))
					{
						this->m_arrPtrCadObjects.at(i)->RenderOverlay(ptrCurrViewPoint);
					};
				};
				return 1;
			}else{
				return NULL;
			};
			return NULL;
		};


		void GtPartModel::UpdateScene(void)
		{
			if(this->m_blnRenderLocked == false)
			{
				//emit SceneModified();
			};//end scene emmision
		};

		GtAABox GtPartModel::GetSceneBoundingBox(bool blnIncludeGrids)
		{
			bool blnBBSet = false;
			std::string strType;
			GtAABox objBoxReturn, objBoxTemp;
			GM_Grid * ptrGridTest = NULL;
			GM_Grid * ptrGridCast = NULL;
			int i, intNumItems;
			objBoxReturn.Zero();

			if(!m_blnSceneModified)
			{
				//do nothing
			}else{
				intNumItems = this->m_arrPtrCadObjects.size();
				for(i = 0; i < intNumItems;i++)
				{
					ptrGridCast = dynamic_cast<GM_Grid*>(this->m_arrPtrCadObjects.at(i));
					if( ((ptrGridCast)&&(blnIncludeGrids == false))||
						(this->m_arrPtrCadObjects.at(i)->Get_blnVisible() == false) )
					{
						//then this is a grid or object turned off and we are supposed to skip it
					}else{
						//otherwise calculate the bounding box and compare
						objBoxTemp = this->m_arrPtrCadObjects.at(i)->GetBoundingBox();

						if(blnBBSet == false)
						{//first time through
							objBoxReturn = objBoxTemp;
							blnBBSet = true;
						};

						if(objBoxTemp.m_dblXMin < objBoxReturn.m_dblXMin)
						{
							//new XMIN
							objBoxReturn.m_dblXMin = objBoxTemp.m_dblXMin;
						};
						if(objBoxTemp.m_dblYMin < objBoxReturn.m_dblYMin)
						{
							//new YMIN
							objBoxReturn.m_dblYMin = objBoxTemp.m_dblYMin;
						};
						if(objBoxTemp.m_dblZMin < objBoxReturn.m_dblZMin)
						{
							//new ZMIN
							objBoxReturn.m_dblZMin = objBoxTemp.m_dblZMin;
						};

						if(objBoxTemp.m_dblXMax > objBoxReturn.m_dblXMax)
						{
							//new XMAX
							objBoxReturn.m_dblXMax = objBoxTemp.m_dblXMax;
						};
						if(objBoxTemp.m_dblYMax > objBoxReturn.m_dblYMax)
						{
							//new YMAX
							objBoxReturn.m_dblYMax = objBoxTemp.m_dblYMax;
						};
						if(objBoxTemp.m_dblZMax > objBoxReturn.m_dblZMax)
						{
							//new ZMAX
							objBoxReturn.m_dblZMax = objBoxTemp.m_dblZMax;
						};
					};//end if grid check

				};//end for loop through items
				m_blnSceneModified = false;
			};//end scene modified check

			m_objSceneBoundingBox = objBoxReturn;
			return m_objSceneBoundingBox;
		};

	};//end namespace GtOpenGL
};//end namespace GT