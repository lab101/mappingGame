#include "npFbxMesh.h"

	
npFbxMesh::npFbxMesh(void)
{
	reflection=0.01;
	specular =3;
	specularVal=0.1;
}


npFbxMesh::~npFbxMesh(void)
{
}

void npFbxMesh::setup()
{/*
	int numVertices =300;
	numIndices =numVertices ; 
	 lVertices  =new float[9*numVertices];
	



	//unsigned int * lIndices =new unsigned int [numVertices];
	int count =0;
	float  sPosX =0;
	float  sPosY =0;
	float  sPosZ =0;
	for (unsigned int i =0; i< numVertices ;i++)
	{
		int vPos = i*9;
		

	
		lVertices[vPos] =sPosX +((float)rand()/RAND_MAX -0.5) *10;
		lVertices[vPos+1] =sPosY +((float)rand()/RAND_MAX -0.5)*10 ;
		lVertices[vPos+2] =sPosZ +((float)rand()/RAND_MAX -0.5) *10;
		lVertices[vPos+3]  =1;
		
				//	cout<< i<<" " <<  lVertices [ vPos+0]<<" "<<  lVertices [ vPos+1]<<" " <<  lVertices [ vPos+2]<<std::endl   ;
		lVertices[vPos+4]  =100;
		lVertices[vPos+5]  =100;
		lVertices[vPos+6]  =100;
		
		lVertices[vPos+7] =100;
		lVertices[vPos+8]  =100;
		
		lIndices[i] =i;
	 count ++;
	 if (count ==3)
	 {
	 sPosX =((float)rand()/RAND_MAX -0.5) *100;
	 sPosY =((float)rand()/RAND_MAX -0.5) *100;
	 sPosZ  =((float)rand()/RAND_MAX -0.5) *100;
	 count =0;
	 }
	
	}


	glGenBuffers(NUM_VBO, vbos);
	
    // Save vertex attributes into GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 9 * sizeof(float), lVertices, GL_STATIC_DRAW);
    


   glBindBuffer(GL_ARRAY_BUFFER, 0);
    
 
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[INDEX]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numVertices * sizeof(unsigned int), lIndices, GL_STATIC_DRAW);
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	  */
}











void npFbxMesh::setFBXMesh( FbxMesh * pMesh)
{
	
	//pMesh->GetLayer(0)->GetTextures(
    const int TRIANGLE_VERTEX_COUNT = 3;
    const int VERTEX_STRIDE = 4;
    const int NORMAL_STRIDE = 3;
    const int UV_STRIDE = 2;

    if (!pMesh->GetNode())return ;

    const int lPolygonCount = pMesh->GetPolygonCount();
	if (name.compare("mainBody_gloss")==0)
	{
	reflection=0.6;
	specular =6;
	specularVal=0.7;
	
	}	if (name.compare("yellow")==0)
	{
	reflection=0.15;
	specular =10;
	specularVal=0.5;
	
	}if (name.compare("hull1")==0)
	{
	reflection=0.1;
	specular =16;
	specularVal=0.2;
	
	}
	
	std::cout <<"polygions "<<name<<" :" <<lPolygonCount<<std::endl;
	/*if (m->id ==8)m->reflection =0.05;// allgrey
					if (m->id ==5)m->reflection =0.0;//platform
					if (m->id ==3)m->reflection =0.05;//yellow;
					if (m->id ==4)m->reflection =0.2;*/




    FbxLayerElementArrayTemplate<int>* lMaterialIndice = NULL;
    FbxGeometryElement::EMappingMode lMaterialMappingMode = FbxGeometryElement::eNone;
   
	
	if (pMesh->GetElementMaterial())
    {
        lMaterialIndice = &pMesh->GetElementMaterial()->GetIndexArray();
        lMaterialMappingMode = pMesh->GetElementMaterial()->GetMappingMode();
        if (lMaterialIndice && lMaterialMappingMode == FbxGeometryElement::eByPolygon)
        {
            FBX_ASSERT(lMaterialIndice->GetCount() == lPolygonCount);
            if (lMaterialIndice->GetCount() == lPolygonCount)
            {
                // Count the faces of each material
                for (int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; ++lPolygonIndex)
                {
                    const int lMaterialIndex = lMaterialIndice->GetAt(lPolygonIndex);
                    if (mSubMeshes.GetCount() < lMaterialIndex + 1)
                    {
                        mSubMeshes.Resize(lMaterialIndex + 1);
                    }
                    if (mSubMeshes[lMaterialIndex] == NULL)
                    {
                        mSubMeshes[lMaterialIndex] = new SubMesh;
                    }
                    mSubMeshes[lMaterialIndex]->TriangleCount += 1;
                }

                // Record the offset (how many vertex)
                const int lMaterialCount = mSubMeshes.GetCount();
                int lOffset = 0;
                for (int lIndex = 0; lIndex < lMaterialCount; ++lIndex)
                {
                    mSubMeshes[lIndex]->IndexOffset = lOffset;
                    lOffset += mSubMeshes[lIndex]->TriangleCount * 3;
                    // This will be used as counter in the following procedures, reset to zero
                    mSubMeshes[lIndex]->TriangleCount = 0;
                }
                FBX_ASSERT(lOffset == lPolygonCount * 3);
            }
        }
    }

    // All faces will use the same material.
    if (mSubMeshes.GetCount() == 0)
    {
        mSubMeshes.Resize(1);
        mSubMeshes[0] = new SubMesh();
    }
	

    // Congregate all the data of a mesh to be cached in VBOs.
    // If normal or UV is by polygon vertex, record all vertex attributes by polygon vertex.
   bool  mHasNormal = pMesh->GetElementNormalCount() > 0;
   bool mHasUV = pMesh->GetElementUVCount() > 0;

   if (!mHasNormal ||!mHasUV )
   {
	cout << "mising normals &| uv"<<endl;
	//return;
   }

    bool mAllByControlPoint =true;

    FbxGeometryElement::EMappingMode lNormalMappingMode = FbxGeometryElement::eNone;
    FbxGeometryElement::EMappingMode lUVMappingMode = FbxGeometryElement::eNone;
    if (mHasNormal)
    {
        lNormalMappingMode = pMesh->GetElementNormal(0)->GetMappingMode();
        if (lNormalMappingMode == FbxGeometryElement::eNone)
        {
            mHasNormal = false;
        }
        if (mHasNormal && lNormalMappingMode != FbxGeometryElement::eByControlPoint)
        {
            mAllByControlPoint = false;
        }
    }
    if (mHasUV)
    {
        lUVMappingMode = pMesh->GetElementUV(0)->GetMappingMode();
        if (lUVMappingMode == FbxGeometryElement::eNone)
        {
            mHasUV = false;
        }
        if (mHasUV && lUVMappingMode != FbxGeometryElement::eByControlPoint)
        {
            mAllByControlPoint = false;
        }
    }

    // Allocate the array memory, by control point or by polygon vertex.
    int lPolygonVertexCount = pMesh->GetControlPointsCount();
    if (!mAllByControlPoint)
    {
        lPolygonVertexCount = lPolygonCount * TRIANGLE_VERTEX_COUNT;
    }
    float * lVertices = new float[lPolygonVertexCount * VERTEX_STRIDE];
    unsigned int * lIndices = new unsigned int[lPolygonCount * TRIANGLE_VERTEX_COUNT];
    float * lNormals = NULL;
    if (mHasNormal)
    {
        lNormals = new float[lPolygonVertexCount * NORMAL_STRIDE];
    }
    float * lUVs = NULL;
    FbxStringList lUVNames;
    pMesh->GetUVSetNames(lUVNames);
    const char * lUVName = NULL;
    if (mHasUV && lUVNames.GetCount())
    {
        lUVs = new float[lPolygonVertexCount * UV_STRIDE];
        lUVName = lUVNames[0];
    }

    // Populate the array with vertex attribute, if by control point.
    const FbxVector4 * lControlPoints = pMesh->GetControlPoints();
    FbxVector4 lCurrentVertex;
    FbxVector4 lCurrentNormal;
    FbxVector2 lCurrentUV;


		int numVertices =lPolygonVertexCount*3;
	numIndices =lPolygonCount * TRIANGLE_VERTEX_COUNT ; 
	float * vertices  =new float[9*numVertices];

	  unsigned int * indices = new unsigned int[lPolygonCount * TRIANGLE_VERTEX_COUNT];



    if (mAllByControlPoint)
    {
		cout << "mAllByControlPoint??? npFbxMesh \n";
        const FbxGeometryElementNormal * lNormalElement = NULL;
        const FbxGeometryElementUV * lUVElement = NULL;
        if (mHasNormal)
        {
            lNormalElement = pMesh->GetElementNormal(0);
        }
        if (mHasUV)
        {
            lUVElement = pMesh->GetElementUV(0);
        }
        for (int lIndex = 0; lIndex < lPolygonVertexCount; ++lIndex)
        {
      

			int vCount = lIndex *9;

            lCurrentVertex = lControlPoints[lIndex];

			ofVec4f rootPos;
			rootPos.set(static_cast<float>(lCurrentVertex[0]),static_cast<float>(lCurrentVertex[1]),static_cast<float>(lCurrentVertex[2]),1);
			ofVec4f tarPos;
			tarPos =objectMatrix.preMult( rootPos);
			vertices [ vCount]= tarPos.x;
            vertices [ vCount+1] =  tarPos.y;
            vertices [ vCount+2] = tarPos.z;

           /* vertices [ vCount]= static_cast<float>(lCurrentVertex[0]);
            vertices [ vCount+1] = static_cast<float>(lCurrentVertex[1]);
            vertices [ vCount+2] = static_cast<float>(lCurrentVertex[2]);*/
            vertices [ vCount+3] = 1;
			
       
            if (mHasNormal)
            {
                int lNormalIndex = lIndex;
                if (lNormalElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
                {
                    lNormalIndex = lNormalElement->GetIndexArray().GetAt(lIndex);
                }
                lCurrentNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
               vertices [ vCount+4] = static_cast<float>(lCurrentNormal[0]);
               vertices [ vCount+5]= static_cast<float>(lCurrentNormal[1]);
                vertices [ vCount+6]= static_cast<float>(lCurrentNormal[2]);
            }

            if (mHasUV)
            {
                int lUVIndex = lIndex;
                if (lUVElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
                {
                    lUVIndex = lUVElement->GetIndexArray().GetAt(lIndex);
                }
                lCurrentUV = lUVElement->GetDirectArray().GetAt(lUVIndex);
                vertices [ vCount+7] = static_cast<float>(lCurrentUV[0]);
                vertices [ vCount+8] =1.0- static_cast<float>(lCurrentUV[1]);
            }
        }

    }



    int lVertexCount = 0;
    for (int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; ++lPolygonIndex)
    {
     
      int lMaterialIndex = 0;
        if (lMaterialIndice && lMaterialMappingMode == FbxGeometryElement::eByPolygon)
        {
            lMaterialIndex = lMaterialIndice->GetAt(lPolygonIndex);
        }

       
        const int lIndexOffset = mSubMeshes[lMaterialIndex]->IndexOffset +   mSubMeshes[lMaterialIndex]->TriangleCount * 3;
        for (int lVerticeIndex = 0; lVerticeIndex < TRIANGLE_VERTEX_COUNT; ++lVerticeIndex)
        {
            const int lControlPointIndex = pMesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex);

            if (mAllByControlPoint)
            {
		
               indices[lIndexOffset + lVerticeIndex] = static_cast<unsigned int>(lControlPointIndex);
				
            }
      
            else
            {
				int vCount = lVertexCount*9;
				
               indices[lIndexOffset + lVerticeIndex] = static_cast<unsigned int>(lVertexCount);
			
                lCurrentVertex = lControlPoints[lControlPointIndex];
             
				ofVec4f rootPos;
			rootPos.set(static_cast<float>(lCurrentVertex[0]),static_cast<float>(lCurrentVertex[1]),static_cast<float>(lCurrentVertex[2]),1);
			ofVec4f tarPos;
			tarPos =objectMatrix.preMult( rootPos);
			vertices [ vCount]= tarPos.x;
            vertices [ vCount+1] =  tarPos.y;
            vertices [ vCount+2] = tarPos.z;

				/*vertices [ vCount]   = static_cast<float>(lCurrentVertex[0]);
				vertices [ vCount+1]   = static_cast<float>(lCurrentVertex[1]);
				vertices [ vCount+2]   = static_cast<float>(lCurrentVertex[2]);*/
				vertices [ vCount+3]   =1;
			
                if (mHasNormal)
                {
                    pMesh->GetPolygonVertexNormal(lPolygonIndex, lVerticeIndex, lCurrentNormal);

					vertices [ vCount+4] = static_cast<float>(lCurrentNormal[0]);
					vertices [ vCount+5]   = static_cast<float>(lCurrentNormal[1]);
					vertices [ vCount+6]  = static_cast<float>(lCurrentNormal[2]);

				}else
				{
				
					vertices [ vCount+4] = 0;
					vertices [ vCount+5]   =0;
					vertices [ vCount+6]  = 0;
				}

                if (mHasUV)
                {
                    pMesh->GetPolygonVertexUV(lPolygonIndex, lVerticeIndex, lUVName, lCurrentUV);		
					vertices [ vCount+7]   = static_cast<float>(lCurrentUV[0]);
					vertices [ vCount+8]  =1.0- static_cast<float>(lCurrentUV[1]);
					
				}else
				{
					vertices [ vCount+7]   = 0;
					vertices [ vCount+8]  = 0;
				}
            }
            ++lVertexCount;
        }
        mSubMeshes[lMaterialIndex]->TriangleCount += 1;
    }



	



	





	glGenBuffers(NUM_VBO, vbos);
	
   
    glBindBuffer(GL_ARRAY_BUFFER, vbos[VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 9 * sizeof(float), vertices, GL_STATIC_DRAW);
    
	glBindBuffer(GL_ARRAY_BUFFER, 0);

 
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[INDEX]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	delete[] indices;
	delete[] vertices;
	delete[] lIndices;
	delete[] lVertices;
	delete[] lNormals;
	delete[] lUVs;
}



void npFbxMesh::loadTextures()
{
	/*if (textureFile.length() == 0)
	{
		string file =    "background.png" ;
	return;
	}
	int  found=textureFile.find_last_of("/\\");
 
	string file =    "realTimeTex/"+ textureFile.substr(found+1) ;
//	CornerstoneImageLoader imgLoader;
//	texture =  imgLoader.loadImage( npGetLocalPath(file));*/
	

}