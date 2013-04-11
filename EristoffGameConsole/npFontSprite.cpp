//
//  npFontSprite.cpp
//  eristoffGameConsole
//
//  Created by Kris Meeusen on 05/10/12.
//
//

#include "npFontSprite.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

npFontSprite::npFontSprite(){
    mColor = Color( 1, 1, 1.1f );
    mAlign = NP_ALIGN_BOTTEMLEFT;

}

void npFontSprite::setup(){

    setup("Arial-BoldMT", 120,NP_ALIGN_BOTTEMLEFT );
}

void npFontSprite::setup(std::string fontName,int size,int align){
    mAlign = align;
    mFont = ci::Font(ci::app::loadResource("AVGITCBT.TTF"),size);
    npBitmapSprite::setUV(0,0,1,1);
    isTextureReady=false;
}



void npFontSprite::setText(std::string text){
    mText = text;
    isDirty = true;
}

void npFontSprite::setAlign(int align){
    mAlign = align;
    isDirty = true;
}

void npFontSprite::setColor(ci::Color color){
    mColor  = color;
    isDirty = true;
}

bool  npFontSprite::update(bool parentIsDirty =false){
    if (isDirty) {
       // std::cout << "new texture" << std::endl;
        generateTexture();
    }
    return npBitmapSprite::update(parentIsDirty);
}


void npFontSprite::generateTexture(){
    TextLayout simple;
	simple.setFont(  mFont );
	simple.setColor(mColor);
	simple.addLine( mText );
	mTexture = gl::Texture( simple.render( true, true ) );
    
    
    npBitmapSprite::setSize(mTexture.getWidth(),mTexture.getHeight(),mAlign);
    
    
    isTextureReady=true;


}


void npFontSprite::bind(){    
    glBindTexture(GL_TEXTURE_2D, mTexture.getId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
