//
//  ColorMeshRenderer.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 04/10/12.
//
//

#ifndef EristoffGameServer_ColorMeshRenderer_h
#define EristoffGameServer_ColorMeshRenderer_h

#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "npMesh.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/Matrix44.h"
#include "ProjectionCamera.h"
using namespace ci;
using namespace ci::app;
using namespace std;
/*
 using namespace boost
 */


class ColorMeshRenderer
{
    
public:
    
	ColorMeshRenderer(){};
    
	void setup();
	void start();
    void startShadow();
    void startFlat();
    void drawFlat(vector<Vec2<float> > vertices ,GLenum type);
	void draw(const npMesh *mesh);
    	void drawNonBuffer(const npMesh *mesh);
	void draw(const vector<npMesh *> &meches );
    
	void stop();
    ci::gl::GlslProg mShader;
    
    
	ProjectionCamera *camera;
     cinder::Matrix44f idMatrix;
     cinder::Matrix44f worldMatrix;
	GLuint program;
    
	GLint uPerspectiveMatrix ;
	GLint uWorldMatrix;
	GLint uObjectMatrix;
    
	GLint aVertex;
	GLint uColor;
    
    float r;
    float g;
    float b;
    float a;
};

#endif
