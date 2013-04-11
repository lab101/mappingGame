//
//  ColorMeshRenderer.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 04/10/12.
//
//

#include "ColorMeshRenderer.h"





void ColorMeshRenderer::setup()
{
    
    try {
        
        
        mShader = gl::GlslProg( loadAsset( "shaders/colorShader.vsh" ), loadAsset( "shaders/colorShader.fsh" ) );
        
        
        
        
        
        
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
    
	uPerspectiveMatrix  =glGetUniformLocation(program, "perspectiveMatrix");
	uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
	uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
    uColor = glGetUniformLocation(program,"color");
	aVertex= 	glGetAttribLocation (program,"position");
	
    idMatrix.setToIdentity();
    worldMatrix.setToIdentity();
     worldMatrix.scale( Vec2<float> (2,-2));
    worldMatrix.translate(Vec3<float>(-0.5,-0.5,0));
    
    r =1.0f;
    g=0.0f;
    b=0.0f;
    a=1.0f;
    glUseProgram(0);

}
void ColorMeshRenderer::startShadow()
{
    
    glUseProgram(program);
    
    glUniformMatrix4fv(uPerspectiveMatrix,1,false,camera->perspectiveMatrixShadow.m );
    glUniformMatrix4fv(uWorldMatrix,1,false,camera->worldMatrixShadow.m );
	
    
   /// glUniformMatrix4fv(uPerspectiveMatrix,1,false,camera->perspectiveMatrix.m );
    ///glUniformMatrix4fv(uWorldMatrix,1,false,camera->worldMatrix.m );
	
	
    
    glEnableVertexAttribArray(aVertex);
    
}
void ColorMeshRenderer::start()
{
    
    glUseProgram(program);
    
    glUniformMatrix4fv(uPerspectiveMatrix,1,false,camera->perspectiveMatrix.m );
    glUniformMatrix4fv(uWorldMatrix,1,false,camera->worldMatrix.m );
	
    
    
	
	
    
    glEnableVertexAttribArray(aVertex);
    	
}
void ColorMeshRenderer::startFlat()
{
    
    glUseProgram(program);
    
    glUniformMatrix4fv(uPerspectiveMatrix,1,false, idMatrix.m );
    glUniformMatrix4fv(uWorldMatrix,1,false, worldMatrix.m );
	
    
    
	
	
    
    glEnableVertexAttribArray(aVertex);
    
}
void ColorMeshRenderer::drawFlat(vector<Vec2<float> > vertices ,GLenum type)
{
    //console()<< mesh->name << endl<< mesh->objectMatrix<< endl ;
    glUniformMatrix4fv(uObjectMatrix,1,false ,  idMatrix);
    glUniform4f(uColor,r,g,b,a );
	
    
    
	glVertexAttribPointer(aVertex, 2, GL_FLOAT, GL_FALSE, 0,vertices.data());
    
    // console() <<"? " <<  testBlok.indexBuffer << vertexPos << testBlok.vertexBuffer<<endl;;
    

  
    
    glDrawArrays(type , 0, vertices.size());
}
void ColorMeshRenderer::drawNonBuffer(const npMesh *mesh)
{
    //console()<< mesh->name << endl<< mesh->objectMatrix<< endl ;
    glUniformMatrix4fv(uObjectMatrix,1,false , mesh->objectMatrix.m );
   
	
    
    
	glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * mesh->stride,mesh->vertices);
    
    // console() <<"? " <<  testBlok.indexBuffer << vertexPos << testBlok.vertexBuffer<<endl;;
    

    
    glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, mesh->indices);
}
void ColorMeshRenderer::draw(const npMesh *mesh)
{
    //console()<< mesh->name << endl<< mesh->objectMatrix<< endl ;
    glUniformMatrix4fv(uObjectMatrix,1,false , mesh->objectMatrix.m );
    glUniform4f(uColor,r,g,b,a );
	//glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
    
    
	glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * mesh->stride,(GLvoid*) mesh->vertices);
    
    // console() <<"? " <<  testBlok.indexBuffer << vertexPos << testBlok.vertexBuffer<<endl;;
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    
    
    glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT,  mesh->indices);
}
void ColorMeshRenderer::draw(const vector<npMesh *> &meshes )
{
	for (int i=0;i<meshes.size();i++  )
	{
        draw(meshes [i]);
	}
}
void ColorMeshRenderer::stop()
{
    
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glDisableVertexAttribArray(aVertex);
    	glUseProgram(0);
}
