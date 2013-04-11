#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/params/Params.h"

#include <sstream>
#include <iostream>

#include "GameController.h"
#include "NetworkController.h"
#include "PrizeController.h"
#include "uiSprite.h"
#include "uiSpriteRender.h"
#include "SettingManager.h"

// ui
#include "ScorePanel.h"
#include "GameUI.h"
#include "VideoSprite.h"
#include "VideoLayer.h"
#include "SoundController.h"
#include "MainVisuals.h"
#include "ColorAdjustmentRenderer.h"
#include "AntTweakBar.h"


#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.



using namespace ci;
using namespace ci::app;
using namespace std;


class EristoffGameServerApp : public AppBasic {
private:
	
	NetworkController	mNetworkController;
	
    params::InterfaceGl	mSettingsBar;
	
	VideoLayer mVideoLayer;
	uiSprite testSprite2;
    
	uiSpriteRender	mSpriteRender;
    float a;
    ScorePanel mScorePanel;
    GameUI mGameUI;
    
    Vec2f mouseToIPadCoord(Vec2f mouse);
    MainVisuals *mainVisuals;
	std::string fakeMouseIP;
	
    void newPlayer();
	
	float outroDelayTimer;
    
	gl::Fbo mainFbo;
    ColorAdjustmentRenderer adjRenderer;
public:
	void setup();
	void prepareSettings( Settings *settings );
	void mouseDown( MouseEvent event );
	void mouseMove( MouseEvent event );
	void keyDown( KeyEvent event);
	void keyUp( KeyEvent event);
	void update();
	void draw();
	void resize(ResizeEvent event);
    void startIntro();
	void startGame();
	
    void newGame();
	void startOutro();
	void startOutroDelayed();
	
	void sendScoresToSlaveServer();

	void writeScores(std::vector<Player> players,bool firstElement);
};

void EristoffGameServerApp::setup()
{
	console() << "setup";
    //setFrameRate( 1000.0f );
    mainVisuals =new MainVisuals(timeline());
    
    mainVisuals->setup();
	mainFbo= gl::Fbo( 1920,1080);

    adjRenderer.setup();
   adjRenderer.texture = mainFbo.getTexture().getId();
    
    
	mNetworkController.setup();
    GameController::Instance()->setup();
	
	GameController::Instance()->windowWidth = getWindowWidth();
	GameController::Instance()->windowHeight = getWindowHeight();
	
    
    mNetworkController.sNewPlayer.connect(boost::bind(&GameController::addPlayer, GameController::Instance(),boost::arg<1>::arg(),boost::arg<2>::arg(),boost::arg<3>::arg(),boost::arg<4>::arg()));
    //mNetworkController.sNewPlayer.connect(boost::bind(&EristoffGameServerApp::newPlayer, this));
	
    mNetworkController.sUpdatePlayer.connect(boost::bind(&GameController::updatePlayer, GameController::Instance(),boost::arg<1>::arg(),boost::arg<2>::arg(),boost::arg<3>::arg()));
    mNetworkController.sUpdatePlayerScore.connect(boost::bind(&GameController::updatePlayerScore, GameController::Instance(),boost::arg<1>::arg(),boost::arg<2>::arg()));
    mNetworkController.sWriteScores.connect(boost::bind(&EristoffGameServerApp::writeScores, this,boost::arg<1>::arg(),boost::arg<2>::arg()));
	
	GameController::Instance()->sStartIntro.connect(boost::bind(&EristoffGameServerApp::startIntro, this));
	mVideoLayer.sIntroVideoDone.connect(boost::bind(&EristoffGameServerApp::startGame, this));
	mVideoLayer.sOutroVideoDone.connect(boost::bind(&EristoffGameServerApp::newGame, this));
	GameController::Instance()->sStartOutro.connect(boost::bind(&EristoffGameServerApp::startOutroDelayed, this));
	GameController::Instance()->sNewGame.connect(boost::bind(&EristoffGameServerApp::newGame, this));
	
    GameController::Instance()->sUpdateClient.connect(boost::bind(&NetworkController::updateClient, &mNetworkController,boost::arg<1>::arg(),boost::arg<2>::arg()));
    GameController::Instance()->sClientAccepted.connect(boost::bind(&NetworkController::sendAcceptedToClient, &mNetworkController,boost::arg<1>::arg()));
    GameController::Instance()->sClientAccepted.connect(boost::bind(&EristoffGameServerApp::newPlayer, this));
	
	
	
	
    
    // Setup the parameters
	mSettingsBar = params::InterfaceGl( "parameters", Vec2i( 220, 800 ) );
    TwDefine("parameters position='1700 135'");
	
	//  mSettingsBar.setOptions("position", "200 40");
    mSettingsBar.addText("GAMEPLAY");
	mSettingsBar.addParam( "totalGameTime", &SettingManager::Instance()->totalGameTime, "min=1 max=1000 step=1");
	mSettingsBar.addParam( "totalPlayers", &SettingManager::Instance()->totalPlayers, "min=1 max=1000 step=1");
	mSettingsBar.addParam( "dizzyTrailSamples", &SettingManager::Instance()->dizzyTrailSamples, "min=1 max=1000 step=1");
	mSettingsBar.addParam( "dizzyTrailTime", &SettingManager::Instance()->dizzyTrailTime, "min=1 max=1000 step=1");
	mSettingsBar.addParam( "windowOpenTime", &SettingManager::Instance()->windowOpenTime, "min=1 max=60 step=1");
	mSettingsBar.addParam( "gyroscopeMultiplier", &SettingManager::Instance()->gyroscopeMultiplier, "min=0.1 max=3 step=0.2");
	mSettingsBar.addParam("isScramble", &SettingManager::Instance()->isScramble);
	mSettingsBar.addParam("bottleDropSpeed", &SettingManager::Instance()->bottleDropSpeed);

    mSettingsBar.addText("boundingbox");
	mSettingsBar.addParam("x1", &SettingManager::Instance()->boundingBox.x1);
	mSettingsBar.addParam("y1", &SettingManager::Instance()->boundingBox.y1);
	mSettingsBar.addParam("x2", &SettingManager::Instance()->boundingBox.x2);
	mSettingsBar.addParam("y2", &SettingManager::Instance()->boundingBox.y2);
	
	
    mSettingsBar.addSeparator();
    
    mSettingsBar.addText("COLOR");
	mSettingsBar.addParam( "saturation", &SettingManager::Instance()->saturation, "min=-1 max=3 step=0.01");
	mSettingsBar.addParam( "brightness", &SettingManager::Instance()->brightness, "min=-1 max=2 step=0.01");
	mSettingsBar.addParam( "contrast",&SettingManager::Instance()->contrast, "min=-1 max=2 step=0.01");
	
	
    mSettingsBar.addSeparator();

	
    //mSettingsBar.addText("OUTRO");
	//mSettingsBar.addParam( "totalOutroTime", &SettingManager::Instance()->totalOutroTime, "min=5 max=60 step=1");
//	mSettingsBar.addSeparator();
    
    mSettingsBar.addText("SERVER/failover");
	mSettingsBar.addParam("isMasterServer", &SettingManager::Instance()->isMasterServer);
	mSettingsBar.addSeparator();
    
    mSettingsBar.addText("MESH LAYER");
	mSettingsBar.addParam("m_offset", &SettingManager::Instance()->meshOffset);
	mSettingsBar.addParam("m_scale X", &SettingManager::Instance()->meshScaleX, "min=0.5 max=3 step=0.001");
	mSettingsBar.addParam("m_scale Y", &SettingManager::Instance()->meshScaleY, "min=0.5 max=3 step=0.001");
	mSettingsBar.addSeparator();
	
    mSettingsBar.addText("VIDEO LAYER");
	mSettingsBar.addParam("offset", &SettingManager::Instance()->videoOffset);
	mSettingsBar.addParam("scale X", &SettingManager::Instance()->videoScaleX, "min=0.5 max=3 step=0.001");
	mSettingsBar.addParam("scale Y", &SettingManager::Instance()->videoScaleY, "min=0.5 max=3 step=0.001");
	mSettingsBar.addParam("alpha", &SettingManager::Instance()->videoAlpha, "min=0.0 max=1 step=0.04 keyIncr=e keyDecr=d");
	mSettingsBar.addParam("speed", &SettingManager::Instance()->videoSpeed, "min=0.0 max=10 step=0.01");
	mSettingsBar.addSeparator();
	
	mSettingsBar.addText("SCOREPANEL1");
	mSettingsBar.addParam("s1 offset", &SettingManager::Instance()->scorepanel1Pos);
	mSettingsBar.addParam("s1 scale", &SettingManager::Instance()->scorepanel1Scale, "min=0.5 max=3 step=0.001");
	mSettingsBar.addSeparator();
    
	mSettingsBar.addText("SCOREPANEL2");
	mSettingsBar.addParam("s2 offset", &SettingManager::Instance()->scorepanel2Pos);
	mSettingsBar.addParam("s2 scale", &SettingManager::Instance()->scorepanel2Scale, "min=0.5 max=3 step=0.001");
	mSettingsBar.addSeparator();
    
	mSettingsBar.addText("SCOREPANEL OUTRO");
	mSettingsBar.addParam("sOutro offset", &SettingManager::Instance()->scorepanelOutroPos);
	mSettingsBar.addParam("sOutro scale", &SettingManager::Instance()->scorepanelOutroScale, "min=0.5 max=3 step=0.001");
	mSettingsBar.addSeparator();
    
    mSettingsBar.addSeparator();
    mSettingsBar.addParam( "Light move", &mainVisuals->autoLightMove, "" );
   mSettingsBar.addParam( "Light Direction", &mainVisuals->mLightDirection, "" );
    mSpriteRender.setup();
    
	mSettingsBar.addSeparator();
	mSettingsBar.addSeparator();
	
	
	mSettingsBar.addButton( "SAVE", std::bind( &SettingManager::saveSettings, SettingManager::Instance() ) );
	mSettingsBar.addSeparator();
	mSettingsBar.addSeparator();

	mSettingsBar.addParam("debug text",  &SettingManager::Instance()->debugText);
	mSettingsBar.addParam("interface tweaker", &mScorePanel.pos);

	mSettingsBar.addButton( "SEND scores", std::bind( &EristoffGameServerApp::sendScoresToSlaveServer, this) );
	
	// mSpriteRender.add(&testSprite);
    
    mScorePanel.setup();
    mGameUI.setup();
    mVideoLayer.setup();
    mVideoLayer.setIntroLoop();
    
	
    SettingManager::Instance()->printSettings();
	outroDelayTimer = -1;
	
//	GameController::Instance()->currentGameState = WAITING;
//	std::cout << GameController::players.size() << std::endl;
//	
//	GameController::Instance()->addPlayer("Fdsfsad","Fdsadsa","FIRST","LAST");
//	GameController::Instance()->addPlayer("fdsafsad","Fdsafdsa","FIRST","LAST");
//	GameController::Instance()->currentGameState = OUTRO;
//	std::cout << GameController::players.size() << std::endl;
//
//	mScorePanel.generateFinalScoreBoardText();
//	
//	newPlayer();
//	
//	startOutro();

	
}

void EristoffGameServerApp::newPlayer(){
    mGameUI.setPlayerNames();
	SoundController::Instance()->NewPlayer();
}

Vec2f EristoffGameServerApp::mouseToIPadCoord(Vec2f mouse){
    // for debugging only
    Vec2f centerCoordinates((1 - (mouse.x / getWindowWidth() * 2.0 ))/2.0, (1 - (mouse.y / getWindowHeight() * 2.0 ))/2.0);
    centerCoordinates.y *= -1;
    centerCoordinates *= (1 / SettingManager::Instance()->gyroscopeMultiplier);
   ///console()<< centerCoordinates <<"endl;"<<endl;
    return centerCoordinates;
}


void EristoffGameServerApp::mouseDown( MouseEvent event )
{
	//SoundController::Instance()->WolfHit();

	//SoundController::Instance()->wolfHit();
    // for debugging only
    GameController::Instance()->updatePlayer(fakeMouseIP,mouseToIPadCoord(event.getPos()),true);
    if(event.isRight()){
		
		boost::uuids::uuid uuid = boost::uuids::random_generator()();
		string uniqueIDString = boost::lexical_cast<std::string>(uuid);
		
		fakeMouseIP = uniqueIDString;
		
        GameController::Instance()->addPlayer(fakeMouseIP,uniqueIDString,"FIRST","LAST");
        newPlayer();
    }
}

void EristoffGameServerApp::mouseMove( MouseEvent event )
{
    // for debugging only
    //console()<<event.getPos()<< "mouse";
    GameController::Instance()->updatePlayer(fakeMouseIP,mouseToIPadCoord(event.getPos()),false);
}

void EristoffGameServerApp::keyDown( KeyEvent event )
{
}

void EristoffGameServerApp::keyUp( KeyEvent event )
{
	if(event.getCode() == event.KEY_ESCAPE){
	//	mNetworkController.sendGameOver();
	//	mNetworkController.sendNewGame();
		quit();
	}else if(event.getCode() == event.KEY_m){
        SettingManager::Instance()->isMasterServer = true;
    }else if(event.getCode() == event.KEY_s){
        SettingManager::Instance()->isMasterServer = false;
    }
}

void EristoffGameServerApp::update()
{
	mSpriteRender.update();
    mVideoLayer.update();
    mNetworkController.update();
	GameController::Instance()->update();
    mainVisuals->update();
	
	if(outroDelayTimer > 0 && (getElapsedSeconds() - outroDelayTimer ) > 1.5){
		startOutro();
		outroDelayTimer = -1;
	}
}

void EristoffGameServerApp::sendScoresToSlaveServer(){
	mNetworkController.sendScores(ScoreController::Instance()->getScores());
}

void EristoffGameServerApp::writeScores(std::vector<Player> players,bool  firstElement){
	ScoreController::Instance()->resetPlayers(players,firstElement);
}



void EristoffGameServerApp::resize(ResizeEvent event){
	GameController::Instance()->windowWidth = getWindowWidth();
	GameController::Instance()->windowHeight = getWindowHeight();
    
    mSpriteRender.resize(getWindowWidth(),getWindowHeight());
}

void EristoffGameServerApp::prepareSettings(Settings *settings){
	//settings->setFullScreen();
	
	//settings->setWindowPos(1920,0);
	
	//settings->setBorderless();
	//settings->setAlwaysOnTop();

	//settings->setWindowPos(1920,0);

	//settings->setBorderless();
	//settings->setFullScreen();
	//settings->setFrameRate(30);
	settings->setWindowSize(1920,1080);
}


void EristoffGameServerApp::startIntro(){
	console() << "INTRO STARTED" << endl;

	mainVisuals->newGame();
	PrizeController::Instance()->newGame();
    mVideoLayer.setIntroGame();
}


void EristoffGameServerApp::startGame(){
	console() << "GAMESTARTED" << endl;
	mainVisuals->enableAllWindows();
    mNetworkController.sendStartGame();
    GameController::Instance()->startCountdown();
}


void EristoffGameServerApp::startOutro(){
	GameController::Instance()->currentGameState = OUTRO;
	
    mVideoLayer.setOutro();
    mainVisuals->setOutro();
    // SEND gameover to clients
	console()  << "GAMEOVER > going to outro" << endl;
    mNetworkController.sendGameOver();
}

void EristoffGameServerApp::startOutroDelayed(){
	mainVisuals->disableAllWindows();
	mScorePanel.generateFinalScoreBoardText();
	outroDelayTimer = getElapsedSeconds();
	
}

void EristoffGameServerApp::newGame(){
    console()  << "NEWGAME" << endl;
	
    GameController::Instance()->reset();
    mNetworkController.sendNewGame();
    mNetworkController.reset();
    mVideoLayer.setIntroLoop();
	
    
}


void EristoffGameServerApp::draw()
{
    //PREPARE DRAW
    
    gl::enableAlphaBlending();

	if(GameController::Instance()->currentGameState == OUTRO){
		
         mainFbo.bindFramebuffer();
        gl::clear( Color( 0, 0, 0 ) ,true);
        mScorePanel.drawOutroScore(); ///drawscore uit
         mainFbo.unbindFramebuffer();
        
        
        mainVisuals->startDistrotion();
        mVideoLayer.draw();

    mainVisuals->draw3D(true);

        mainVisuals->stopDistrotion();
        
        
          mainFbo.bindFramebuffer();
        	gl::enableAlphaBlending();
        mainVisuals->drawDistrotion();
        
        mainFbo.unbindFramebuffer();
        
			
	}else{
	
        mainVisuals->drawShadows ();
		mainVisuals->startDistrotion();
	
		mainVisuals->draw3D();

		gl::enableAlphaBlending();
		mVideoLayer.draw();
		mainVisuals->stopDistrotion();
        
        mainFbo.bindFramebuffer();
         gl::clear( Color( 0, 0, 0 ) ,true);
		mainVisuals->drawDistrotion();
       
		mGameUI.draw();
		mScorePanel.drawScorePanels();
        mainFbo.unbindFramebuffer();
   
	}
	  
    
    
 
	//REAL DRAW
    
    
   
    gl::clear( Color( 0, 0, 0 ) ,true);
   
//     //gebruik oderstaande voor 2de scherm, zoder al te veel overhead...
//    glPushMatrix();
//    gl::translate(Vec3f(0,1080,0));
//    gl::scale(Vec3f(1,-1,1));
// 
//    gl::draw( mainFbo.getTexture());
//	glPopMatrix();
//    
//    
     adjRenderer.draw();
    
    
    
    
    // Draw the settings bar
	params::InterfaceGl::draw();
	
//	glColor3f(0, 0.2, 0.2);
//	gl::drawSolidRect(Rectf(80,80,200,120));
//	gl::drawString(toString(getAverageFps()) + ":" + toString(getFrameRate()),Vec2f(100,100));
//	glColor3f(1, 1, 1);
	
    //console()<< getAverageFps() << endl;
    
    GLenum errCode;
    errCode = glGetError();
    if ((errCode) != GL_NO_ERROR) {
        console()  << "\n GL ERROR at: ";
        console()  << " code: "<< errCode;
        if(errCode == GL_INVALID_ENUM)console()  <<" GL_INVALID_ENUM";
        if(errCode == GL_INVALID_VALUE)console() <<"GL_INVALID_VALUE";
        if(errCode == GL_INVALID_OPERATION)console()  <<"GL_INVALID_OPERATION";
        if(errCode == GL_OUT_OF_MEMORY)console()  <<"GL_OUT_OF_MEMORY";
        console()  <<"\n";
    };
	
}

CINDER_APP_BASIC( EristoffGameServerApp, RendererGl(0) )
