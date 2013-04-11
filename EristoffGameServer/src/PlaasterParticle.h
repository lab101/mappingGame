//
//  PlaasterParticle.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 15/10/12.
//
//

#ifndef EristoffGameServer_PlaasterParticle_h
#define EristoffGameServer_PlaasterParticle_h

#include "npMesh.h"
#include "PlaasterTriangle.h"

class PlaasterTriangle;
class PlaasterParticle
{
    public :
   PlaasterParticle(){}
    void setup(PlaasterTriangle *triangle );
    void update();
    void reset(float dist,Vec2f dir  );
    npMesh * partMesh;
    float rotX;
    float rotY;
    float x ;
    float y;
    float z;
    float xs ;
    float ys;
    float zs;
    float speedX ;
    float speedY;
    float speedZ;
};

#endif
