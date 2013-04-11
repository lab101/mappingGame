//
//  Crosshair.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 22/10/12.
//
//

#ifndef __EristoffGameServer__Crosshair__
#define __EristoffGameServer__Crosshair__

#include <iostream>
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Font.h"
#include "cinder/Vector.h"
#include "cinder/Timeline.h"

class Crosshair{
	ci::gl::Texture     crosshair;
	ci::gl::Texture     spike;
	ci::gl::Texture     txtPlayer;
	ci::Font			mFont;

    ci::Vec2f playerNameDrawOffset;
    ci::Vec2f crosshairDrawOffset;
	
	ci::Anim<float> spikeOffset;
	ci::Anim<float> actionAn;
	float action;

public:
	void shoot();
	void setup();
	void draw(ci::Vec2f position,ci::Color color,bool isDizzy);
	void setName(std::string name,ci::Color color);

	Crosshair();

};


#endif /* defined(__EristoffGameServer__Crosshair__) */
