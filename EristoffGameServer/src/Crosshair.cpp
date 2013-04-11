//
//  Crosshair.cpp
//  EristoffGameServer
//
//  Created by Kris Meeusen on 22/10/12.
//
//

#include "Crosshair.h"
#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace std;
using namespace ci::app;

void Crosshair::setup(){

}

void Crosshair::setName(std::string name,Color color){
	TextLayout simple;
	simple.setFont(  mFont );
	
	if (name.size() > 9) {
		name = name.substr(0,9);
	}
	
	simple.setColor(color);
	simple.addLine(name);
	
	txtPlayer = gl::Texture( simple.render( true, true ) );
	playerNameDrawOffset.x = -txtPlayer.getWidth()/2.0;
	playerNameDrawOffset.y = 66;
}

Crosshair::Crosshair(){
	spikeOffset= 0;
	action =0;
	
	mFont = Font(ci::app::loadAsset("fonts/Railway.ttf"), 24 );
    
    crosshair = loadImage(loadAsset("crosshairRed.png"));
    spike = loadImage(loadAsset("spike.png"));
	
    crosshairDrawOffset.x = crosshair.getWidth() / -2.0;
    crosshairDrawOffset.y = crosshair.getHeight() / -2.0;

}

void Crosshair::shoot(){
	timeline().removeTarget(&spikeOffset);

	timeline().apply(&spikeOffset,0.6f,.05f,EaseOutCubic());
	timeline().appendTo(&spikeOffset,0.0f,0.1f,EaseInCubic()).delay(0.1);
	
	action = 0.5;
}

void Crosshair::draw(ci::Vec2f position,Color color,bool isDizzy){
	glColor3f(color);
	
	
//	if (action > 0) {
//		action -= action / 10.0;
//	}
	
	glPushMatrix();
	glTranslated(position.x, position.y, 1);
	glPushMatrix();

	glRotated(action *45.0, 0, 0, 1);
	
	glScaled(1+ action,1 + action, 1);

	if(isDizzy){
		float scale = 1 + ((sin(getElapsedSeconds()*10.0)) / 4.0);
		glScaled(scale, scale, 1);
	}

	gl::draw(crosshair,crosshairDrawOffset);
	
	
	
	// top spike
	gl::draw(spike, Vec2f(spike.getWidth()/-2.0,-spike.getHeight()-5 - spikeOffset* 20.5));

	
	// bottom spike
	glPushMatrix();
	glRotated(-180, 0, 0, 1);
	gl::draw(spike, Vec2f(spike.getWidth()/-2.0,-spike.getHeight()-5 - spikeOffset* 20.5));
	glPopMatrix();

	// left spike
	glPushMatrix();
	glRotated(-90, 0, 0, 1);
	gl::draw(spike, Vec2f( spike.getWidth()/-2.0,-spike.getHeight()-5 -spikeOffset* 20.5 ));
	glPopMatrix();
	
	// right spike
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	gl::draw(spike, Vec2f(spike.getWidth()/-2.0,-spike.getHeight()-5 - spikeOffset * 20.5));
	glPopMatrix();
	glPopMatrix();
	
	if(action){
		gl::draw(crosshair,crosshairDrawOffset);
	}
	
	if(txtPlayer) gl::draw(txtPlayer,playerNameDrawOffset);
	
	
	glPopMatrix();
	
	glColor3f(1,1,1);

	action=0;
	
}
