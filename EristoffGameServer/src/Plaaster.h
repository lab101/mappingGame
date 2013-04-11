//
//  Plaaster.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 15/10/12.
//
//

#ifndef EristoffGameServer_Plaaster_h
#define EristoffGameServer_Plaaster_h
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/Matrix44.h"
#include "npMesh.h"
#include "PlaasterTriangle.h"
#include "PlaasterParticle.h"
using namespace std;
using namespace ci;
using namespace cinder;

using namespace ci::app;
using namespace std;
class Plaaster
{

public:
    Plaaster(){};
    void setup(npMesh *mesh);
    void reset();
    int shoot(Vec3f pos);
    void devide();
    void updateMainMesh();
    void update();
    void setOutro();
	npMesh * baseMesh;
    npMesh * renderMesh;
    
    vector<PlaasterTriangle *>triangles;
    vector<PlaasterTriangle *>trianglesRoot;
    vector<PlaasterParticle *>particles;
};

#endif
