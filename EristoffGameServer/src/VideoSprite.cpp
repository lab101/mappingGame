//
//  videoSprite.cpp
//  EristoffGameServer
//
//  Created by Kris Meeusen on 10/10/12.
//
//

#include "VideoSprite.h"
#include "cinder/app/AppBasic.h"


void VideoSprite::loadVideo(std::string path){
    
    isLoaded = false;
    std::cout << ci::app::getAssetPath(path);
    mMovie = ci::qtime::MovieGl(ci::app::loadAsset(path) );
	//mMovie.setLoop();
    mMovie.play();
}


void VideoSprite::update(){
    
    if(!isLoaded && mMovie.getTexture().getHeight() > 0){
        uiSprite::setupByTexture(mMovie.getTexture(),200,200,ALIGN_TOPLEFT);
        isLoaded = true;
    }
    
    if(isLoaded){
      //  std::cout << "id from movie obj " << mMovie.getTexture().getId() << std::endl;

        uiSprite::setTexture(mMovie.getTexture());
    }
    
    
    uiSprite::update();

}