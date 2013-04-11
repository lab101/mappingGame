//
//  SettingManager.cpp
//  EristoffGameConsole
//
//  Created by Kris Meeusen on 13/09/12.
//  Copyright (c) 2012 Lab101.be. All rights reserved.
//

#include <iostream>
#include "SettingManager.h"
using namespace ci;



SettingManager*  SettingManager::instance = NULL;

//// shortcut
//static SettingManager*  set(){
//    return SettingManager::Instance();
//}

void set(){
    std::cout << "shit" << std::endl;
}

SettingManager* SettingManager::Instance(){
     if(instance == NULL)
     {
         instance = new SettingManager();
     }

    return instance;
}


SettingManager::SettingManager(){
#if defined( CINDER_COCOA )
    settingsRef = ci::app::loadResource("settings.xml");
#else
    settingsRef = ci::app::loadAsset("settings.xml");
#endif
    
	xmlSettings = ci::XmlTree(settingsRef);
    
    loadSettings();
}

void SettingManager::loadSettings(){
    XmlTree &firstServer = xmlSettings.getChild( "settings/servers");
    
    // load servers
    for( XmlTree::Iter child = firstServer.begin(); child != firstServer.end(); ++child ){
        servers.push_back(child->getChild("ip").getValue());
    }
    
    // load game variables
    totalGameTime = xmlSettings.getChild( "settings/game/totalTime").getValue<int>();
    totalOutroTime = xmlSettings.getChild( "settings/outro/totalTime").getValue<int>();
    totalPlayers = xmlSettings.getChild( "settings/game/totalPlayers").getValue<int>();
    dizzyTrailSamples = xmlSettings.getChild( "settings/game/dizzyTrailSamples").getValue<int>();
    dizzyTrailTime = xmlSettings.getChild( "settings/game/dizzyTrailTime").getValue<int>();
    gyroscopeMultiplier = xmlSettings.getChild( "settings/game/gyroscopeMultiplier").getValue<float>();
    windowOpenTime = xmlSettings.getChild( "settings/game/windowOpenTime").getValue<int>();
    isMasterServer = xmlSettings.getChild( "settings/isMasterServer").getValue<bool>();
    isScramble = xmlSettings.getChild( "settings/game/isScramble").getValue<bool>();
    bottleDropSpeed = xmlSettings.getChild( "settings/game/bottleDropSpeed").getValue<float>();
	
	
	
	videoScaleX = xmlSettings.getChild( "settings/video/scaleX").getValue<float>();
	videoScaleY = xmlSettings.getChild( "settings/video/scaleY").getValue<float>();
	
	videoOffset.x = xmlSettings.getChild( "settings/video/offset").getAttributeValue<float>("x");
	videoOffset.y = xmlSettings.getChild( "settings/video/offset").getAttributeValue<float>("y");
	videoAlpha = xmlSettings.getChild("settings/video/alpha").getValue<float>();
	videoSpeed = xmlSettings.getChild("settings/video/speed").getValue<float>();

	
	meshScaleX = xmlSettings.getChild( "settings/mesh/scaleX").getValue<float>();
	meshScaleY = xmlSettings.getChild( "settings/mesh/scaleY").getValue<float>();
	
	meshOffset.x = xmlSettings.getChild( "settings/mesh/offset").getAttributeValue<float>("x");
	meshOffset.y = xmlSettings.getChild( "settings/mesh/offset").getAttributeValue<float>("y");

	
	scorepanel1Scale = xmlSettings.getChild( "settings/scorePanel1/scale").getValue<float>();
	scorepanel1Pos.x = xmlSettings.getChild( "settings/scorePanel1/offset").getAttributeValue<float>("x");
	scorepanel1Pos.y = xmlSettings.getChild( "settings/scorePanel1/offset").getAttributeValue<float>("y");
	
	scorepanel2Scale = xmlSettings.getChild( "settings/scorePanel2/scale").getValue<float>();
	scorepanel2Pos.x = xmlSettings.getChild( "settings/scorePanel2/offset").getAttributeValue<float>("x");
	scorepanel2Pos.y = xmlSettings.getChild( "settings/scorePanel2/offset").getAttributeValue<float>("y");
	
	scorepanelOutroScale = xmlSettings.getChild( "settings/scorePanelOutro/scale").getValue<float>();
	scorepanelOutroPos.x = xmlSettings.getChild( "settings/scorePanelOutro/offset").getAttributeValue<float>("x");
	scorepanelOutroPos.y = xmlSettings.getChild( "settings/scorePanelOutro/offset").getAttributeValue<float>("y");
	
	// color tweaking
	brightness = xmlSettings.getChild( "settings/color/brightness").getValue<float>();
	contrast = xmlSettings.getChild( "settings/color/contrast").getValue<float>();
	saturation = xmlSettings.getChild( "settings/color/saturation").getValue<float>();
	
	//boundingbox
	boundingBox.x1 = xmlSettings.getChild( "settings/game/boundingBox").getAttributeValue<float>("x1");
	boundingBox.y1 = xmlSettings.getChild( "settings/game/boundingBox").getAttributeValue<float>("y1");
	boundingBox.x2 = xmlSettings.getChild( "settings/game/boundingBox").getAttributeValue<float>("x2");
	boundingBox.y2 = xmlSettings.getChild( "settings/game/boundingBox").getAttributeValue<float>("y2");


	   
}

void SettingManager::saveSettings(){
    // save game variables
    xmlSettings.getChild("settings/game/totalTime").setValue(totalGameTime);
    xmlSettings.getChild("settings/outro/totalTime").setValue(totalOutroTime);
    
    xmlSettings.getChild("settings/game/totalPlayers").setValue(totalPlayers);
    xmlSettings.getChild("settings/game/dizzyTrailSamples").setValue(dizzyTrailSamples);
    xmlSettings.getChild("settings/game/dizzyTrailTime").setValue(dizzyTrailTime);
    xmlSettings.getChild("settings/game/gyroscopeMultiplier").setValue(gyroscopeMultiplier);
    xmlSettings.getChild("settings/game/windowOpenTime").setValue(windowOpenTime);
    xmlSettings.getChild("settings/isMasterServer").setValue(isMasterServer);
    xmlSettings.getChild("settings/game/isScramble").setValue(isScramble);
    xmlSettings.getChild("settings/game/bottleDropSpeed").setValue(bottleDropSpeed);
	
	


	// video layer
	xmlSettings.getChild("settings/video/scaleX").setValue(videoScaleX);
	xmlSettings.getChild("settings/video/scaleY").setValue(videoScaleY);
	xmlSettings.getChild("settings/video/offset").setAttribute("x",videoOffset.x);
	xmlSettings.getChild("settings/video/offset").setAttribute("y",videoOffset.y);
	xmlSettings.getChild("settings/video/alpha").setValue(videoAlpha);
	xmlSettings.getChild("settings/video/speed").setValue(videoSpeed);
	
	// mesh layer
	xmlSettings.getChild("settings/mesh/scaleX").setValue(meshScaleX);
	xmlSettings.getChild("settings/mesh/scaleY").setValue(meshScaleX);
	xmlSettings.getChild("settings/mesh/offset").setAttribute("x",meshOffset.x);
	xmlSettings.getChild("settings/mesh/offset").setAttribute("y",meshOffset.y);
	
	// scorepanel 1
	xmlSettings.getChild("settings/scorePanel1/scale").setValue(scorepanel1Scale);
	xmlSettings.getChild("settings/scorePanel1/offset").setAttribute("x",scorepanel1Pos.x);
	xmlSettings.getChild("settings/scorePanel1/offset").setAttribute("y",scorepanel1Pos.y);
	
	// scorepanel 2
	xmlSettings.getChild("settings/scorePanel2/scale").setValue(scorepanel2Scale);
	xmlSettings.getChild("settings/scorePanel2/offset").setAttribute("x",scorepanel2Pos.x);
	xmlSettings.getChild("settings/scorePanel2/offset").setAttribute("y",scorepanel2Pos.y);
	
	// scorepanel outro
	xmlSettings.getChild("settings/scorePanelOutro/scale").setValue(scorepanelOutroScale);
	xmlSettings.getChild("settings/scorePanelOutro/offset").setAttribute("x",scorepanelOutroPos.x);
	xmlSettings.getChild("settings/scorePanelOutro/offset").setAttribute("y",scorepanelOutroPos.y);
	
	//color
	// color tweaking
	xmlSettings.getChild("settings/color/brightness").setValue(brightness);
	xmlSettings.getChild("settings/color/contrast").setValue(contrast);
	xmlSettings.getChild("settings/color/saturation").setValue(saturation);
	
	xmlSettings.getChild("settings/game/boundingBox").setAttribute("x1",boundingBox.x1);
	xmlSettings.getChild("settings/game/boundingBox").setAttribute("y1",boundingBox.y1);
	xmlSettings.getChild("settings/game/boundingBox").setAttribute("x2",boundingBox.x2);
	xmlSettings.getChild("settings/game/boundingBox").setAttribute("y2",boundingBox.y2);

	    
    std::cout << "writing xml settings to: "  <<  settingsRef->getFilePath() << std::endl;
    xmlSettings.write(writeFile(settingsRef->getFilePath()));
}

void SettingManager::printSettings(){
    // just for testing
    std::cout << "totalTime: " << totalGameTime << std::endl;
    std::cout << "totalPlayers: " << totalPlayers << std::endl;
    
}


