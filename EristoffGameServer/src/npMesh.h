
#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/Matrix44.h"
#include "cinder/Quaternion.h"
#include "npMaterial.h"
using namespace std;

class npMesh
{
public:
	npMesh(){material =NULL;normalMatrix.setToIdentity();};
	void resolveModelMatrix();
 
   npMesh * clone();
	int numVertices;
	int stride;
	float *vertices ;
    string name;


	int numIndices; 
	unsigned int *indices;
    
     Vec3<float> basePos;
    
	cinder::Matrix44f objectMatrixModel;
    cinder::Matrix44f objectMatrix;


    cinder::Matrix33f normalMatrix;
    
	float xMin;
	float yMin;
	float zMin;

	float xMax;
	float yMax;
	float zMax;

    npMaterial *material;

	GLuint vertexBuffer;
    GLuint indexBuffer;

	void createBuffer();
};