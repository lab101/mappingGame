#pragma once
#include "cinder/gl/GlslProg.h"
#include "cinder/Camera.h"
#include "uiSprite.h"
#include "cinder/Vector.h"

enum {
    ATTRIB_VERTEX = 0,
    ATTRIB_UV = 1,
};



class uiSpriteRender{
	  ci::gl::GlslProg mShader;
	  GLint uWorldMatrix;
	  ci::CameraOrtho worldMatrix;
	

public:
    std::vector<uiSprite*> sprites;
	uiSpriteRender();
	void add(uiSprite* sprite);
	
    void setup();
    void setup(std::string shaderName);
    
	void update();
	void draw();
	void bind();
	void unbind();
	void draw(uiSprite &sprite);
    
    void resize(float width,float height);

};

