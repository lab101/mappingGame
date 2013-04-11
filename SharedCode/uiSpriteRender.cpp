#include "uiSpriteRender.h"
#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;
using namespace std;

 uiSpriteRender::uiSpriteRender(){

 }

void uiSpriteRender::add(uiSprite* sprite){
	sprites.push_back(sprite);
}

void uiSpriteRender::update(){
	for(vector<uiSprite*>::iterator it = sprites.begin();it != sprites.end();++it){
		(*it)->update();
	}
}

void uiSpriteRender::draw(){
	bind();
	for(vector<uiSprite*>::const_iterator it = sprites.begin();it != sprites.end();++it){
		draw(**it);
	}
	unbind();
}



void uiSpriteRender::setup(std::string shaderName)
    {
        
    try {
            mShader = gl::GlslProg( loadAsset( shaderName + ".vsh" ), loadAsset( shaderName + ".fsh" ) );
            
            
            glBindAttribLocation(mShader.getHandle(), ATTRIB_VERTEX, "position");
            glBindAttribLocation(mShader.getHandle(), ATTRIB_UV, "uv");
            
            glLinkProgram(mShader.getHandle());
            
            
            uWorldMatrix= glGetUniformLocation(mShader.getHandle(), "worldMatrix");
			worldMatrix.setOrtho( 0, getWindowWidth(), getWindowHeight(), 0, -100, 100 );
            
            mShader.unbind();
            
        }
        catch( gl::GlslProgCompileExc &exc ) {
            std::cout << "Shader compile error: " << std::endl;
            std::cout << exc.what();
        }
        catch( ... ) {
            std::cout << "Unable to load shader" << std::endl;
        }

}

void uiSpriteRender::setup(){
    setup("ShaderFlat");
}

void uiSpriteRender::resize(float width,float height){
    worldMatrix.setOrtho( 0, width, height, 0, -100, 100 );
}

void uiSpriteRender::bind(){
    mShader.bind();
     
    glUniformMatrix4fv(uWorldMatrix, 1, 0,worldMatrix.getProjectionMatrix().m);
    
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_UV);
 }


void uiSpriteRender::draw(uiSprite &sprite){

    if(!sprite.isTextureLoaded) return;
    
	sprite.getTexture().bind();
  //  std::cout << "id from sprite obj " << sprite.getTexture().getId() << "\n-----\n"  << std::endl;

    
    //std::cout << sprite.getTexture().getId();
	GLfloat *pointer = sprite.data;
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 6 * sizeof(GLfloat), pointer);

    pointer +=3;
    glVertexAttribPointer(ATTRIB_UV, 3, GL_FLOAT, 0, 6 * sizeof(GLfloat), pointer);
   
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
	sprite.getTexture().unbind();
}

 void uiSpriteRender::unbind(){
	mShader.unbind();

    glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_UV);
    
    
   GLenum errCode;
   errCode = glGetError();
   if ((errCode ) != GL_NO_ERROR) {
       std::cout << "\n GL ERROR ";
           cout << ": "<< errCode;
           if(errCode == GL_INVALID_ENUM)cout <<" GL_INVALID_ENUM";
           if(errCode == GL_INVALID_VALUE)cout <<"GL_INVALID_VALUE";
           if(errCode == GL_INVALID_OPERATION)cout <<"GL_INVALID_OPERATION";
           if(errCode == GL_OUT_OF_MEMORY)cout <<"GL_OUT_OF_MEMORY";
           cout <<"\n";
    }

 }
