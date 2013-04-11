//
//  uiSprite.cpp
//  EristoffGameServer
//
//  Created by Kris Meeusen on 17/09/12.
//
//

#include "uiSprite.h"
#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"


using namespace ci;
using namespace ci::app;
using namespace std;

uiSprite::uiSprite(){
    mWidth = 0;
    mHeight = 0;

    rotation = 0;
    scale = 1;
    mAlpha = 1;

    isDirty = 0;
	isTextureLoaded = false;

	mTotalAnimationframes = 1;
	mCurrentAnimationframe = 0;
}

void uiSprite:: setupByTexture(ci::gl::Texture texture,float x,float y,int align){
    mTexture = texture;
	isTextureLoaded = true;
    
    mWidth =  mTexture.getWidth() / mTotalAnimationframes;
    mHeight = mTexture.getHeight();
    
    data = new float [36];
    
    switch (align) {
        case ALIGN_TOPLEFT:
            mCenterPointAnimated().x = x + (mWidth / 2.0);
            mCenterPointAnimated().y = y + (mHeight / 2.0);
            break;
            
        case ALIGN_TOPRIGHT:
            mCenterPointAnimated().x = x - mWidth / 2.0;
            mCenterPointAnimated().y = y + mHeight / 2.0;
            break;
            
        case ALIGN_BOTTOMRIGHT:
            mCenterPointAnimated().x = x - mWidth / 2.0;
            mCenterPointAnimated().y = y - mHeight / 2.0;
            break;
            
        case ALIGN_BOTTOMLEFT:
            mCenterPointAnimated().x = x + mWidth / 2.0;
            mCenterPointAnimated().y = y - mHeight / 2.0;
            break;
            
        case ALIGN_CENTER:
        default:
            mCenterPointAnimated().x = x;
            mCenterPointAnimated().y = y;
            break;
            
            
            // TODO implement all the other aligns
    }
    
    resetData();
  
}


void uiSprite::setupByResource(std::string fileName,float x,float y,int align){
    gl::Texture texture =  loadImage(loadResource(fileName));
    setupByTexture(texture, x, y, align);
}

void uiSprite::setupByAsset(std::string fileName,float x,float y,int align){
    gl::Texture texture =  loadImage(loadAsset(fileName));
    setupByTexture(texture, x, y, align);
}

void uiSprite::setAlpha(float alpha){
	mAlpha = alpha;
	isDirty = true;
}


void uiSprite::setTotalAnimationframes(int totalAnimationframes){
	mTotalAnimationframes = totalAnimationframes;
	if(isTextureLoaded) mWidth = mTexture.getWidth() / mTotalAnimationframes;
	isDirty = true;
}

void uiSprite::setCurrentAnimationFrame(int animationframe){
	mCurrentAnimationframe = animationframe;
	isDirty = true;
}


Vec2f uiSprite::getCenterPosition( ){
    return mCenterPointAnimated;
}

void uiSprite::setCenterPosition(Vec2f newPosition){
    mCenterPointAnimated = newPosition;
    isDirty = true;
}


void uiSprite::update(){
    if(isDirty){
        isDirty = false;
        resetData();
    }
}

void uiSprite::moveTo(ci::Vec2f position,float durationSec,float delay){
	timeline().apply( &mCenterPointAnimated, position, durationSec, EaseInCubic()).updateFn( std::bind( &uiSprite::setDirty, this ) );
}

void uiSprite::fadeTo(float newAlpha,float durationSec,float delay){
	timeline().apply( &mAlpha, newAlpha, durationSec, EaseInCubic()).updateFn( std::bind( &uiSprite::setDirty, this )).delay(delay);
}



void uiSprite::setDirty(){
	isDirty = true;
}

void uiSprite::resetData(){
     
    float uvHeight = 1.0;
	float uvWidth = 1.0 / mTotalAnimationframes;
	float uvLeft = mCurrentAnimationframe * uvWidth;
	float uvRight = (mCurrentAnimationframe+1) * uvWidth;

    leftBottom = Vec4f(- mWidth/2, mHeight/2,0.0f,1.0f);
    leftTop = Vec4f( - mWidth/2, -mHeight/2,0.0f,1.0f);
    rightBottom = Vec4f(  mWidth/2,mHeight/2,0.0f,1.0f);
    rightTop = Vec4f(  mWidth/2,-mHeight/2,0.0f,1.0f);
       
    mModelMatrix.setToIdentity();
    mModelMatrix.scale(scale);
	mModelMatrix.setTranslate(Vec4f(mCenterPointAnimated().x,mCenterPointAnimated().y,0,1));
    mModelMatrix.rotate(Vec3f(0,0,1), rotation);

    leftBottom = mModelMatrix.postMultiply(leftBottom);
    leftTop=mModelMatrix.postMultiply(leftTop);
    rightBottom=mModelMatrix.postMultiply(rightBottom);
    rightTop=mModelMatrix.postMultiply(rightTop);
    
    data[0] = leftTop.x;
    data[1] = leftTop.y;
    data[2] = 0;
    
    data[3] = uvLeft;
    data[4] = 0;
    data[5] = mAlpha;
    

	data[6] = rightTop.x ;
    data[7] = rightTop.y ;
    data[8] = 0;
    
	data[9] = uvRight;
    data[10] = 0;
    data[11] = mAlpha;
    
    
    data[12] = leftBottom.x ;
    data[13] = leftBottom.y ;
    data[14] = 0;
    
    data[15] = uvLeft;
    data[16] = uvHeight;
    data[17] = mAlpha;
    
    
    data[18] = rightBottom.x ;
    data[19] = rightBottom.y ;
    data[20] = 0;
    
    data[21] = uvRight;
    data[22] = uvHeight;
    data[23] = mAlpha;
    
    
    data[24] = data[12];
    data[25] = data[13];
    data[26] = data[14];
    
    data[27] = data[15];
    data[28] = data[16];
    data[29] = data[17];
    
    
    data[30] = data[6];
    data[31] = data[7];
    data[32] = data[8];
    
    data[33] = data[9];
    data[34] = data[10];
    data[35] = data[11];

}

 ci::gl::Texture& uiSprite::getTexture(){
    return mTexture;
}


void uiSprite::setTexture(ci::gl::Texture texture){
    mTexture = texture;
}


ci::Rectf uiSprite::getBoundingBox(){
    Rectf boundingBox(mCenterPointAnimated().x - mWidth/2, mCenterPointAnimated().y - mHeight/2, mCenterPointAnimated().x + mWidth/2, mCenterPointAnimated().y + mHeight/2);
    return boundingBox;
}


bool uiSprite::isHit(ci::Vec2f point){
    return getBoundingBox().contains(point);
}
