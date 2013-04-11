//
//  HitItem.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 04/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "HitItem.h"


void HitItem:: update()
{
    if (!used)return;
  updateFrame();
    visualMesh->objectMatrix.setToIdentity();
   visualMesh->objectMatrix.translate(Vec3<float>(basePos.x+x,basePos.y+y,basePos.z+z));
    
  visualMesh->objectMatrix.rotate(Vec3<float>(0,0,1),rotZ);
    visualMesh->objectMatrix.rotate(Vec3<float>(0,1,0),rotY);
    visualMesh->objectMatrix.rotate(Vec3<float>(1,0,0),rotX);
    
    
    visualMesh->resolveModelMatrix();


}