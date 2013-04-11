//
//  MeshVertex.h
//  basicApp
//
//  Created by Kris Temmerman on 06/10/12.
//
//

#ifndef basicApp_MeshVertex_h
#define basicApp_MeshVertex_h

#include "cinder/Vector.h"

using namespace cinder;
using namespace ci;
using namespace std;
class MeshVertex
{
    
    public :
    MeshVertex(){isSelected =false;useCount=0;};
    
    Vec4<float> startVec;
    Vec4<float> projectedVec;
    Vec3<float> screenVec;
    Vec2<float> posVec;
    Vec2<float>uvVec;
    int useCount;
    bool isSelected;
    int index;
    
};


#endif
