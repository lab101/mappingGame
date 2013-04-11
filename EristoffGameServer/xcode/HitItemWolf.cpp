//
//  HitItemWolf.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 17/10/12.
//
//

#include "HitItemWolf.h"
#include "SoundController.h"

using namespace ci;
using namespace ci::app;

HitItemWolf::HitItemWolf(){
	yPos = 30.0f;
	zPos = -100.0f;
}

void HitItemWolf::updateFrame()
{
    rotX= 3.1415/2;
	rotZ= 3.1415;
	y = yPos;
	z = zPos;
}

void HitItemWolf::show()
{
	SoundController::Instance()->WolfOpen();
	timeline().apply(&yPos,-80.0f,0.1f,EaseOutCubic()).delay(0.5f);
	timeline().apply(&zPos,120.0f,0.6f,EaseOutCubic()).delay(0.6f);
    
}
void HitItemWolf::hide()
{
	timeline().apply(&zPos,-100.0f,0.1f,EaseOutCubic());
	timeline().apply(&yPos,0.0f,0.2f,EaseOutCubic()).finishFn( std::bind( &HitItem::hideComplete, this));
}

void HitItemWolf::hit()
{
	SoundController::Instance()->WolfHit();
    
}