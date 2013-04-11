

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/gl/GlslProg.h"

#include "cinder/Matrix44.h"
#include "ProjectionCamera.h"
#include "Resources.h"
#include "npCinderAssimpLoader.h"
#include "cinder/Filesystem.h"
#include "cinder/Utilities.h"

#include "BasicMeshRenderer.h"
#include "npMesh.h"
#include "cinder/params/Params.h"

#include "cinder/gl/Fbo.h"
#include "MeshGenerator.h"
#include "npMaterial.h"
#include "ProjectionRenderer.h"
#include "ProjectionSaveLoad.h"


using namespace boost;



using namespace ci;
using namespace ci::app;

#include <list>
using namespace std;


class BasicApp : public AppBasic {
public:
    
	void mouseDrag( MouseEvent event );
    void mouseDown( MouseEvent event );
    void mouseUp( MouseEvent event );
	void keyDown( KeyEvent event );
    void keyUp( KeyEvent event );
	void setup();
	void update();
	void draw();
    void togleState();
    void dataSave();
    void save();
    void saveFile();
    void loadFile();
    void moveLight();
    void prepareSettings(Settings *settings);
	params::InterfaceGl		mParams;
	gl::GlslProg	mProgram;
    
	list<Vec2f>		mPoints;
	ProjectionCamera camera;
	//DestructibleBlock testBlok;
    void prepStateFine();
	GLint	uPerspectiveMatrix ;
	GLint uWorldMatrix;
    
	npCinderAssimpLoader loader;
	BasicMeshRenderer meshRenderer;
    ColorMeshRenderer colorMeshRenderer;
    MeshGenerator meshGenerator;
    ProjectionRenderer projectionRenderer;
    
    ProjectionSaveLoad saveLoad;
    float					projectorX;
    float					projectorY;
    float					projectorZ;
    
    float					projectionWidth;
    float					projectionHeight;
    
    float					buildingOffsetX;
    float					buildingOffsetY;

    float coinX;
    float coinY;
    float coinZ;
    float coinRot;
    float coinScale;
    float				frustrum;
    void  switchTexture();
    vector<npMaterial *> materials;
    int currentMaterial;
    
    
    float SCREEN_W;
    float SCREEN_H;
    
    npMesh *lowPoly;
    npMesh *coin;
    int state ;
    gl::Fbo hitFbo;
   gl::Fbo shadowFbo;
    int previewState;
};
void  BasicApp::moveLight()
{

    camera.moveLight();
}
void  BasicApp::switchTexture()
{
    currentMaterial++;
    if (currentMaterial==materials.size())currentMaterial =0;
    lowPoly->material = materials[currentMaterial];
    
    
}
void BasicApp::mouseDrag( MouseEvent event )
{
    if (state ==1)
    {
        
        meshGenerator.mouseMove(event.getX(), event.getY());
    }
	
}
void BasicApp::mouseDown( MouseEvent event )
{
    if (state ==1)
    {
        
        meshGenerator.mouseDown(event.getX(), event.getY());
    }
}

void BasicApp::mouseUp ( MouseEvent event )
{
    if (state ==1)
    {
        meshGenerator.ctrlDown= event.isControlDown();
        meshGenerator.shiftDown  = event.isShiftDown();
    	meshGenerator.mouseUp (event.getX(), event.getY());
        
    }
	
}
void BasicApp::keyUp ( KeyEvent event )
{
    //float pivot=(min(min(color.x, color.y), color.z)+max(max(color.x, color.y), color.z))/2.0;
    //color.xyz -= vec3( pivot );
    //color.xyz *= saturationScale;
    //color.xyz += vec3( pivot );
   
    
//    pixelColor.rgb = ((pixelColor.rgb - 0.5f) * max(Contrast, 0)) + 0.5f;
    
    // Apply brightness.
  //  pixelColor.rgb += Brightness;

    if (state==1)
    {
    }
    
}
void BasicApp::keyDown( KeyEvent event )
{
    
    if (state==1)
    {
        //console()<< event.getCode() << event.SHIFT_DOWN<<endl ;
        if( event.getCode() ==event.KEY_DOWN  )
        {
            meshGenerator.moveSelected(0, 1);
        }
        if( event.getCode() ==event.KEY_UP  )
        {
            meshGenerator.moveSelected(0, -1);
            
        }
        if( event.getCode() ==event.KEY_LEFT  )
        {
            meshGenerator.moveSelected(-1, 0);
        }
        if( event.getCode() ==event.KEY_RIGHT  )
        {
            meshGenerator.moveSelected(1, 0);
        }
    }
	if( event.getChar() == 'f' )
		setFullScreen( ! isFullScreen() );
}
void BasicApp::togleState()
{
    if (state==0)
    {
        state =1;
        prepStateFine();
        mParams.setOptions( "text", "label=`positioning`" );
    }else if (state==1)
    {
        //mParams.setOptions( "text", "label=`FineTuning`" );
        // state =0;
    }
    
    
    
}
void BasicApp::save()
{
    if (state ==0) return;
    if (previewState ==0)
    {
        previewState =1;
        meshGenerator.updateRenderer(projectionRenderer);
        
    }else
    {
        previewState =0;
        
    }
    
    
}
void BasicApp::setup()
{
    meshGenerator.setup();
    projectionRenderer.setup();
    colorMeshRenderer.setup();
    //string p = getResourcePath( "vert.glsl" ).string();
    // console() << p << endl;
	//setWindowSize (1400,1050);
    state =0;
	projectorX =projectionRenderer.projectorX;
	projectorY=projectionRenderer.projectorY;;
	projectorZ =projectionRenderer.projectorZ;
	projectionWidth =projectionRenderer.projectionWidth;
	projectionHeight=projectionRenderer.projectionHeight;
	buildingOffsetX =projectionRenderer.buildingOffsetX;
	buildingOffsetY =projectionRenderer.buildingOffsetY;
    previewState =0;
    
    
    coinX=0;
    coinY=0;
    coinZ =0;
    coinRot =0;
    coinScale=1;
    
    
    /* projectorX =0;
     projectorY=0;
     projectorZ =2000;
     projectionWidth =1872,
     projectionHeight=1375,
     buildingOffsetX =0;
     buildingOffsetY =0;
     
     */
    
    
    
	mParams = params::InterfaceGl( "App parameters", Vec2i( 300, 400 ) );
	/*mParams.addParam( "projectorX", &projectorX, "min=-10000 max=10000 step=0.5 keyIncr=x keyDecr=X" );
	mParams.addParam( "projectorY", &projectorY, "min=-10000 max=10000 step=0.5 keyIncr=y keyDecr=Z" );
	mParams.addParam( "projectorZ", &projectorZ, "min=-10000  max=10000 step=0.5 keyIncr=y keyDecr=Z" );
	mParams.addSeparator();
	mParams.addParam( "projectionWidth", &projectionWidth, "min=0.1 max=10000 step=0.1 keyIncr=w keyDecr=W" );
	mParams.addParam( 	"projectionHeight", &projectionHeight, "min=0.1 max=10000 step=0.1 keyIncr=h keyDecr=H" );
    mParams.addSeparator();
    
	mParams.addParam( "buildingOffsetX", &buildingOffsetX, "min=-10000 max=10000 step=0.1 keyIncr=w keyDecr=W" );
	mParams.addParam( 	"buildingOffsetY", &buildingOffsetY, "min=-10000 max=10000 step=0.1 keyIncr=h keyDecr=H" );
    */
    
    mParams.addParam( "globalScale", &camera.globalScale, "min=0.5 max=1.5 step=0.0001 keyIncr=x keyDecr=X" );
    mParams.addParam( "globalX", &camera.globalX, "min=-1 max=1 step=0.0001 keyIncr=x keyDecr=X" );
	mParams.addParam( "globalY", &camera.globalY, "min=-1 max=1 step=0.0001 keyIncr=y keyDecr=Z" );
	

    
    mParams.addSeparator();
    mParams.addButton( "switch state", std::bind( &BasicApp::togleState, this ) );
    mParams.addText( "text", "label=`positioning`" );
    mParams.addSeparator();
    mParams.addButton( "preview", std::bind( &BasicApp::save, this ) );
    
    
    mParams.addSeparator();
    mParams.addButton( "switchT", std::bind( &BasicApp::switchTexture, this ) );
    mParams.addSeparator();
    
     mParams.addButton( "moveLight", std::bind( &BasicApp::moveLight , this ) );
    
    //mParams.addSeparator();
   // mParams.addButton( "load", std::bind( &BasicApp::dataLoad , this ) );
    
    
    
    mParams.addSeparator();
    mParams.addButton( "save file", std::bind( &BasicApp::saveFile, this ) );
    mParams.addSeparator();
    mParams.addButton( "load file", std::bind( &BasicApp::loadFile  , this ) );
  
    //mParams.addSeparator();
   // mParams.addButton( "save", std::bind( &BasicApp::dataSave , this ) );
    

    
    
	meshRenderer.setup();
	meshRenderer.camera =&camera;
    
    cinder::Matrix44f mat;
    mat.setToIdentity();
    //mat.rotate(Vec3<float>(1,0,0) , -3.14159265/2);
    mat.scale(0.01)  ;
	string p = getAssetPath( "simpleMeshFinal2.dae" ).string();
    console()<<p<< "test";
    loader.preMatrix =mat;
	loader.load(p);
    p = getAssetPath( "attackpowerstanding.dae" ).string();
    //console()<<p<< "test";
    
	loader.load(p);
	lowPoly =loader.getMeshByName("STAIRS");
    lowPoly->objectMatrix.setToIdentity();
    lowPoly->objectMatrix.rotate(Vec3f(1,0,0), -3.14/2);
	lowPoly->resolveModelMatrix();
    
    npMaterial *m55 =new npMaterial();
    m55->setColorTexture();
    coin = loader.getMeshByName("WolfREDUCED");
    coin->material = m55;
    currentMaterial =0;
    
    npMaterial *m1 =new npMaterial();
    m1->setColorTexture("simpleMeshFinal2inv.png");
    materials.push_back(m1);
    
    
    npMaterial *m2 =new npMaterial();
    m2->setColorTexture("simpleMeshFinal2.png");
    materials.push_back(m2);
    
    npMaterial *m3 =new npMaterial();
    m3->setColorTexture("uvgrid.png");
    materials.push_back(m3);
    
 
    npMaterial *m4 =new npMaterial();
    m4->setColorTexture("white.jpg");
    materials.push_back(m4);
    
    
    lowPoly->material= m1;
    meshGenerator.screenW  =SCREEN_W;
    meshGenerator.screenH  =SCREEN_H;
    if (state==1){
        camera.set(projectorX,projectorY,projectorZ,projectionWidth,projectionHeight,buildingOffsetX,buildingOffsetY);
        meshGenerator.init(lowPoly, &camera);
        
    }
    hitFbo = gl::Fbo( SCREEN_W,SCREEN_H );
    
    
      
    gl::Fbo::Format formatS;
    formatS.enableDepthBuffer(true,true);
    shadowFbo= gl::Fbo(1024*4,1024*4  ,formatS);

    meshRenderer.shadowTexture =  shadowFbo.getDepthTexture().getId();
	
}
void BasicApp::saveFile()
{
    saveLoad.save (meshGenerator,camera);
    meshGenerator.updateRenderer(projectionRenderer);
}
void BasicApp::loadFile()
{
    saveLoad.load(meshGenerator,camera);
     meshGenerator.updateRenderer(projectionRenderer);
   // meshGenerator.update();
}
void BasicApp::dataSave()
{
    console()<< endl <<endl;
    
    /* console()<< "projectorY="<<projectorY<<";"<<endl;
     console()<< "projectorZ="<<projectorZ<<";"<<endl;
     
     console()<< "projectionWidth="<<projectionWidth<<";"<<endl;
     console()<< "projectionHeight="<<projectionHeight<<";"<<endl;
     
     console()<< "buildingOffsetX="<<buildingOffsetX<<";"<<endl;
     console()<< "buildingOffsetY="<<buildingOffsetY<<";"<<endl<<endl;
     */
    
    console()<< "globalScale="<<camera.globalScale<<";"<<endl;
    console()<< "globalX="<<camera.globalX<<";"<<endl;
    console()<< "globalY="<<camera.globalY<<";"<<endl;
   
    
    meshGenerator.save(projectionRenderer);
    
}
void BasicApp::update()
{
    if (state==0){
        camera.set(projectorX,projectorY,projectorZ,projectionWidth,projectionHeight,-buildingOffsetX,-buildingOffsetY);
    }else if (state==1)
    {
        meshGenerator.update();
         camera.set(projectorX,projectorY,projectorZ,projectionWidth,projectionHeight,-buildingOffsetX,-buildingOffsetY);
    }
	//lowPoly->objectMatrix.setToIdentity();
	//lowPoly->objectMatrix.translate(Vec3f(-buildingOffsetX,-buildingOffsetY,0));
    coin->objectMatrix.setToIdentity();
    
    
    coin->objectMatrix.translate(Vec3<float>(coinX,coinY,coinZ));
    coin->objectMatrix.scale(Vec3<float>(coinScale,coinScale,coinScale));
    coin->objectMatrix.rotate (Vec3<float> (1,0,0),coinRot);
    coin->objectMatrix.rotate (Vec3<float> (0,1,0),coinRot/3);
    coin->objectMatrix.rotate (Vec3<float> (0,0,1),coinRot/2);
    coin->resolveModelMatrix();
    
}
void BasicApp::draw()
{
    
    shadowFbo.bindFramebuffer();
    glPolygonOffset(0.2f,0.3f);
    glEnable(GL_POLYGON_OFFSET_FILL);
     glEnable(GL_DEPTH_TEST);
    glViewport(0,0,1024*4,1024*4);
    gl::clear( Color( 0.0f, 1.0f, 0.0f ),true );
    
    
    colorMeshRenderer.camera =&camera;
    colorMeshRenderer.startShadow();
    
    
    
    colorMeshRenderer.draw( lowPoly);
    
    
    
    
    colorMeshRenderer.stop();
    glDisable(GL_POLYGON_OFFSET_FILL);
    shadowFbo.unbindFramebuffer();
    
    meshRenderer.shadowTexture = shadowFbo.getDepthTexture().getId();
    
    
    glViewport(0,0,SCREEN_W,SCREEN_H);

	
    
    
    if (state==0){
        
        
        glEnable(GL_DEPTH_TEST);
		gl::clear( Color( 1.0f, 0.0f, 0.0f ),true );
        
        meshRenderer.start();
        
        meshRenderer.draw(lowPoly);
        meshRenderer.stop();
        
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
        
        
        
        
        glDisable(GL_DEPTH_TEST);
        
    }
    if (state==1)
    {
        if (previewState==1){
            
            
                  
            gl::clear( Color( 0,0 , 0.0f ),true );
            
            hitFbo.bindFramebuffer();
            //glViewport(0,0,windowW/2,windowH/2);
            
            gl::clear( Color( 0,0 , 0.0f ),true );
            
            glEnable(GL_DEPTH_TEST);
            
            
            meshRenderer.start();
            //  console() << "draw"<<lowPoly->material->colortexture<<endl;
            meshRenderer.draw(lowPoly);
           // meshRenderer.draw(coin);
            meshRenderer.stop();
            
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
            
            
            
            
            //  glDisable(GL_DEPTH_TEST);
            hitFbo.unbindFramebuffer();
            //  gl::draw( hitFbo.getTexture() );
            projectionRenderer.texture = hitFbo.getTexture().getId();
            projectionRenderer.draw();
            
        }
        else
        {
            
            glDisable(GL_DEPTH_TEST);
            gl::clear( Color( 0.0f, 0.0f, 0.0f ),true );
            meshGenerator.draw();
        }
        
    }
    
    
    // Draw the interface
	//gl::draw(shadowFbo.getDepthTexture());
    params::InterfaceGl::draw();
    
    
    
    
    
    
	
}
void BasicApp::prepareSettings(Settings *settings){
	//settings->setFullScreen();
	//settings->setWind*
    SCREEN_W = 1920;//1280;
	SCREEN_H =1080; //960;
    
	settings->setWindowPos(0,0);
	
	settings->setBorderless();
	// settings->setFullScreen();
	//settings->setWindowSize(1400,1050);
	settings->setWindowSize(  SCREEN_W ,  SCREEN_H);
}




void BasicApp::prepStateFine()
{
    meshGenerator.init(lowPoly, &camera);
    
}



CINDER_APP_BASIC( BasicApp, RendererGl )