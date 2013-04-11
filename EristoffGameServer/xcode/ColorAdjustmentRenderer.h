//
//  ColorAdjustmentRenderer.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 23/10/12.
//
//

#ifndef EristoffGameServer_ColorAdjustmentRenderer_h
#define EristoffGameServer_ColorAdjustmentRenderer_h

#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "npMesh.h"
#include "cinder/gl/GlslProg.h"

#include "ProjectionCamera.h"
using namespace ci;
using namespace ci::app;
using namespace std;


class ColorAdjustmentRenderer
{
    
public:
    ColorAdjustmentRenderer(){contrast=1;saturation=1;brightness=0;}
    void setup();
    void draw();

    float contrast;
    float saturation;
    float brightness;
    
    ci::gl::GlslProg mShader;
    GLuint program;
	float * vertices;
    

    GLuint texture ;
    GLint uContrast;
    GLint uSaturation;
    GLint uBrightness;
	GLint aVertex;
    GLint aUV;
};


#endif
