//
//  HitItemWolf.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 17/10/12.
//
//

#ifndef EristoffGameServer_HitItemWolf_h
#define EristoffGameServer_HitItemWolf_h

#include "HitItem.h"
#include "cinder/Timeline.h"

class HitItemWolf :public HitItem
{
    
public:
    HitItemWolf();
    virtual void  updateFrame();
    virtual void show();
    virtual void  hide();
    virtual void hit();
	
	Anim<float> yPos;
	Anim<float> zPos;
    
};

#endif
