//
//  ColorAdjustmentRenderer.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 23/10/12.
//
//


#include "ColorAdjustmentRenderer.h"
#include "SettingManager.h"

void ColorAdjustmentRenderer:: setup()
{
    try {
    
    
        mShader = gl::GlslProg( loadAsset( "shaders/adjShader.vsh" ), loadAsset( "shaders/adjShader.fsh" ) );
    
    
    
    
    
    
    }
        catch( gl::GlslProgCompileExc &exc ) {
        console() << "Shader compile error: " << std::endl;
        console() <<  exc.what();
    }
        catch( ... ) {
            console() <<  "Unable to load shader" << std::endl;
        }
    console() << "oked";

    program =  mShader.getHandle();

    glUseProgram(program);

    aVertex= glGetAttribLocation (program,"position");
    
    aUV= glGetAttribLocation (program,"uv");

    
    
    uContrast =glGetUniformLocation(program, "contrast");
     uSaturation=glGetUniformLocation(program, "saturation");
    uBrightness=glGetUniformLocation(program, "brightness");
    
    
    glUseProgram(0);
    
    
    vertices =new float[4*4];
    int count =0;
    vertices[count++] =-1;
    vertices[count++] =-1;
    vertices[count++] =0;
    vertices[count++] =0;
    
    
    vertices[count++] =1;
    vertices[count++] =-1;
    vertices[count++] =1;
    vertices[count++] =0;
    
    
    vertices[count++] =1;
    vertices[count++] =1;
    vertices[count++] =1;
    vertices[count++] =1;
    
    
    vertices[count++] =-1;
    vertices[count++] =1;
    vertices[count++] =0;
    vertices[count++] =1;
    
}

void ColorAdjustmentRenderer:: draw()
{
 glUseProgram(program);
    glBindTexture(GL_TEXTURE_2D, texture);
     glEnableVertexAttribArray(aVertex);
     glEnableVertexAttribArray(aUV);

    
    glUniform1f(uSaturation, SettingManager::Instance()->saturation);
     glUniform1f(uBrightness, SettingManager::Instance()->brightness);
      glUniform1f(uContrast,SettingManager::Instance()->contrast);
    float * pointer  = vertices;
    glVertexAttribPointer(aVertex, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4,(GLvoid*) pointer);
    pointer+=2;
    glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float)* 4,(GLvoid*) pointer);

    glDrawArrays(GL_QUADS, 0, 4);
    
    glDisableVertexAttribArray(aVertex);
    glDisableVertexAttribArray(aUV);
     glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}