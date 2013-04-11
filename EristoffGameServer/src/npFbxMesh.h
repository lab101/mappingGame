#pragma once
#include <fbxsdk.h>

class npFbxMesh
{
public:
	npFbxMesh(void);
	~npFbxMesh(void);

	void setup();
	void loadTextures();
	 enum
    {
        VERTEX,
        INDEX,
        NUM_VBO
    };
	string name;
	 GLuint vbos[ NUM_VBO];
	 int numIndices;
	 float *lVertices;
	 void setFBXMesh( FbxMesh * lMesh);
	 
	 ofMatrix4x4 objectMatrix;
     string textureFile;
	 float reflection;
	  float specular;
 float specularVal;
	 int id;
	GLuint texture; 
	
		bool isColor;
		float r;
		float g;
		float b;	
		
	struct SubMesh
    {
        SubMesh() : IndexOffset(0), TriangleCount(0) {}

        int IndexOffset;
        int TriangleCount;
    };
    FbxArray<SubMesh*> mSubMeshes;

	
};

