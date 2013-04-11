//
//  videoLayer.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 11/10/12.
//
//

#ifndef __EristoffGameServer__videoLayer__
#define __EristoffGameServer__videoLayer__

#include <iostream>
#include "cinder/qtime/QuickTime.h"
#include <boost/signals2.hpp>



enum VideoState{ NO_VIDEO,INTRO_LOOP_VIDEO,INTRO_GAME_VIDEO,OUTRO_VIDEO};
class VideoLayer{
	ci::qtime::MovieGl	mIntroMovieLoop;
	ci::qtime::MovieGl	mIntroMovieGame;
	ci::qtime::MovieGl	mOutroMovie;
	
	float fadeOutStartFadeOut;
	float fadeOutTime;
	
public:
	
	void setIntroLoop();
	void setIntroGame();
	void setOutro();
	
	void update();
	void setup();
	void draw();
    
    void stop();
    
    VideoState requestedVideoState;
    
    boost::signals2::signal<void()> sIntroVideoDone;
    boost::signals2::signal<void()> sOutroVideoDone;
	
    
};


#endif /* defined(__EristoffGameServer__videoLayer__) */
