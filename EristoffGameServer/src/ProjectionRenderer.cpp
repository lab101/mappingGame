//
//  ProjectionRenderer.cpp
//  basicApp
//
//  Created by Kris Temmerman on 09/10/12.
//
//

#include "ProjectionRenderer.h"


void ProjectionRenderer::setup()
{
    projectionWidth=2250*0.8;
    
    projectionHeight=projectionWidth/1.77777777;
    projectorX=0;
	projectorY=-500;
	projectorZ=3100;
	//projectionWidth=2100;
	
	buildingOffsetX=-857;
	buildingOffsetY=626-25;
	
    vertices =NULL;
    indices =NULL;
    
    
    globalX=0;
    globalY =0;
    globalScale =0.8;

    try {
        
        
        mShader = gl::GlslProg( loadAsset( "shaders/projectionShader.vsh" ), loadAsset( "shaders/projectionShader.fsh" ) );
        
        
        
        
        
        
    }
    catch( gl::GlslProgCompileExc &exc ) {
        std::cout << "Shader compile error: " << std::endl;
        std::cout << exc.what();
    }
    catch( ... ) {
        std::cout << "Unable to load shader" << std::endl;
    }
    
    
	program =  mShader.getHandle();
    
	glUseProgram(program);
    

	aVertex= 	glGetAttribLocation (program,"position");

    aUV= 	glGetAttribLocation (program,"uv");
    
    glUseProgram(0);

}


void ProjectionRenderer::draw()
{
	glUseProgram(program);
    glEnable(GL_DEPTH_TEST);
    
    glBindTexture(GL_TEXTURE_2D,  texture);
   
    glEnableVertexAttribArray(aVertex);
  
    glEnableVertexAttribArray(aUV);


    float *p  = vertices;
    
	glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5,p);
    p+=3;
      glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float)* 5,p );

  
    
    glDrawElements(GL_TRIANGLES,numIndices , GL_UNSIGNED_INT, indices);

	
    glDisableVertexAttribArray(aVertex);
 
    glDisableVertexAttribArray(aUV);
	glUseProgram(0);


}