//
//  MeshTriangle.h
//  basicApp
//
//  Created by Kris Temmerman on 06/10/12.
//
//

#ifndef basicApp_MeshTriangle_h
#define basicApp_MeshTriangle_h
#include "cinder/Vector.h"
#include "MeshVertex.h"
using namespace cinder;
using namespace ci;
using namespace std;
class MeshTriangle
{

    public :
    MeshTriangle(){};
    MeshVertex *v1;
    MeshVertex *v2;
    MeshVertex *v3;
    Vec3<float> normal;
    void calculateNormal();
    

};

#endif
