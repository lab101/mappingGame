//
//  HitItemCoin.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 12/10/12.
//
//

#ifndef EristoffGameServer_HitItemCoin_h
#define EristoffGameServer_HitItemCoin_h
#include "HitItem.h"
#include "cinder/Timeline.h"

class HitItemCoin :public HitItem
{
	
public:
    HitItemCoin();
    virtual void  updateFrame();
	virtual void show();
	virtual void  hide();
	virtual void hit();
	
	Anim<float> yPos;
	Anim<float> zPos;
	Anim<float> rotationY;
	Anim<float> rotationZ;
	
	
};

#endif
