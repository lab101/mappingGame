//
//  PlaasterVertex.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 15/10/12.
//
//

#ifndef EristoffGameServer_PlaasterVertex_h
#define EristoffGameServer_PlaasterVertex_h
#include "cinder/Vector.h"

using namespace cinder;

class PlaasterVertex
{
public:
    PlaasterVertex(){}
    void setData(float *v, int ofzet)
    {
        vertex.x = v[ofzet++];
        vertex.y  = v[ofzet++];
        vertex.z= v[ofzet++];
        
        normal.x = v[ofzet++];
        normal.y  = v[ofzet++];
        normal.z  = v[ofzet++];
        
        uv.x =  v[ofzet++];
        uv.y =  v[ofzet++];
    }
    Vec3f vertex;
    Vec3f normal;
    Vec2f uv;


};


#endif
