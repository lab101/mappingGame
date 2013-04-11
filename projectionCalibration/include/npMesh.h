
#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/Matrix44.h"


class npMesh
{
public:
	npMesh(){};
	
	int numVertices;
	int stride;
	float *vertices ;



	int numIndices; 
	unsigned int *indices;

		cinder::Matrix44f objectMatrix;

	float xMin;
	float yMin;
	float zMin;

	float xMax;
	float yMax;
	float zMax;



	GLuint vertexBuffer;
    GLuint indexBuffer;

	void createBuffer();
};