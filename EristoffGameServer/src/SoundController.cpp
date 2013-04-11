//
//  soundController.cpp
//  EristoffGameServer
//
//  Created by Kris Meeusen on 17/10/12.
//
//

#include "SoundController.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;


SoundController*  SoundController::instance = NULL;


SoundController* SoundController::Instance(){
    if(instance == NULL)
    {
        instance = new SoundController();
    }
    
    return instance;
}


SoundController::SoundController(){
	
	
	// SOUNDS are not part of the nonbranded version...
	/*
	
	mWolfHit.loadSound( getAssetPath( "sounds/wolf/wolf-yap.aif" ).string(),FALSE);
	mCoinHit.loadSound( getAssetPath( "sounds/coin-hit/coin-hit-2.aif" ).string(),FALSE);
	mNewPlayer.loadSound( getAssetPath( "sounds/coin-hit/coin-hit-2.aif" ).string(),FALSE);
	mWolfOpen.loadSound( getAssetPath( "sounds/wolf/growl-snarl.wav" ).string(),FALSE);
	
	mShot1.loadSound( getAssetPath( "sounds/gunshots/gun4.aif" ).string(),FALSE);
	mShot2.loadSound( getAssetPath( "sounds/gunshots/ricochet1.aif" ).string(),FALSE);
	mShot3.loadSound( getAssetPath( "sounds/gunshots/gun3.aif" ).string(),FALSE);
	
	mWall1.loadSound( getAssetPath( "sounds/debris/debris-falling-1.aif" ).string(),FALSE);
	mWall2.loadSound( getAssetPath( "sounds/debris/debris-falling-2.aif" ).string(),FALSE);
	mWall3.loadSound( getAssetPath( "sounds/debris/debris-falling-3.aif" ).string(),FALSE);
	mWall4.loadSound( getAssetPath( "sounds/debris/debris-falling-4.aif" ).string(),FALSE);
	
	mShutterOpen.loadSound( getAssetPath( "sounds/shutters/swing-open.wav" ).string(),FALSE);
	mShutterClose.loadSound( getAssetPath( "sounds/shutters/swing-close.aif" ).string(),FALSE);
	
	mCountDown.loadSound( getAssetPath( "sounds/countdown-5s.aif" ).string(),FALSE);

	mPlayer1Bottle.loadSound( getAssetPath( "sounds/hit-the-bottle/player1-drinksonChit.aif" ).string(),FALSE);
	mPlayer2Bottle.loadSound( getAssetPath( "sounds/hit-the-bottle/player2-drinksonChit.aif" ).string(),FALSE);
	
	//	FmodexPlayer ;
//	FmodexPlayer ;
	
	mShot1.setVolume(0.5);
	mShot2.setVolume(0.5);
	mShot3.setVolume(0.5);
//	mShot4.setVolume(0.8);
	
	mShutterOpen.setVolume(0.3);
	mShutterClose.setVolume(0.3);
	
	mParachutte.loadSound( getAssetPath( "sounds/parachute/parachute-open-flapping.wav" ).string(),FALSE);
	
	mWall1.setVolume(0.4);
	mWall2.setVolume(0.4);
	mWall3.setVolume(0.4);
	mWall4.setVolume(0.4);
	 */
	
//	mCountDown.setVolume(1.2);

}

void SoundController::PlayerBottle(int nr){
//	if(nr ==1){
//		mPlayer1Bottle.play();
//	}else{
//		mPlayer2Bottle.play();
//
//	}
}


void SoundController::ShuttersOpen(){
	//mShutterOpen.play();
}

void SoundController::CountDown(){
	//mCountDown.play();
}

void SoundController::ShuttersClose(){
	//mShutterClose.play();
}

void SoundController::Shoot(float pan){
//	float rnd = ci::randFloat(0,100);
//	if(rnd < 10){
//		mShot2.setPan(pan);
//		mShot2.play();
//	}else if(rnd < 30){
//		mShot3.setPan(pan);
//		mShot3.play();
//	}else{
//		mShot1.setPan(pan);
//		mShot1.play();
//	}
//
}


void SoundController::Parachutte(){
///	mParachutte.play();
}


void SoundController::WolfOpen(){
//	mWolfOpen.play();
}


void SoundController::CointHit(){
//	mCoinHit.play();
	
}

void SoundController::NewPlayer(){
//	mCoinHit.play();

}

void SoundController::Wall(float pan){
//	float rnd = ci::randFloat(0,100);
//	if(rnd < 10){
//		mWall1.play();
//		mWall1.setPan(pan);
//
//	}else if(rnd < 30){
//		mWall2.play();
//		mWall2.setPan(pan);
//
//	}else if(rnd < 60){
//		mWall3.play();
//		mWall3.setPan(pan);
//
//	}else{
//		mWall4.play();
//		mWall4.setPan(pan);
//
//	}
}

void SoundController::WolfHit(){
	//audio::Output::play( mWolfHit.get() );
	//mWolfHit.play();
}