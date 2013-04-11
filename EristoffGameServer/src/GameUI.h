//
//  GameUI.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 01/10/12.
//
//

#ifndef __EristoffGameServer__GameUI__
#define __EristoffGameServer__GameUI__

#include <iostream>
#include "Crosshair.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

class GameUI{
    
private:
 
	std::vector<Crosshair> crosshairs;
	std::vector<ci::Color> colors;
	ci::gl::Texture backup;

public:
    void setup();
    void draw();
    
    void setPlayerNames();
    
};

#endif /* defined(__EristoffGameServer__GameUI__) */
