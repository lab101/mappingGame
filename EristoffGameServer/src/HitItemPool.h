//
//  HitItemPool.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 12/10/12.
//
//

#ifndef EristoffGameServer_HitItemPool_h
#define EristoffGameServer_HitItemPool_h


#include "npMesh.h"
#include "npCinderAssimpLoader.h"
#include "cinder/app/AppBasic.h"
#include "HitItem.h"
#include "HitItemCoin.h"
#include "HitItemWolf.h"
#include "AppConstants.h"
using namespace ci;
using namespace ci::app;

using namespace cinder;


using namespace std;

class HitItemPool
{

public:
    HitItemPool(){coinMesh =NULL;}
    void setup();
    HitItem * getHitItem(PrizeType type );
    
    HitItem * getCoin(PrizeType type );
    
    vector <HitItem *> coins;
    
    HitItem * getWolf(PrizeType type );
    
    vector <HitItemWolf *> wolven;
    npCinderAssimpLoader loader;
    
    npMesh * coinMesh;
    npMesh * wolfMesh;
    npMaterial *coin10Mat;
    npMaterial *coin25Mat;
    npMaterial *coin50Mat;
	
	npMaterial *wolfMat;

};

#endif
