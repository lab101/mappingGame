//
//  SettingManager.h
//  EristoffGameConsole
//
//  Created by Kris Meeusen on 13/09/12.
//  Copyright (c) 2012 Lab101.be. All rights reserved.
//

#ifndef EristoffGameConsole_SettingManager_h
#define EristoffGameConsole_SettingManager_h

#include "cinder/Xml.h"
#include "cinder/app/App.h"
#include "cinder/Vector.h"
#include "cinder/Rect.h"

class SettingManager{
public:
    
    SettingManager();
    
    static SettingManager* Instance();
        
    std::vector<std::string> servers;
    
    void loadSettings();
    void saveSettings();
    
    void printSettings();
    
    int totalGameTime;
    int totalOutroTime;
    
    int totalPlayers;
    int dizzyTrailSamples;
    int dizzyTrailTime;
    int windowOpenTime;

	//videolayer
	float videoScaleX;
	float videoScaleY;
	float videoAlpha;
	float videoSpeed;
	ci::Vec3f videoOffset;
	
	//mesh tweaks
	float meshScaleX;
	float meshScaleY;
	ci::Vec3f meshOffset;

	// scorepanel1
	float scorepanel1Scale;
	ci::Vec3f scorepanel1Pos;

	// scorepanel2
	float scorepanel2Scale;
	ci::Vec3f scorepanel2Pos;

	// scorepanelOutro
	float scorepanelOutroScale;
	ci::Vec3f scorepanelOutroPos;

	// color manager
	float saturation;
	float brightness;
	float contrast;

	float bottleDropSpeed;

	
    bool isMasterServer;
    bool isScramble;
	
    float gyroscopeMultiplier;
	
	ci::Rectf boundingBox;
	
	std::string debugText;
    
    private:
    
    ci::XmlTree xmlSettings;
    static SettingManager* instance;
    ci::DataSourceRef settingsRef;
    
};



#endif
