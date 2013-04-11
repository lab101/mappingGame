#pragma once
#include <fbxsdk.h>
#include "npFbxMesh.h"

class npFbxLoader
{
public:
	npFbxLoader(void);
	~npFbxLoader(void);
	void load(const char *fileName,int debugLoad);
	void destroySdkObjects(FbxManager* pSdkManager);
	void initializeSdkObjects(FbxManager*& pSdkManager, FbxScene*& pScene);
	void triangulateRecursive(FbxNode* pNode);
	void preparePointCacheData(FbxScene* pScene, FbxTime &pCache_Start, FbxTime &pCache_Stop);


	void LoadCacheRecursive(FbxNode * pNode, FbxAnimLayer * pAnimLayer, bool pSupportVBO,ofMatrix4x4 parentMatrix);
	void UnloadCacheRecursive(FbxNode * pNode);
	void LoadCacheRecursive(FbxScene * pScene, FbxAnimLayer * pAnimLayer, const char * pFbxFileName, bool pSupportVBO);
	void UnloadCacheRecursive(FbxScene * pScene);
	
	void FillCameraArray(FbxScene* pScene);
	void FillCameraArrayRecursive(FbxNode* pNode);
	
	FbxManager * mSdkManager;
    FbxScene * mScene;
    FbxImporter * mImporter;
    FbxAnimLayer * mCurrentAnimLayer;
    FbxNode * mSelectedNode;
	vector <npFbxCam *> cameras;
	vector <npFbxMesh *> meshes;
	// FbxArray<FbxNode*> mCameraArray;
private:
	mutable FbxTime mCache_Start, mCache_Stop;

	ofMatrix4x4 getOFMatrix( FbxAMatrix mat);
	ofMatrix4x4 getGeometry(FbxNode* pNode);
};

