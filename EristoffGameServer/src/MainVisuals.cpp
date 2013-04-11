//
//  MainVisuals.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 02/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MainVisuals.h"
#include "AppConstants.h"
#include "SoundController.h"
#include "SettingManager.h"

void MainVisuals::setup()
{
    mLightDirection = Vec3<float>( 0.31, 0.63, -0.72 );
    windowW =1920;
    windowH =1080;
    
    hitItemPool = new HitItemPool();
    hitItemPool->setup();
    //itItemPool->getHitItem(POINTS10);
    
   
    projectionRenderer.setup();
    meshloader.load(   getAssetPath( "calibration.txt" ).string(),generator,camera);
    
    generator.  updateRenderer(projectionRenderer);

 
    
    //projectionRenderer.setupFinal();
    
    
    globalX=  camera.globalX; //= globalX =projectionRenderer.globalX;
    globalY  = camera.globalY;// =  globalY=projectionRenderer.globalY;
    globalScale = camera.globalScale;//= projectionRenderer.globalScale;
	
    SettingManager::Instance()->meshScaleX = globalScale;
    SettingManager::Instance()->meshScaleY = globalScale;
	
  	projectorX =  projectionRenderer.projectorX;
	projectorY=projectionRenderer.projectorY;
	projectorZ =projectionRenderer.projectorZ;
	projectionWidth =projectionRenderer.projectionWidth;
	projectionHeight=projectionRenderer.projectionHeight;
	buildingOffsetX =projectionRenderer.buildingOffsetX;
	buildingOffsetY =projectionRenderer.buildingOffsetY ;
	
    gameController =GameController::Instance();
    
    
	//console()<<" p" <<projectionWidth<< endl;
	//projectionHeight=1250;
    
    colorMeshRenderer.setup();
	colorMeshRenderer.camera =&camera;
    
    
    basicMeshRenderer.setup();
	basicMeshRenderer.camera =&camera;
    
    
    
  
    cinder::Matrix44f mat;
    mat.setToIdentity();
    mat.scale (0.01);
 
    string p5 = getAssetPath( "models/FPLT.dae" ).string();
   
    loader.preMatrix =mat;
    loader.load(p5);
    
//parachutte
    string p6 = getAssetPath( "models/PARASHUT.dae" ).string();
     mat.setToIdentity();
      mat.scale (0.9);
   loaderParachutte.preMatrix =mat;
  
   loaderParachutte.load(p6);
    fles =new HitItemFles();
    fles->hitMesh = loaderParachutte.getMeshByName("Cube");
    fles->visualMesh1= loaderParachutte.getMeshByName("bottle");
	fles->visualMesh1->material  = new npMaterial();
	fles->visualMesh1->material ->setColorTexture("models/parashutebotleColor.png");
   
    
    fles->visualMesh2= loaderParachutte.getMeshByName("parashute");
    
    fles->visualMesh2->material  = new npMaterial();
    fles->visualMesh2->material ->setColorTexture("models/parashuteclothColor.png");
//targets
    mat.setToIdentity();
    string p0 = getAssetPath( "models/windowTargets2.dae" ).string();
    loaderWindows.blender =true;
    loaderWindows.preMatrix =mat;
    loaderWindows.load(p0);
	
	

   
    
    
    //facade
    npMaterial *materialFacade = new npMaterial();
    materialFacade ->setColorTexture("models/BRICKSColor.png");
    facade=loader.getMeshByName("FACADE");
    facade->material  =materialFacade;
    facade->objectMatrix.setToIdentity();
    facade->objectMatrix.translate(Vec3f(0,0,-3));
    facade->objectMatrix.rotate(Vec3f(1,0,0), -3.14/2);

    
    npMaterial *materialTrap = new npMaterial();
    materialTrap ->setColorTexture("models/stairsColor.png");
    trap=loader.getMeshByName("STAIRS");
    trap->material =materialTrap;
    trap->objectMatrix.setToIdentity();
    trap->objectMatrix.rotate(Vec3f(1,0,0), -3.1415/2);
    
    
    npMaterial *materialRoof = new npMaterial();
   materialRoof  ->setColorTexture("models/roofColor.png");
     dakgoot=loader.getMeshByName("ROOF");
    dakgoot->material =materialRoof ;
    dakgoot->objectMatrix.setToIdentity();
    dakgoot->objectMatrix.rotate(Vec3f(1,0,0), -3.14/2);
    
    //plaaster
	npMaterial *material = new npMaterial();
    material->setColorTexture("models/PLAASTERColor2.png");
    lowPoly =loader.getMeshByName("PLAASTER");
    lowPoly->material =material ;
    lowPoly->objectMatrix.rotate(Vec3f(1,0,0), -3.14/2);
    //lowPoly
    plaaster.setup(lowPoly);
   plaaster.renderMesh->objectMatrix.rotate(Vec3f(1,0,0), -3.14/2);
    //fbos
    
    
    gl::Fbo::Format format;
    format.enableDepthBuffer(true,false);
    hitFbo = gl::Fbo( windowW/2,windowH/2,format  );
    
    mainFbo= gl::Fbo( windowW,windowH  );
    
    gl::Fbo::Format formatS;
    formatS.enableDepthBuffer(true,true);
    shadowFbo= gl::Fbo(1024*4,1024*4  ,formatS);
    
   
    buildTargets();
    
	scrampleTexture = loadImage(loadAsset("scramble1.png"));

	 
}

void MainVisuals::enableAllWindows(){
	for (int i=0;i<  windowTargets.size();i++)
    {
		windowTargets[i]->enable();
    }
}

void MainVisuals::disableAllWindows(){
	for (int i=0;i<  windowTargets.size();i++)
    {
		windowTargets[i]->disable();
    }
}

void MainVisuals::newGame(){
	plaaster.reset();
	fles->show();
}

void MainVisuals::update()
{
   
    
    bool hasShot = false;
    if (!autoLightMove){
	camera.lightPosTar.x =mLightDirection.x*-2000;
	camera.lightPosTar.y = mLightDirection.y*-2000;
        camera.lightPosTar.z = mLightDirection.z*-2000;
    }
    plaaster.update();
    for(std::map<std::string,Player>::iterator it = GameController::players.begin();it != GameController::players.end();++it){
        
        Player* player = &(it->second);
        if ( player->hasShot){
			hasShot =true; ;
            //console() << "shot";
        }
		
    }
    camera.set(projectorX,projectorY,projectorZ,projectionWidth,projectionHeight,-buildingOffsetX,-buildingOffsetY);
    
	fles->update();
	
    
    for (int i=0;i<  windowTargets.size();i++)
    {
        windowTargets[i]->update();
    }
    
    if ( hasShot ) checkShot();
	
}

void MainVisuals::drawShadows()
{
     glEnable (GL_DEPTH_TEST);
    shadowFbo.bindFramebuffer();
    glPolygonOffset(0.2f,0.3f);
    glEnable(GL_POLYGON_OFFSET_FILL);
    
	glViewport(0,0,1024*4,1024*4);
	gl::clear( Color( 0.0f, 1.0f, 0.0f ),true );
	
	
	
    colorMeshRenderer.startShadow();
    
    for (int i=0;i<  windowTargets.size();i++)
    {
        if(windowTargets[i]->hitItem)
            if(windowTargets[i]->hitItem->used)
				colorMeshRenderer.draw( windowTargets[i]->hitItem->visualMesh);
        
    }
	colorMeshRenderer.draw( fles->visualMesh1);
    colorMeshRenderer.draw( fles->visualMesh2);
	
	
    colorMeshRenderer.draw( facade);
    colorMeshRenderer.draw( trap);
    colorMeshRenderer.draw( dakgoot);
	colorMeshRenderer.draw( plaaster.renderMesh);
    
	for (int i=0;i<  windowTargets.size();i++)
    {
		
        for (int i=0;i<  windowTargets.size();i++)
        {
            colorMeshRenderer.draw( windowTargets[i]->luikL);
            colorMeshRenderer.draw( windowTargets[i]->luikR);
 
        }
	}
    
    for(int i=0;i< plaaster.particles.size();i++)
    {
		if ( plaaster.particles[i]->y<200)
			colorMeshRenderer.draw(  plaaster.particles[i]->partMesh);
        
    }
	
	
 
    
    colorMeshRenderer.stop();
	glDisable(GL_POLYGON_OFFSET_FILL);
    shadowFbo.unbindFramebuffer();
    
  
    
    
	glViewport(0,0,windowW,windowH);
 glDisable(GL_DEPTH_TEST);


}
void MainVisuals::startDistrotion(){
    mainFbo.bindFramebuffer();
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

}
void MainVisuals::stopDistrotion(){
mainFbo.unbindFramebuffer();

}
void MainVisuals::drawDistrotion(){
glEnable(GL_DEPTH_TEST);
    projectionRenderer.texture = mainFbo.getTexture().getId();
	projectionRenderer.draw();
glDisable(GL_DEPTH_TEST);
}
void MainVisuals::draw3D(bool isIntro ){

    if (isIntro)
    {
        basicMeshRenderer.start();
       
        basicMeshRenderer.shadowTexture  =  shadowFbo.getDepthTexture().getId(); 
        //basicMeshRenderer.draw( plaaster.renderMesh);
       
        glBindTexture(GL_TEXTURE_2D, lowPoly->material->colortexture);
     //   console()<<  plaaster.particles[0]->z <<endl;
        
        for(int i=0;i< plaaster.particles.size();i++)
        {
            
            if ( plaaster.particles[i]->z<100)
                basicMeshRenderer.draw(  plaaster.particles[i]->partMesh);
            
        }
        basicMeshRenderer.stop();
        return;
    
    
    }
    
    glEnable(GL_DEPTH_TEST);
    
    //	gl::clear( Color( .0f, .0f, .0f ),true );
	
	// DRAW WHITE BACKGROUND FOR SCRAMBLER
	
	if(SettingManager::Instance()->isScramble){
		glDisable( GL_DEPTH_TEST );
		//glEnable( GL_BLEND );
		glColor3f(1, 1, 1);
		gl::drawSolidRect(Rectf(120,120,1600,1000));
		glEnable( GL_DEPTH_TEST );
		//glDisable( GL_BLEND );
	}
	
	
	
    basicMeshRenderer.shadowTexture  =  shadowFbo.getDepthTexture().getId();
	basicMeshRenderer.start();
	for (int i=0;i<  windowTargets.size();i++)
	{
		if(windowTargets[i]->hitItem)
            if(windowTargets[i]->hitItem->used)
				basicMeshRenderer.draw( windowTargets[i]->hitItem->visualMesh);
		
	}
    
	// DRAW SCRAMBLER
	if(SettingManager::Instance()->isScramble){
		basicMeshRenderer.stop();
		glDisable( GL_DEPTH_TEST );
		glEnable( GL_BLEND );
		glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
		gl::draw(scrampleTexture,Rectf(120,120,1600,1000));
		glEnable( GL_DEPTH_TEST );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable( GL_BLEND );
		basicMeshRenderer.start();
	}
    
    glBindTexture(GL_TEXTURE_2D, lowPoly->material->colortexture);
    for(int i=0;i< plaaster.particles.size();i++)
    {
		
		if ( plaaster.particles[i]->z<200)
            basicMeshRenderer.draw(  plaaster.particles[i]->partMesh);
		
    }
    basicMeshRenderer.draw( facade);
    basicMeshRenderer.draw( trap);
    basicMeshRenderer.draw( dakgoot);
	basicMeshRenderer.draw( plaaster.renderMesh);
	for (int i=0;i<  windowTargets.size();i++)
	{
		basicMeshRenderer.draw( windowTargets[i]->luikL);
		basicMeshRenderer.draw( windowTargets[i]->luikR);
		// console() << "draw??"<<endl;
		//    basicMeshRenderer.draw( windowTargets[i]->window);
	}
    basicMeshRenderer.draw( fles->visualMesh1);
    basicMeshRenderer.draw( fles->visualMesh2);
	basicMeshRenderer.stop();
	
    
    glDisable(GL_DEPTH_TEST);



}
/*
void MainVisuals::draw()
{
   
    glEnable(GL_DEPTH_TEST);
  
//	gl::clear( Color( .0f, .0f, .0f ),true );
	
	// DRAW WHITE BACKGROUND FOR SCRAMBLER
	
	if(SettingManager::Instance()->isScramble){
		glDisable( GL_DEPTH_TEST );
		//glEnable( GL_BLEND );
		glColor3f(1, 1, 1);
		gl::drawSolidRect(Rectf(120,120,1600,1000));
		glEnable( GL_DEPTH_TEST );
		//glDisable( GL_BLEND );
	}
	
	
	
    basicMeshRenderer.shadowTexture  =  shadowFbo.getDepthTexture().getId();
	basicMeshRenderer.start();
	for (int i=0;i<  windowTargets.size();i++)
	{
		if(windowTargets[i]->hitItem)
            if(windowTargets[i]->hitItem->used)
				basicMeshRenderer.draw( windowTargets[i]->hitItem->visualMesh);
		
	}

	// DRAW SCRAMBLER
	if(SettingManager::Instance()->isScramble){
		basicMeshRenderer.stop();
		glDisable( GL_DEPTH_TEST );
		glEnable( GL_BLEND );
		glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
		gl::draw(scrampleTexture,Rectf(120,120,1600,1000));
		glEnable( GL_DEPTH_TEST );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable( GL_BLEND );
		basicMeshRenderer.start();
	}

	   glBindTexture(GL_TEXTURE_2D, lowPoly->material->colortexture);
   for(int i=0;i< plaaster.particles.size();i++)
    {
		
		if ( plaaster.particles[i]->y<200)
        basicMeshRenderer.draw(  plaaster.particles[i]->partMesh);
		
    }
    basicMeshRenderer.draw( facade);
    basicMeshRenderer.draw( trap);
    basicMeshRenderer.draw( dakgoot);
	basicMeshRenderer.draw( plaaster.renderMesh);
	for (int i=0;i<  windowTargets.size();i++)
	{
		basicMeshRenderer.draw( windowTargets[i]->luikL);
		basicMeshRenderer.draw( windowTargets[i]->luikR);
		// console() << "draw??"<<endl;
		//    basicMeshRenderer.draw( windowTargets[i]->window);
	}
    basicMeshRenderer.draw( fles->visualMesh1);
     basicMeshRenderer.draw( fles->visualMesh2);
	basicMeshRenderer.stop();
	
   
glDisable(GL_DEPTH_TEST);
        
}*/
/*void MainVisuals::startDraw(){

	glEnable(GL_DEPTH_TEST);
    
	gl::clear( Color( 0.0f, 0.0f, 0.0f ),true );
	
    ///////////////SHADOW
    //////////////
    
       
	
    
    
    
    
    
  mainFbo.bindFramebuffer();
glDisable(GL_DEPTH_TEST);
gl::clear( Color( .0f, .0f, .0f ),true );
}*/
/*void MainVisuals::stopDraw(){

	mainFbo.unbindFramebuffer();
    
    projectionRenderer.texture = mainFbo.getTexture().getId();
	projectionRenderer.draw();
	
    
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
    
	

	
	
    colorMeshRenderer.stop();
    
  //  gl::draw( hitFbo.getTexture(),Rectf(0,0,300,200) );


}*/
void MainVisuals::checkShot()
{
	
	if(GameController::Instance()->currentGameState != GAME) return;
	
    hitFbo.bindFramebuffer();
    glViewport(0,0,windowW/2,windowH/2);
    
    gl::clear( Color( 0.0f, 0.0f, 0.0f ),true );
    glEnable(GL_DEPTH_TEST);
    colorMeshRenderer.start();
    for (int i=0;i<  windowTargets.size();i++)
    {
        if ( windowTargets[i]->isOpen){
			colorMeshRenderer.r = windowTargets[i]->currentPrizeType / 255.0;
			colorMeshRenderer.g = windowTargets[i]->id / 255.0;
			colorMeshRenderer.b =0;
			colorMeshRenderer.a =1.0f;
			colorMeshRenderer.draw( windowTargets[i]->window);
        }
    }
    colorMeshRenderer.r = 0;
    colorMeshRenderer.g = 0;
    colorMeshRenderer.b =1;
    colorMeshRenderer.a =1.0f;
	colorMeshRenderer.draw( lowPoly);
    
    colorMeshRenderer.r = 1;
    colorMeshRenderer.g = 1;
    colorMeshRenderer.b =0;
    colorMeshRenderer.a =1.0f;
    colorMeshRenderer.draw(fles->hitMesh);
    
    colorMeshRenderer.stop();
    
    
    float *depth;
    depth= new float[1];
    
    float *color;
    color = new float[4];
    
    for(std::map<std::string,Player>::iterator it = GameController::players.begin();it != GameController::players.end();++it){
        
        Player* player = &(it->second);
        if (player->hasShot)
        {
                      // console() <<"playerIpos" << player->getPosition().x << " "<<player->getPosition().y<< endl;
			float playerX =( ((float)player->getPosition().x/windowW)*2.0 -1) /globalScale-globalX;
            float playerY = (( (float)player->getPosition().y/windowH)*2.0 -1) /globalScale  +globalY;
           // console() <<"playerPre" << playerX << " "<<playerY<< endl;

            playerX  +=1.0;
            playerX  /=2.0;
            playerX *=windowW;
            playerY  +=1.0;
            playerY  /=2.0;
            playerY *=windowH;

           
            glReadPixels((int)player->getPosition().x/2,(int) windowH/2-(int)player->getPosition().y /2,1, 1, GL_RGBA,GL_FLOAT,color);
          // console() << "depth: "<< depth[0]<< " color: " << color[2] <<endl;
			if (color[2]==1 )
            {
                
				//glReadPixels((int)playerX/2, (int) windowH/2-(int)playerY /2,1, 1, GL_DEPTH_COMPONENT,GL_FLOAT,depth);
               
				
                float posX =( ((float)playerX/windowW)-0.5)*projectionWidth +	buildingOffsetX;
           
                float posY = (((float)playerY/windowH )-0.5)*projectionHeight- buildingOffsetY;
                 Vec3f shootPos = Vec3f (-posX,posY, 0);
               // console()<<"x:"<< posX << " pw " <<posY <<" s" <<endl;
				int triangles = plaaster.shoot(shootPos );
                
				if(triangles > 20)
					SoundController::Instance()->Wall(player->normalizedPosition.x);

            }

			// bottle!
			if (!fles->isHit && color[0] == 1 && color[1] == 1 && GameController::Instance()->currentGameState == GAME){
				fles->hit();
				GameController::Instance()->hit(player,BOTTLE);
				SoundController::Instance()->PlayerBottle(player->playerNumber);
			}else if (color[0] > 0 && GameController::Instance()->currentGameState == GAME){
			
				int windowNr = (int) (color[1] * 255.0);
				
				if(windowNr >= windowTargets.size() || windowNr < 0)
					std::cout << "invalid window id " << windowNr << std::endl;
				else{
					//					std::cout << " CLOSING window nr " << windowNr << std::endl;
					windowTargets.at(windowNr)->hit();
					windowTargets.at(windowNr)->close();
					GameController::Instance()->hit(player,(PrizeType) (color[0]* 255.0));
					SoundController::Instance()->CointHit();
                    if (autoLightMove) camera.moveLight();

				}
			}

			
            player->hasShot=false;
        }
    }
    
    delete [] depth;
    delete [] color;
    
	
    
    /// glReadPixels(	0,0,1,1,GL_RED,GL_BYTE,f);
    //  console() <<"pixel "<< f[0];
    hitFbo.unbindFramebuffer();
    glViewport(0,0,windowW,windowH);
	
	
	
	
}

void MainVisuals::buildTargets()
{
   	
	int windowId=0;
    for (int i=0;i < NR_OF_WINDOWS;i++)
    {
        WindowTarget * target = new WindowTarget();
        target->mTimeline =&mTimeline;
        string luikL = "LUIK_"+cinder::toString((i+1))+"_L";
        string luikR= "LUIK_"+cinder::toString((i+1))+"_R";
		string window= "window"+cinder::toString((i+1));
        
        target->luikL = loader.getMeshByName(luikL);
        target->luikR = loader.getMeshByName(luikR);
		
		target->window =    loaderWindows.getMeshByName(window);
        
		if (target->luikL &&  target->luikR )
        {
            
            string luikLM = "models/luik"+cinder::toString((i+1))+"lColor.png";
            string luikRM= "models/luik"+cinder::toString((i+1))+"rColor.png";

            
            npMaterial *materialL = new npMaterial();
            materialL->setColorTexture(luikLM );

            
            npMaterial *materialR = new npMaterial();
            materialR->setColorTexture(luikRM );

            //target->luikR->objectMatrix.rotate(Vec3f(1,0,0), -3.14/2);
            //target->luikR->objectMatrix.rotate(Vec3f(1,0,0), -3.14/2);
			target->luikR->material   =materialR;
            target->luikL->material   =materialL;
			target->id =  windowId;
            target->hitItemPool = hitItemPool;
			windowId++;
            target->basePos = target->window->basePos;
			target->assignNewTarget();
            windowTargets.push_back(target);
        }else
        {
            console() << "luikNotFound" << (i+1)<< endl;
        }
		
    }
    
	
	
}

void MainVisuals::setOutro()
{
    plaaster.setOutro();
}