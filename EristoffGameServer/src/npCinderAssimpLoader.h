#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/Matrix44.h"
#include "assimp.h"
#include "aiScene.h"
#include "npMesh.h"
using namespace std;
using namespace ci;
using namespace ci::app;

class npCinderAssimpLoader
{

public :
	npCinderAssimpLoader(){    preMatrix.setToIdentity();blender =false;};

	void load(string fileName);
	void processScene();
	void makeMesh(aiMesh *mesh,string name,aiMatrix4x4 	&mTransformation);
    npMesh* getMeshByName(const string &name);
	const aiScene* scene;

	vector <npMesh *> meshes;
    bool blender ;
    void parseNode(aiNode *node);
    cinder::Matrix44f preMatrixNormal;
        cinder::Matrix44f preMatrix;
};

