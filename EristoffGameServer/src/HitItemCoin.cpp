//
//  HitItemCoin.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 12/10/12.
//
//

#include "HitItemCoin.h"
using namespace ci;
using namespace ci::app;

HitItemCoin::HitItemCoin(){
	//	yPos = 30.0f;
	zPos = -100.0f;
	
	rotationZ = 0;
	rotationY = 0;
	//
	//rotX=-M_PI/2.0;
	//	rotY-=-90;
}

void HitItemCoin::updateFrame()
{
    rotY=rotationY;
    rotZ=rotationZ;
	y = yPos;
	z = zPos;
}

void HitItemCoin::show()
{
	rotX=-M_PI/2.0;
	rotationY = 0;
	
	//open
	timeline().apply(&yPos,-80.0f,0.1f,EaseOutCubic()).delay(0.5f);
	timeline().apply(&zPos,120.0f,0.6f,EaseOutCubic()).delay(0.6f);
	
	timeline().apply(&rotationY,(float) (M_PI * 12.0f),6.0f,EaseOutCubic());
	//	timeline().appendTo(&rotationY,(float) (M_PI * 12.0f),12.7f,EaseNone());
	//timeline().apply(&rotationZ,12.0f,7.0f,EaseNone());
	
	
}
void HitItemCoin::hide()
{
	timeline().apply(&zPos,-100.0f,0.1f,EaseOutCubic());
	timeline().apply(&rotationY,(float) (M_PI * 8.0f),2.3f,EaseOutCubic());
	
	timeline().apply(&yPos,0.0f,0.2f,EaseOutCubic()).finishFn( std::bind( &HitItem::hideComplete, this));
}

void HitItemCoin::hit()
{
	
	
}