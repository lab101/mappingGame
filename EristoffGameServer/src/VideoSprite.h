//
//  videoSprite.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 10/10/12.
//
//

#ifndef __EristoffGameServer__videoSprite__
#define __EristoffGameServer__videoSprite__

#include <iostream>
#include "uiSprite.h"
#include "cinder/qtime/QuickTime.h"

class VideoSprite : public uiSprite{
 
    bool isLoaded;
    
public:
	
	ci::qtime::MovieGl	mMovie;

    void loadVideo(std::string path);
    virtual void update();

};

#endif /* defined(__EristoffGameServer__videoSprite__) */
