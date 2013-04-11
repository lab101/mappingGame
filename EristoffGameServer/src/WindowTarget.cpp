//
//  WindowTarget.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 03/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "WindowTarget.h"
#include "PrizeController.h"
#include "cinder/Rand.h"
#include "SettingManager.h"
#include "SoundController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

WindowTarget::WindowTarget()
{
	isOpen =false;
	isActive =false;
	windowOpenAngle = 0;
    hitItem=NULL;
	closingTime = ci::app::getElapsedSeconds();

	//assignNewTarget();
}

void WindowTarget::assignNewTarget(){
	WindowData data = PrizeController::Instance()->getNextPrize();
	currentPrizeType = data.prizeType;
	respawnTime = data.windowDelay;

	//std::cout << "set prize type: " << currentPrizeType << "/" << currentPrizeType / 5.0 << "/"  << std::endl;
	hitItem =  hitItemPool->getHitItem(currentPrizeType);
    hitItem->basePos =basePos;
	
}


const ci::Color WindowTarget::getRGB(){
	return ci::Color(currentPrizeType / 255.0,0,0);
}



void WindowTarget::update()
{
	
	if(isActive && !isOpen && (ci::app::getElapsedSeconds() - closingTime) > respawnTime)
	{
		// console()<< "open";
		open();
	}
	
	   
    //windowOpenAngle-=0.1;
    
   luikL->objectMatrix.setToIdentity();
	
    luikL->objectMatrix.rotate(Vec3<float> (0,1,0), -windowOpenAngle );
	luikL->objectMatrix.rotate(Vec3<float> (1,0,0), 3.1415/2);


    luikL->resolveModelMatrix();
    
    
    luikR->objectMatrix.setToIdentity();
	
	
   luikR->objectMatrix.rotate(Vec3<float> (0,1,0),  windowOpenAngle);
	luikR->objectMatrix.rotate(Vec3<float> (1,0,0), 3.1415/2 );
	
    luikR->resolveModelMatrix();
	window->objectMatrix.setToIdentity();
	window->objectMatrix.rotate(Vec3<float> (1,0,0), -3.1415/2);
	window->resolveModelMatrix();
	if (hitItem) hitItem->update();
}

void WindowTarget::enable(){
	isActive = true;
	closingTime = ci::app::getElapsedSeconds();
}

void WindowTarget::disable(){
	close();
	isActive = false;
	assignNewTarget();

	
}

void WindowTarget::hit ()
{
	
    if (windowOpenAngle < - 2.6f && hitItem) hitItem->hit();
}
void WindowTarget::open()
{
	SoundController::Instance()->ShuttersOpen();
	
	assignNewTarget();
	// windowOpenAngle =3.14;
	timeline().apply( &windowOpenAngle, (float)-2.7, 1.0f, EaseInOutCubic() );//.finishFn( std::bind( &WindowTarget::close, this)  );
	timeline().appendTo( &windowOpenAngle, (float)-2.7, .0f, EaseInOutCubic() ).finishFn( std::bind( &WindowTarget::close, this)).delay(SettingManager::Instance()->windowOpenTime);
	
    isOpen =true;
    hitItem->show();
	
}

void WindowTarget::close()
{
	SoundController::Instance()->ShuttersClose();

	timeline().apply( &windowOpenAngle, (float)0, .5f, EaseInOutCubic()).delay(0.2);
    
	isOpen =false;
	
	hitItem->hide ();
	
	// adding animation delay
	closingTime = getElapsedSeconds() + 0.7;
    
	
}