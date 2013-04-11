

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/gl/GlslProg.h"
#include "DestructibleBlock.h"
#include "cinder/Matrix44.h"
#include "ProjectionCamera.h"
#include "Resources.h"

#include "cinder/Filesystem.h"
using namespace boost;



using namespace ci;
using namespace ci::app;

#include <list>
using namespace std;


class BasicApp : public AppBasic {
 public:

	void mouseDrag( MouseEvent event );
	void keyDown( KeyEvent event );
	void setup();
	void update();
	void draw();

	gl::GlslProg	mProgram;
	Matrix44f test;
	list<Vec2f>		mPoints;
	ProjectionCamera camera;
	DestructibleBlock testBlok;

	GLint	uPerspectiveMatrix ;
		GLint uWorldMatrix;
};

void BasicApp::mouseDrag( MouseEvent event )
{

	mPoints.push_back( event.getPos() );
}

void BasicApp::keyDown( KeyEvent event )
{
	if( event.getChar() == 'f' )
		setFullScreen( ! isFullScreen() );
}
void BasicApp::setup()
{
	console() << "Setup" << endl;
	
	//char *fs = loadFile("data/shaders/vert.glsl");
	//
	fs::path vertPath( "data/shaders/vert.glsl" );
	fs::path fragPath( "data/shaders/frag.glsl" );



	if( fs::exists(vertPath ) )
	{
		mProgram = gl::GlslProg( loadFile(vertPath.native()),loadFile(fragPath.native()));
			

	}
	else 
	{
	console() << "shaders not loaded " <<endl;

	}
	mProgram.bind();
	uPerspectiveMatrix  = mProgram.getUniformLocation( "perspectiveMatrix");
	uWorldMatrix = mProgram.getUniformLocation( "worldMatrix");
	
	mProgram.unbind();
//	console() << "program: "<<mProgram.getHandle() <<endl;
	
		console() << "matri"<< uPerspectiveMatrix<< " " << uWorldMatrix <<endl;

//	console() << "program: "<<mProgram.getHandle()<<" atrib" <<test <<endl;
	testBlok.setup(-500,-500,1000,1000,100,10,10);
	camera.setup();
	
	
}
void BasicApp::update()
{
		
}
void BasicApp::draw()
{
	 
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
		gl::clear( Color( 0.0f, 0.9f, 0.0f ),true );
		mProgram.bind();
		
		  glBindBuffer(GL_ARRAY_BUFFER,testBlok.vertexBuffer);
		  mProgram.uniform("perspectiveMatrix",camera.perspectiveMatrix);
		    mProgram.uniform("worldMatrix",camera.worldMatrix);
    	GLint vertexPos= 	mProgram.getAttribLocation("position");
	
		glEnableVertexAttribArray(vertexPos);
    glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3,(GLvoid*) (sizeof(float) * 0));
    //glVertexAttribPointer(normalPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3,(GLvoid*) (sizeof(float) *3 ));
   
   // console() <<"? " <<  testBlok.indexBuffer << vertexPos << testBlok.vertexBuffer<<endl;;
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  testBlok.indexBuffer);

    
    glDrawElements(GL_TRIANGLES,testBlok.numIndices , GL_UNSIGNED_INT, (void*)0);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	   glBindBuffer(GL_ARRAY_BUFFER,0);
		mProgram.unbind();
	//mProgram.uniform("prespectiveMatrix",)






		 GLenum errCode;
        errCode = glGetError();
        if ((errCode ) != GL_NO_ERROR) {
           console()  << "\n GL ERROR at: ";
           console()  << " code: "<< errCode;
            if(errCode == GL_INVALID_ENUM)console()  <<" GL_INVALID_ENUM";
            if(errCode == GL_INVALID_VALUE)console() <<"GL_INVALID_VALUE";
            if(errCode == GL_INVALID_OPERATION)console()  <<"GL_INVALID_OPERATION";
            if(errCode == GL_OUT_OF_MEMORY)console()  <<"GL_OUT_OF_MEMORY";
           console()  <<"\n";
        };















	return;
	//mProgram.bind();
	//mProgram.uniform("prespectiveMatrix",)

	//mProgram.unbind();
	gl::setMatricesWindow( getWindowSize() );
	
	gl::clear( Color( 0.1f, 0.1f, 0.1f ) );


	glColor3f( 1.0f, 0.5f, 0.25f );
	
	
	glBegin( GL_LINE_STRIP );

	for( list<Vec2f>::iterator pointIter = mPoints.begin(); pointIter != mPoints.end(); ++pointIter ) {
		glVertex2f( *pointIter );
	}

	glEnd();
	
}


CINDER_APP_BASIC( BasicApp, RendererGl )