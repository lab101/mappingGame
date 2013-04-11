//
//  npMaterial.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 08/10/12.
//
//

#ifndef EristoffGameServer_npMaterial_h
#define EristoffGameServer_npMaterial_h

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/app/AppBasic.h"
using namespace std;
using namespace ci;

class npMaterial
{
public:
    npMaterial()
    {
        colortexture =0;
    }
    void setColorTexture(string name="image.jpeg");
   
    cinder::gl::Texture cinderColortexture;
    GLuint colortexture;

};


#endif
