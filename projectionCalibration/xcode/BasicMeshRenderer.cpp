#include "BasicMeshRenderer.h"
#include "npProgramLoader.h"
#include "cinder/app/AppBasic.h"

using namespace ci;
void BasicMeshRenderer::setup()
{
  
	npProgramLoader pl;
	program = pl.loadProgram("basicShader");

	pl.linkProgram();

	glUseProgram(program);

	uPerspectiveMatrix  =glGetUniformLocation(program, "perspectiveMatrix");
	uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
	uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
	aVertex= 	glGetAttribLocation (program,"position");
	aNormal= 	glGetAttribLocation (program,"normal");
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
	


	
	

		glEnableVertexAttribArray(aVertex);
		glEnableVertexAttribArray(aNormal);
	
}
void BasicMeshRenderer::draw(const npMesh *mesh)
{
 
		glUniformMatrix4fv(uObjectMatrix,1,false, mesh->objectMatrix.m );
	glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
		
    	
	glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * mesh->stride,(GLvoid*) (sizeof(float) * 0));
    glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, sizeof(float)* mesh->stride,(GLvoid*) (sizeof(float) *3 ));
   
   // console() <<"? " <<  testBlok.indexBuffer << vertexPos << testBlok.vertexBuffer<<endl;;
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);

    
    glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);
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
	glUseProgram(0);
}
