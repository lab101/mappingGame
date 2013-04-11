//
//  PlaasterTriangle.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 15/10/12.
//
//

#ifndef EristoffGameServer_PlaasterTriangle_h
#define EristoffGameServer_PlaasterTriangle_h

#include "cinder/Vector.h"
#include "PlaasterVertex.h"
#include "PlaasterParticle.h"

class PlaasterParticle;
using namespace cinder;
class PlaasterTriangle
{

public:
    PlaasterTriangle(){}
    PlaasterVertex v1;
    PlaasterVertex v2;
    PlaasterVertex v3;
    
    void calculateCenter();
    
    Vec3f center;
    PlaasterParticle *particle;
};

#endif
