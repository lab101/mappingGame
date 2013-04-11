//
//  npFontObject.h
//  eristoffGameConsole
//
//  Created by Kris Meeusen on 05/10/12.
//
//

#ifndef __eristoffGameConsole__npFontObject__
#define __eristoffGameConsole__npFontObject__

#include <iostream>

#include "cinder/Font.h"
#include "cinder/Text.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

#include "npBitmapSprite.h"

class npFontSprite : public npBitmapSprite{
    ci::Font	mFont;
    ci::gl::Texture	mTexture;
    ci::Color mColor;
    
    void generateTexture();
    
    std::string mText;
    int mAlign;
    

public:
    
    bool isTextureReady;
    npFontSprite();
    
    void setup();
    void setup(std::string fontName,int size,int align);
    
    virtual bool update(bool parentIsDirty );


    void bind();
    void setText(std::string text);
    void setAlign(int align);
    void setColor(ci::Color color);

    
};




#endif /* defined(__eristoffGameConsole__npFontObject__) */
