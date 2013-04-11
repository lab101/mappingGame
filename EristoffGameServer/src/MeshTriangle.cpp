//
//  MeshTriangle.cpp
//  basicApp
//
//  Created by Kris Temmerman on 06/10/12.
//
//

#include "MeshTriangle.h"


void MeshTriangle:: calculateNormal()
{

    
    Vec3<float> U  = v1->screenVec -v2->screenVec;
    Vec3<float> V= v3->screenVec -v2->screenVec;
    
    normal = U.cross(V);


}