//
//  uiSprite.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 17/09/12.
//
//

#ifndef EristoffGameServer_uiSprite_h
#define EristoffGameServer_uiSprite_h


#define ALIGN_TOP 100
#define ALIGN_LEFT 101
#define ALIGN_BOTTEM 102
#define ALIGN_RIGHT 103

#define ALIGN_TOPLEFT 104
#define ALIGN_TOPRIGHT 105
#define ALIGN_BOTTOMLEFT 106
#define ALIGN_BOTTOMRIGHT 107

#define ALIGN_CENTER 1018


#include "cinder/Vector.h"
#include "cinder/gl/Texture.h"
#include "cinder/Timeline.h"

#include "string"

class uiSprite{
   
    ci::Vec2f mCenterPoint;
	ci::Anim<ci::Vec2f> mCenterPointAnimated;

    ci::Anim<float> rotation;
    ci::Anim<float> scale;
    ci::Anim<float> mAlpha;
    
    ci::gl::Texture mTexture;

    float mWidth;
    float mHeight;
    
    
    ci::Vec4f leftBottom;
    ci::Vec4f rightBottom;
    ci::Vec4f leftTop;
    ci::Vec4f rightTop;
   
    ci::Matrix44f mModelMatrix;
 
    bool isDirty;

	int mTotalAnimationframes;
    int mCurrentAnimationframe;
    
public:
    uiSprite();
    
    bool isTextureLoaded;


    void setupByAsset(std::string fileName,float x,float y,int align);
    void setupByResource(std::string fileName,float x,float y,int align);
    
    void setupByTexture(ci::gl::Texture texture,float x,float y,int align);
    
    virtual void update();
    void resetData();

	void setDirty();
    
	void moveTo( ci::Vec2f position,float durationSec,float delay = 0);
	void fadeTo(float newAlpha,float durationSec,float delay = 0);

    float * data;
    
	void setCenterPosition(ci::Vec2f newPosition);
	void setAlpha(float alpha);

    ci::Vec2f getCenterPosition();
    ci::Rectf getBoundingBox();
    
    ci::gl::Texture& getTexture();
    void setTexture(ci::gl::Texture texture);

    bool isHit(ci::Vec2f point);

	void setTotalAnimationframes(int totalAnimationframes);
	void setCurrentAnimationFrame(int animationframe);
};


#endif
