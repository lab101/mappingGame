//
//  ProjectionRenderer.h
//  basicApp
//
//  Created by Kris Temmerman on 09/10/12.
//
//

#ifndef basicApp_ProjectionRenderer_h
#define basicApp_ProjectionRenderer_h

#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"

#include "cinder/gl/GlslProg.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class ProjectionRenderer
{

public:
    ProjectionRenderer(){};
    
    void setup();
   
    
    void draw();

    float * vertices;
    unsigned int *indices;
    int numIndices;
    
    
     ci::gl::GlslProg mShader;
	GLuint program;
    
	    
	GLint aVertex;
	
    GLint aUV;
    GLuint texture;
    float					projectorX;
    float					projectorY;
    float					projectorZ;
    
    float					projectionWidth;
    float					projectionHeight;
    
    float					buildingOffsetX;
    float					buildingOffsetY;
    
    
    float globalX;
    float globalY;
    float globalScale;
};

#endif
