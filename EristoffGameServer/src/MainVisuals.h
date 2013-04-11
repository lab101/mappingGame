//
//  MainVisuals.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 02/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef EristoffGameServer_MainVisuals_h
#define EristoffGameServer_MainVisuals_h

#include "GameController.h"
#include <map>
#include "cinder/Vector.h"
#include "cinder/utilities.h"
#include "cinder/Timeline.h"
#include "cinder/Easing.h"
#include "Player.h"
#include "BasicMeshRenderer.h"
#include "ColorMeshRenderer.h"
#include "npMesh.h"
#include "npCinderAssimpLoader.h"
#include "ProjectionCamera.h"
#include "WindowTarget.h"
#include "npMaterial.h"
#include "ProjectionRenderer.h"
#include "cinder/gl/Fbo.h"
#include "HitItemPool.h"
#include "Plaaster.h"
#include "HitItemFles.h"
#include "MeshGenerator.h"
#include "ProjectionSaveLoad.h"
using namespace std;
using namespace ci;
using namespace cinder;
class MainVisuals
{

public:
    MainVisuals(ci::Timeline &timeline): mTimeline(timeline){autoLightMove =true;};
    void setup();
    void update();    
    //void draw();
   
    void checkShot();
    void buildTargets();
  
    float globalX;
    float globalY;
    float globalScale;
 
    vector<WindowTarget *> windowTargets;
    
   MeshGenerator generator;
    ProjectionSaveLoad meshloader;
    
    GameController *gameController;
    Plaaster plaaster;
    ProjectionCamera camera;
    ProjectionRenderer projectionRenderer;

	gl::Texture scrampleTexture;
	
	npCinderAssimpLoader loader;
    	npCinderAssimpLoader loaderParachutte;
	npCinderAssimpLoader loaderWindows;
    BasicMeshRenderer basicMeshRenderer;
    ColorMeshRenderer colorMeshRenderer;
    HitItemPool * hitItemPool;
	gl::Fbo hitFbo;
    gl::Fbo mainFbo;
    gl::Fbo shadowFbo;
    
    npMesh *lowPoly;
    npMesh *trap;
    npMesh *dakgoot;
    npMesh *facade;
    Vec3<float> mLightDirection;
    float					projectorX;
    float					projectorY;
    float					projectorZ;
    
    
 
    float					projectionWidth;
    float					projectionHeight;
    
    float					buildingOffsetX;
    float					buildingOffsetY;
    
    float windowW;
    float windowH;
    bool autoLightMove;
    Timeline	&mTimeline;
    HitItemFles *fles;
	void setOutro();
	void disableAllWindows();
	void enableAllWindows();
	void newGame();
    
    void drawShadows();
    void startDistrotion();
    void stopDistrotion();
    void drawDistrotion();
	void draw3D(bool isIntro =false);
    
   // void startDraw();
	//void stopDraw();
};

#endif
