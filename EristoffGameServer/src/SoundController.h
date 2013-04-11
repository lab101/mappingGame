//
//  soundController.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 17/10/12.
//
//

#ifndef __EristoffGameServer__soundController__
#define __EristoffGameServer__soundController__

#include <iostream>
#include "cinder/audio/Output.h"
#include "cinder/audio/Io.h"
#include "FmodexPlayer.h"

class SoundController
{

protected:
    SoundController();
	
private:
    static SoundController* instance;

	FmodexPlayer mWolfOpen;
	FmodexPlayer mWindowOpen;
	FmodexPlayer mCoinHit;
	FmodexPlayer mNewPlayer;
	FmodexPlayer mShot1;
	FmodexPlayer mShot2;
	FmodexPlayer mShot3;
	
	FmodexPlayer mWall1;
	FmodexPlayer mWall2;
	FmodexPlayer mWall3;
	FmodexPlayer mWall4;
	FmodexPlayer mWall5;
	
	FmodexPlayer mShutterOpen;
	FmodexPlayer mShutterClose;
	
	FmodexPlayer mCountDown;
	
	
	FmodexPlayer mParachutte;

	FmodexPlayer mPlayer1Bottle;
	FmodexPlayer mPlayer2Bottle;


	FmodexPlayer mWolfHit;

public:
	
    static SoundController* Instance();
	
	void CointHit();
	void NewPlayer();
	void WolfOpen();
	void WolfHit();
	void WallHit();
	void Shoot(float pan);
	void Wall(float pan);
	void Parachutte();
	
	void ShuttersOpen();
	void ShuttersClose();
	
	void CountDown();
	
	void PlayerBottle(int nr);
	

};

#endif /* defined(__EristoffGameServer__soundController__) */
