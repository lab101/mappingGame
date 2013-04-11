#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "npMesh.h"


#include "ProjectionCamera.h"
using namespace ci;
using namespace ci::app;
using namespace std;
/*
using namespace boost
*/


class BasicMeshRenderer
{

public:

	BasicMeshRenderer(){};

	void setup();
	void start();

	void draw(const npMesh *mesh);
	void draw(const vector<npMesh *> &meches );

	void stop();



	ProjectionCamera *camera;

	GLuint program;

	GLint uPerspectiveMatrix ;
	GLint uWorldMatrix;
	GLint uObjectMatrix;

	GLint aVertex;
	GLint aNormal;


};