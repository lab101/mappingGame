#include "npFbxLoader.h"


npFbxLoader::npFbxLoader(void)
{
}


npFbxLoader::~npFbxLoader(void)
{
}

void npFbxLoader::load(const char * fileName,int debugLoad)
{
	cout << fileName<< endl;
	  initializeSdkObjects(mSdkManager, mScene);

	   if (mSdkManager)
   {
	  
       // Create the importer.
       int lFileFormat = -1;
       mImporter = FbxImporter::Create(mSdkManager,"");
       if (!mSdkManager->GetIOPluginRegistry()->DetectReaderFileFormat(fileName, lFileFormat) )
       {
           // Unrecognizable file format. Try to fall back to FbxImporter::eFBX_BINARY
           lFileFormat = mSdkManager->GetIOPluginRegistry()->FindReaderIDByDescription( "FBX binary (*.fbx)" );;
       }
	   
       
       if(mImporter->Initialize(fileName, lFileFormat) == true)
       {
        
		     cout << "importing"<<endl;
           // Set scene status flag to ready to load.
      
			 if (mImporter->Import(mScene) == true)
			  {
            // Set the scene status flag to refresh 
            // the scene in the first timer callback.
           cout << "loading"<<endl;
            // Convert Axis System to what is used in this example, if needed
            FbxAxisSystem SceneAxisSystem = mScene->GetGlobalSettings().GetAxisSystem();
            FbxAxisSystem OurAxisSystem(FbxAxisSystem::eYAxis, FbxAxisSystem::eParityOdd, FbxAxisSystem::eRightHanded);
            if( SceneAxisSystem != OurAxisSystem )
            {
                OurAxisSystem.ConvertScene(mScene);
            }

            // Convert Unit System to what is used in this example, if needed
            FbxSystemUnit SceneSystemUnit = mScene->GetGlobalSettings().GetSystemUnit();
            if( SceneSystemUnit.GetScaleFactor() != 1.0 )
            {
               
                FbxSystemUnit::cm.ConvertScene( mScene);
            }

        
           FillCameraArray(mScene);
		   Camera::getInstance()->cameras  =cameras;
		   Camera::getInstance()->setFirst();


		   if (!debugLoad){
				cout << "triangulate"<< endl;
				//triangulateRecursive(mScene->GetRootNode());
		   }
		
			LoadCacheRecursive(mScene, mCurrentAnimLayer, fileName, false);//??
			cout << "load cache"<< endl;
      
            preparePointCacheData(mScene, mCache_Start, mCache_Stop);
			

			 }
			
       }
       else
       {
		     cout << "filenotfound"<<endl;
         
       }
   }
   else
   {
	   cout << "faild"<<endl;
 
   }

}


void npFbxLoader::initializeSdkObjects(FbxManager*& pSdkManager, FbxScene*& pScene)
{
    // The first thing to do is to create the FBX SDK manager which is the 
    // object allocator for almost all the classes in the SDK.
    pSdkManager = FbxManager::Create();
	
    if( !pSdkManager )
    {
        cout <<"Unable to create the FBX SDK manager\n";
        exit(0);
    }
	else
	{
		 cout <<"FBX SDK version %s\n\n"<< pSdkManager->GetVersion() <<endl;
	}
	
	FbxIOSettings * ios = FbxIOSettings::Create(pSdkManager, IOSROOT );

	pSdkManager->SetIOSettings(ios);

	FbxString lPath = FbxGetApplicationDirectory();

	//pSdkManager->LoadPluginsDirectory(lPath.Buffer());
	
    pScene = FbxScene::Create(pSdkManager,"");
}

void npFbxLoader::destroySdkObjects(FbxManager* pSdkManager)
{
    // Delete the FBX SDK manager. All the objects that have been allocated 
    // using the FBX SDK manager and that haven't been explicitly destroyed 
    // are automatically destroyed at the same time.
    if (pSdkManager) pSdkManager->Destroy();
    pSdkManager = NULL;
}


 void npFbxLoader::triangulateRecursive(FbxNode* pNode)
    {
        FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();

        if (lNodeAttribute)
        {
            if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh ||
                lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbs ||
                lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbsSurface ||
                lNodeAttribute->GetAttributeType() == FbxNodeAttribute::ePatch)
            {
                FbxGeometryConverter lConverter(pNode->GetFbxManager());
                lConverter.TriangulateInPlace(pNode);
            }
        }

        const int lChildCount = pNode->GetChildCount();
        for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
        {
            triangulateRecursive(pNode->GetChild(lChildIndex));
        }
    }


void npFbxLoader::preparePointCacheData(FbxScene* pScene, FbxTime &pCache_Start, FbxTime &pCache_Stop)
{
        // This function show how to cycle through scene elements in a linear way.
        const int lNodeCount = FbxGetSrcCount<FbxNode>(pScene);

        for (int lIndex=0; lIndex<lNodeCount; lIndex++)
        {
            FbxNode* lNode = FbxGetSrc<FbxNode>(pScene, lIndex);
			
            if (lNode->GetGeometry()) 
            {
				

			
                int i, lVertexCacheDeformerCount = lNode->GetGeometry()->GetDeformerCount(FbxDeformer::eVertexCache);
				

                // There should be a maximum of 1 Vertex Cache Deformer for the moment
                lVertexCacheDeformerCount = lVertexCacheDeformerCount > 0 ? 1 : 0;

                for (i=0; i<lVertexCacheDeformerCount; ++i )
                {
                    // Get the Point Cache object
                    FbxVertexCacheDeformer* lDeformer = static_cast<FbxVertexCacheDeformer*>(lNode->GetGeometry()->GetDeformer(i, FbxDeformer::eVertexCache));
                    if( !lDeformer ) continue;
                    FbxCache* lCache = lDeformer->GetCache();
                    if( !lCache ) continue;

                    // Process the point cache data only if the constraint is active
                    if (lDeformer->IsActive())
                    {
						
                        if (lCache->GetCacheFileFormat() == FbxCache::eMaxPointCacheV2)
                        {
                            // This code show how to convert from PC2 to MC point cache format
                            // turn it on if you need it.
#if 0 
                            if (!lCache->ConvertFromPC2ToMC(FbxCache::eMCOneFile, 
                                FbxTime::GetFrameRate(pScene->GetGlobalTimeSettings().GetTimeMode())))
                            {
                                // Conversion failed, retrieve the error here
                                FbxString lTheErrorIs = lCache->GetError().GetLastErrorString();
                            }
#endif
                        }
                        else if (lCache->GetCacheFileFormat() == FbxCache::eMayaCache)
                        {
                            // This code show how to convert from MC to PC2 point cache format
                            // turn it on if you need it.
                            //#if 0 
                            if (!lCache->ConvertFromMCToPC2(FbxTime::GetFrameRate(pScene->GetGlobalSettings().GetTimeMode()), 0))
                            {
                                // Conversion failed, retrieve the error here
                                FbxString lTheErrorIs = lCache->GetError().GetLastErrorString();
                            }
                            //#endif
                        }


                        // Now open the cache file to read from it
                        if (!lCache->OpenFileForRead())
                        {
                            // Cannot open file 
                            FbxString lTheErrorIs = lCache->GetError().GetLastErrorString();

                            // Set the deformer inactive so we don't play it back
                            lDeformer->SetActive(false);
                        }
						else
						{
							// get the start and stop time of the cache
							int lChannelCount = lCache->GetChannelCount();
							
							for (int iChannelNo=0; iChannelNo < lChannelCount; iChannelNo++)
							{
								FbxTime lChannel_Start;
								FbxTime lChannel_Stop;

								if(lCache->GetAnimationRange(iChannelNo, lChannel_Start, lChannel_Stop))
								{
									// get the smallest start time
									if(lChannel_Start < pCache_Start) pCache_Start = lChannel_Start;

									// get the biggest stop time
									if(lChannel_Stop  > pCache_Stop)  pCache_Stop  = lChannel_Stop;
								}
							}
						}
                    }
                }
		
            }
		}

    }



     // Bake node attributes and materials under this node recursively.
    // Currently only mesh, light and material.
    void npFbxLoader::LoadCacheRecursive(FbxNode * pNode, FbxAnimLayer * pAnimLayer, bool pSupportVBO, ofMatrix4x4 parentMatrix)
    {
		// ignoring parent matrix??? only for bone structures?
		 FbxAMatrix lGlobalPosition ;
		  lGlobalPosition = pNode->EvaluateGlobalTransform(mCache_Start);
		  ofMatrix4x4 mat = getOFMatrix(lGlobalPosition);

		 ofMatrix4x4 nodOf =  getGeometry(pNode);
		ofMatrix4x4 pMatrix;
		
		mat.preMult(nodOf);

		float r;
		float g;
		float b;
		//material
		string textureFile = "";
		const int lMaterialCount = pNode->GetMaterialCount();
        for (int lMaterialIndex = 0; lMaterialIndex < lMaterialCount; ++lMaterialIndex)
        {
            FbxSurfaceMaterial * lMaterial = pNode->GetMaterial(lMaterialIndex);
	
   
			if (lMaterial)
			{
				const FbxProperty lProperty = lMaterial->FindProperty( FbxSurfaceMaterial::sDiffuse);
				 FbxDouble3 lResult(0, 0, 0);
       
        const FbxProperty lFactorProperty = lMaterial->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
        if (lProperty.IsValid() && lFactorProperty.IsValid())
        {
            lResult = lProperty.Get<FbxDouble3>();
            double lFactor = lFactorProperty.Get<FbxDouble>();
            if (lFactor != 1)
            {
                lResult[0] *= lFactor;
                lResult[1] *= lFactor;
                lResult[2] *= lFactor;
            }
        }
				 r  = static_cast<GLfloat>( lResult[0]);
				 g  = static_cast<GLfloat>( lResult[1]);
				 b = static_cast<GLfloat>( lResult[2]);
			

				if (lProperty.IsValid())
				{
					const int lTextureCount = lProperty.GetSrcObjectCount(FbxFileTexture::ClassId);
					if (lTextureCount)
					{
						const FbxFileTexture* lTexture = lProperty.GetSrcObject(FBX_TYPE(FbxFileTexture), 0);
						const FbxString lFileName = lTexture->GetFileName();
					//	const FbxString lAbsFbxFileName =  lTexture->GetRelativeFileName();
						
						//cout << lFileName<<endl;

						textureFile = lFileName;
					}

				}
				
				
			}
          
        }







        FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();
        if (lNodeAttribute)
        {
         
            if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
            {
                FbxMesh * lMesh = pNode->GetMesh();
                if ( lMesh && !lMesh->GetUserDataPtr())
                {
					npFbxMesh *m = new npFbxMesh ;
					m->name =pNode->GetName();
					m->objectMatrix =mat;
					m->id = meshes.size();
					m->textureFile = textureFile;
					m->setFBXMesh(lMesh);
					m->r =r;
					m->g =g;
					m->b =b;
					
					meshes.push_back (m);
				
              
                }
            }
         
        }

        const int lChildCount = pNode->GetChildCount();
	
        for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
        {
            LoadCacheRecursive(pNode->GetChild(lChildIndex), pAnimLayer, pSupportVBO, pMatrix);
        }
    }

    // Unload the cache and release the memory under this node recursively.
    void npFbxLoader::UnloadCacheRecursive(FbxNode * pNode)
    {
		
    }

    // Bake node attributes and materials for this scene and load the textures.
    void npFbxLoader::LoadCacheRecursive(FbxScene * pScene, FbxAnimLayer * pAnimLayer, const char * pFbxFileName, bool pSupportVBO)
    {
        
		ofMatrix4x4 rootMatrix;
		rootMatrix.makeIdentityMatrix();
        LoadCacheRecursive(pScene->GetRootNode(), pAnimLayer, pSupportVBO,rootMatrix );
    }

    // Unload the cache and release the memory fro this scene and release the textures in GPU
    void npFbxLoader::UnloadCacheRecursive(FbxScene * pScene)
    {
    
    }

	ofMatrix4x4 npFbxLoader::getOFMatrix( FbxAMatrix mat)
	{
		const  double * matr = (const double*)mat;
		ofMatrix4x4 ofM;
		ofM.set( matr[0], matr[1], matr[2], matr[3], matr[4], matr[5], matr[6], matr[7], matr[8], matr[9], matr[10], matr[11], matr[12], matr[13], matr[14], matr[15]);
		return ofM;
	
	}

	ofMatrix4x4 npFbxLoader::getGeometry(FbxNode* pNode)
{
    const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
    const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

    return getOFMatrix(FbxAMatrix(lT, lR, lS));
}


//
	//camera

	 void npFbxLoader::FillCameraArrayRecursive(FbxNode* pNode)
    {
        if (pNode)
        {
            if (pNode->GetNodeAttribute())
            {
                if (pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eCamera)
                {
					
			
				
					FbxAMatrix lGlobalPosition ;
					lGlobalPosition = pNode->EvaluateGlobalTransform(mCache_Stop);
					FbxCamera* lCamera = (FbxCamera*) pNode->GetNodeAttribute();
				
					lCamera->Position.Set(	lGlobalPosition.GetT());
					

					FbxVector4 lEye(0,0,1);
					lEye = lCamera->Position.Get();
					FbxAMatrix lGlobalRotation;
					FbxVector4 lRotationVector(lGlobalPosition.GetR());
	
					lGlobalRotation.SetR(lRotationVector);

          
					FbxVector4 lInterestPosition(lCamera->InterestPosition.Get());
					FbxVector4 lCameraGlobalPosition(lGlobalPosition.GetT());
					double lLength = (FbxVector4(lInterestPosition - lCameraGlobalPosition).Length());

            
					FbxVector4 lCenter;
					lRotationVector = FbxVector4(1.0,0,0);
					lCenter = lGlobalRotation.MultT(lRotationVector);
					lCenter *= lLength;
					lCenter += lEye;

	
					npFbxCam *cam = new npFbxCam();

					cam->x = lEye[0];
					cam->y = lEye[1]+HORIZON_OFFSET;
					cam->z = lEye[2];
					cam->camVO =new CameraVO();

					cam->xr = lCenter[0];
					cam->yr = lCenter[1]+HORIZON_OFFSET;
					cam->zr = lCenter[2];
					cam->name = pNode->GetName();
					cam->prepMatrix();
					cout<< cam->name<<endl;
					cameras.push_back(cam);
					
				
                }
            }

            const int lCount = pNode->GetChildCount();
            for (int i = 0; i < lCount; i++)
            {
                FillCameraArrayRecursive(pNode->GetChild(i));
				
            }
        }
    }

    // Find all the cameras in this scene.
    void npFbxLoader::FillCameraArray(FbxScene* pScene)
    {
       

        FillCameraArrayRecursive(pScene->GetRootNode());
    }

