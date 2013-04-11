#pragma once
#include "cinder/app/AppBasic.h"
#include <vector>
#include "DeformCube.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DestructibleBlock
{
public:
	DestructibleBlock(){};


	void setup(float x,float y,float w, float h,float d, int subW, int subH);
	
	
	int numCubes ;
	vector< DeformCube *> cubes;
	
	// opengl
	void createBuffer();
	int unsigned *indices;
	float *vertices;

	int numIndices;
	int numVertices;
	int	stride;
    GLuint vertexBuffer;
    GLuint indexBuffer;

	
};