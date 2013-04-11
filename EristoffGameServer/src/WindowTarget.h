//
//  WindowTarget.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 03/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef EristoffGameServer_WindowTarget_h
#define EristoffGameServer_WindowTarget_h
#include <iostream>
#include "npMesh.h"
#include "cinder/Timeline.h"
#include "cinder/Easing.h"
#include "cinder/Matrix44.h"
#include "AppConstants.h"
#include "HitItemPool.h"
#include "HitItem.h"
using namespace cinder;


using namespace std;

class WindowTarget
{
	
	float respawnTime;
	
public:
	
	float closingTime;
	
	
	bool isActive;
    WindowTarget();
	
	void assignNewTarget();
	
    void update();
    void open();
    void close();
    void hit();
	
	void enable();
	void disable();
	
    Vec3<float> basePos;
    int id;
    
    Anim< float>	windowOpenAngle;
    bool isOpen;
    npMesh *luikL;
    npMesh *luikR;
    npMesh *window;
    Timeline  * mTimeline;
	HitItemPool *hitItemPool;
    HitItem *hitItem;
    
	PrizeType currentPrizeType;
	const ci::Color getRGB();
};


#endif
