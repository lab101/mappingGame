//
//  videoLayer.cpp
//  EristoffGameServer
//
//  Created by Kris Meeusen on 11/10/12.
//
//

#include "VideoLayer.h"
#include "cinder/app/AppBasic.h"

#include "cinder/Vector.h"
#include "cinder/gl/Texture.h"
#include "SettingManager.h"

using namespace ci;
using namespace ci::app;

void VideoLayer::setup(){
	//	mIntroMovieLoop. "movies/robot_arms.mov"
	//std::cout << getAssetPath("/movies/spray.mov");
//
//    mIntroMovieLoop = ci::qtime::MovieGl(ci::app::loadAsset("movies/calibratievideolines.mov"));
	mIntroMovieLoop = ci::qtime::MovieGl(ci::app::loadAsset("movies/alpha.mov"));
    mIntroMovieGame = ci::qtime::MovieGl(ci::app::loadAsset("movies/alpha.mov"));
    mOutroMovie = ci::qtime::MovieGl(ci::app::loadAsset("movies/alpha.mov"));
	
	mIntroMovieLoop.setVolume(0.8);
	mIntroMovieGame.setVolume(0.8);
	mOutroMovie.setVolume(0.8);
	
    requestedVideoState = NO_VIDEO;
	fadeOutStartFadeOut = -1;
	fadeOutTime = 1.0f;
	//
	//	//! Returns whether the movie is currently playing or is paused/stopped.
	//	bool	isPlaying() const;
	//	//! Returns whether the movie has completely finished playing
	//	bool	isDone() const;
	//	//! Begins movie playback.
	//	void	play();
	//	//! Stops movie playback.
	//	void	stop();
	
}

void VideoLayer::setIntroLoop(){
    mIntroMovieLoop.seekToStart();
	//mIntroMovieLoop.setLoop(true);
    requestedVideoState = INTRO_LOOP_VIDEO;
	mIntroMovieLoop.play();
	
	mIntroMovieLoop.setRate(SettingManager::Instance()->videoSpeed);
	
}

void VideoLayer::setIntroGame(){
    mIntroMovieGame.seekToStart();
	
    requestedVideoState = INTRO_GAME_VIDEO;
    mIntroMovieLoop.setLoop(false);
	
}

void VideoLayer::setOutro(){
	
	mOutroMovie.play();
	mOutroMovie.setRate(SettingManager::Instance()->videoSpeed);
	
    requestedVideoState = OUTRO_VIDEO;
}


void VideoLayer::stop(){
    mIntroMovieLoop.stop();
    requestedVideoState = NO_VIDEO;
}


void VideoLayer::update(){
	if(requestedVideoState == INTRO_GAME_VIDEO && !mIntroMovieGame.isPlaying() && mIntroMovieLoop.isDone()){
		
        mIntroMovieGame.play();
        mIntroMovieGame.setRate(SettingManager::Instance()->videoSpeed);
        
        mIntroMovieLoop.stop();
		
        std::cout << "switch to intro game" << std::endl;
    }
    
    if(requestedVideoState == INTRO_GAME_VIDEO && mIntroMovieGame.isDone() && fadeOutStartFadeOut == -1){
        
		fadeOutStartFadeOut = getElapsedSeconds();
		std::cout << "intro fadeout start" << std::endl;

    }
    
    if(requestedVideoState == OUTRO_VIDEO && mOutroMovie.isDone()){
        requestedVideoState = NO_VIDEO;
        mOutroMovie.stop();
		mOutroMovie.seekToStart();

        sOutroVideoDone();
    }
	
	if(fadeOutStartFadeOut > 0 && (getElapsedSeconds() - fadeOutStartFadeOut) > fadeOutTime){
		fadeOutStartFadeOut = -1;
		requestedVideoState = NO_VIDEO;
        
		mIntroMovieGame.stop();
        mIntroMovieGame.seekToStart();
        
        sIntroVideoDone();
		
		std::cout << "intro fadeout done" << std::endl;
	}
	
}

void VideoLayer::draw(){
    
    if(SettingManager::Instance()->videoAlpha == 0 || requestedVideoState == NO_VIDEO) return;
    
	glColor4f(1,1,1,SettingManager::Instance()->videoAlpha);
	
	glPushMatrix();
	glTranslatef(SettingManager::Instance()->videoOffset.x,SettingManager::Instance()->videoOffset.y,0);
	glScalef(SettingManager::Instance()->videoScaleX,SettingManager::Instance()->videoScaleY,1);
	
	if (fadeOutStartFadeOut > 0 || (mIntroMovieLoop && mIntroMovieLoop.checkPlayable() && mIntroMovieLoop.isPlaying())) {
		if(fadeOutStartFadeOut > 0){
			glColor4f(1,1,1,(getElapsedSeconds() - fadeOutStartFadeOut) / fadeOutTime);
			//std::cout << ((getElapsedSeconds() - fadeOutStartFadeOut) / fadeOutTime) << std::endl;
		}
		gl::draw(mIntroMovieLoop.getTexture(),Vec2f(0,0));
	}
	
    if (mIntroMovieGame && mIntroMovieGame.checkPlayable() && mIntroMovieGame.isPlaying()) {
		gl::draw(mIntroMovieGame.getTexture(),Vec2f(0,0));
	}
	
    if (mOutroMovie && mOutroMovie.checkPlayable() && mOutroMovie.isPlaying()) {
		glPushMatrix();
	//	glScalef(1.5,1.5,1);
		gl::draw(mOutroMovie.getTexture(),Vec2f(0,0));
		glPopMatrix();
	}
    
	glPopMatrix();
	
	glColor4f(1,1,1,1);
	
}