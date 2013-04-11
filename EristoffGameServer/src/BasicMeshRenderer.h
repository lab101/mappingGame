#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "npMesh.h"
#include "cinder/gl/GlslProg.h"

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
void drawNonBuffer(const npMesh *mesh);
	void draw(const npMesh *mesh);
	void draw(const vector<npMesh *> &meches );

	void stop();
    ci::gl::GlslProg mShader;


	ProjectionCamera *camera;

	GLuint program;

	GLint uPerspectiveMatrix ;
    
    
    GLint uNormalMatrix ;
	GLint uWorldMatrix;
	GLint uObjectMatrix;
    GLint uTextureShadow;
	GLint uTextureMain;
    
    GLint uWorldMatrixShadow;
    GLint  uPerspectiveMatrixShadow ;
    
	GLuint shadowTexture ;
    
    GLint uLightPos;
    
	GLint aVertex;
	GLint aNormal;
    GLint  aTangent;
    GLint aUV;

};