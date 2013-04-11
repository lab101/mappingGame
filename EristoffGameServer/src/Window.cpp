#include "Window.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "settingManager.h"

Window::Window(){
	reset();
}

void Window::setHit(){
	reset();
}

void Window::reset(){
	uiSprite::setCurrentAnimationFrame(0);
	lastHit = ci::app::getElapsedSeconds();
	openTime = -1;
	isClosed = true;
	respawnTime = ci::randFloat(8,22);
 //   ci::randSeed(uiSprite::getCenterPosition().x + uiSprite::getCenterPosition().y);
	
    int random = ci::randInt(0,100);
    
    if(random < 40){
        currentWindowType = POINTS10;
    }else if(random < 70){
        currentWindowType = POINTS25;
    }else if(random < 80){
        currentWindowType = POINTS50;
    }
    else{
        currentWindowType = BAD;
    }
    
 //   currentWindowType = (windowType) ci::randInt(1,5);
    
    //std::cout << currentWindowType << std::endl;
    
    if(currentWindowType == POINTS10){
        points = 10;
    }else if(currentWindowType == POINTS25){
        points = 20;
    }else if(currentWindowType == POINTS50){
        points = 100;
    }else{
        points = 0;
    }
    
   // std::cout << points << std::endl;
}

void Window::update(){

	if(openTime > 0 && (ci::app::getElapsedSeconds() - openTime) > SettingManager::Instance()->windowOpenTime)
	{
		reset();
	} else if(isClosed && lastHit > 0 && (ci::app::getElapsedSeconds() - lastHit) > respawnTime)
	{
		uiSprite::setCurrentAnimationFrame(currentWindowType);
		openTime = ci::app::getElapsedSeconds();
		isClosed = false;
	}
}

