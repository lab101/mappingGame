//
//  npMaterial.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 08/10/12.
//
//

#include "npMaterial.h"
void npMaterial::setColorTexture(string name)
{
    
    cinderColortexture =cinder::loadImage(cinder::app::loadAsset( name ));
    colortexture =cinderColortexture.getId();
}