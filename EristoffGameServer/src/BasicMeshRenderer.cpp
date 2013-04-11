#include "BasicMeshRenderer.h"

#include "cinder/app/AppBasic.h"

using namespace ci;
void BasicMeshRenderer::setup()
{
  
    try {
        
        
        mShader = gl::GlslProg( loadAsset( "shaders/basicShader.vsh" ), loadAsset( "shaders/basicShader.fsh" ) );
        
        
        
        
        
              
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

	uPerspectiveMatrix  =glGetUniformLocation(program, "perspectiveMatrix");
	uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
    
    uPerspectiveMatrixShadow  =glGetUniformLocation(program, "perspectiveMatrixShadow");
	uWorldMatrixShadow = glGetUniformLocation(program,"worldMatrixShadow");

    
    
	uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
    uNormalMatrix = glGetUniformLocation(program,"normalMatrix");
    uLightPos = glGetUniformLocation(program,"lightPos");
    
    uTextureMain =  glGetUniformLocation(program,"textureMain");
    uTextureShadow =glGetUniformLocation(program,"textureShadow");
    
	aVertex= 	glGetAttribLocation (program,"position");
	aNormal= 	glGetAttribLocation (program,"normal");
    //aTangent= 	glGetAttribLocation (program,"tangent");
    aUV= 	glGetAttribLocation (program,"uv");
    
    glUniform1i(uTextureMain, 0);
        glUniform1i(uTextureShadow, 1);
			glUseProgram(0);
	/*
	if( fs::exists(vertPath ) )
	{
		mProgram = gl::GlslProg( loadFile(vertPath.native()),loadFile(fragPath.native()));
		console() << "shaders found " <<endl;

	}
	else 
	{
	console() << "shaders not loaded BasicMesh" <<endl;

	}
	mProgram.bind();
	uPerspectiveMatrix  = mProgram.getUniformLocation( "perspectiveMatrix");
	uWorldMatrix = mProgram.getUniformLocation( "worldMatrix");
	aVertex= 	mProgram.getAttribLocation("position");
	aNormal= 	mProgram.getAttribLocation("normal");
	mProgram.unbind();*/
}
void BasicMeshRenderer::start()
{
    
		glUseProgram(program);

		glUniformMatrix4fv(uPerspectiveMatrix,1,false,camera->perspectiveMatrix.m );
		glUniformMatrix4fv(uWorldMatrix,1,false,camera->worldMatrix.m );
	
    glUniformMatrix4fv(uPerspectiveMatrixShadow,1,false,camera->perspectiveMatrixShadow.m );
    glUniformMatrix4fv(uWorldMatrixShadow,1,false,camera->worldMatrixShadow.m );
    
    glUniform3f(uLightPos, camera->lightPos.x, camera->lightPos.y, camera->lightPos.z);

	//console()<<" ?"<< shadowTexture << uWorldMatrixShadow<<uPerspectiveMatrixShadow;
	glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowTexture);
    glActiveTexture(GL_TEXTURE0);
		glEnableVertexAttribArray(aVertex);
		glEnableVertexAttribArray(aNormal);
    	//glEnableVertexAttribArray(aTangent);
    glEnableVertexAttribArray(aUV);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
	
}
void BasicMeshRenderer::drawNonBuffer(const npMesh *mesh)
{
      //   glBindTexture(GL_TEXTURE_2D, shadowTexture);
    //console()<< mesh->name << endl<< mesh->objectMatrix<< endl ;
    glUniformMatrix4fv(uObjectMatrix,1,false , mesh->objectMatrix.m );
    glUniformMatrix3fv(uNormalMatrix,1,false,mesh->normalMatrix.m  );

    float * pointer = mesh->vertices ;
	glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * mesh->stride,pointer);
    pointer+=3;
    glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, sizeof(float)* mesh->stride,pointer);
       pointer+=3;
       glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float)* mesh->stride,pointer);

    
  
    
    
    glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, mesh->indices);
}


void BasicMeshRenderer::draw(const npMesh *mesh)
{
    if (mesh->material)
   glBindTexture(GL_TEXTURE_2D, mesh->material->colortexture);
  //   glBindTexture(GL_TEXTURE_2D, shadowTexture);
 //console()<< mesh->name << endl<< mesh->objectMatrix<< endl ;
    glUniformMatrix4fv(uObjectMatrix,1,false , mesh->objectMatrix.m );
    glUniformMatrix3fv(uNormalMatrix,1,false,mesh->normalMatrix.m  );
//	glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
	float * pointer  = mesh->vertices;
    
    glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * mesh->stride,(GLvoid*) pointer);
    pointer+=3;
    glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, sizeof(float)* mesh->stride,(GLvoid*) pointer);
    pointer +=3;
    glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float)* mesh->stride,(GLvoid*)pointer);
    
  
	//glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * mesh->stride,(GLvoid*) (sizeof(float) * 0));
    //glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, sizeof(float)* mesh->stride,(GLvoid*) (sizeof(float) *3 ));
     // glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float)* mesh->stride,(GLvoid*) (sizeof(float) *6 ));
   
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);

	glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)mesh->indices);

   // glDrawElements(GL_LINES,mesh->numIndices , GL_UNSIGNED_INT, (void*)mesh->indices);
   // glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);
}
void BasicMeshRenderer::draw(const vector<npMesh *> &meshes )
{
	for (int i=0;i<meshes.size();i++  )
	{
	draw(meshes [i]);
	}
}
void BasicMeshRenderer::stop()
{
   
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	   glBindBuffer(GL_ARRAY_BUFFER,0);
	   glDisableVertexAttribArray(aVertex);
	    glDisableVertexAttribArray(aNormal);
       // glDisableVertexAttribArray(aTangent);
     glDisableVertexAttribArray(aUV);
	glUseProgram(0);
    glActiveTexture(GL_TEXTURE0);
}
