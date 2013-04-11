#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "assimp.h"
#include "aiScene.h"
#include "npMesh.h"
using namespace std;
using namespace ci;
using namespace ci::app;

class npCinderAssimpLoader
{

public :
	npCinderAssimpLoader(){};

	void load(string fileName);
	void processScene();
	void makeMesh(aiMesh *mesh);

	const aiScene* scene;

	vector <npMesh *> meshes;
};

