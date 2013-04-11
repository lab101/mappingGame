//
//  GameUI.cpp
//  EristoffGameServer
//
//  Created by Kris Meeusen on 01/10/12.
//
//

#include "GameUI.h"
#include "Player.h"
#include "GameController.h"
#include "SettingManager.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace std;
using namespace ci::app;


void GameUI::setup(){
	colors.push_back(Color(12/255.0,1,0));
	colors.push_back(Color(1,1,0));
	
	backup = loadImage(loadAsset("backup.png"));

	
	for(int i=0;i < SettingManager::Instance()->totalPlayers;++i){
		crosshairs.push_back(Crosshair());
	}
    
}


void GameUI::setPlayerNames(){
    
    int i=0;
    for(std::map<std::string,Player>::iterator it = GameController::players.begin();it != GameController::players.end();++it){

        Player* player = &(it->second);
		crosshairs[i].setName(player->getFirstName(),colors[player->playerNumber-1]);
        ++i;
    }
 
}

void GameUI::draw(){
    int i=0;
    for(std::map<std::string,Player>::iterator it = GameController::players.begin();it != GameController::players.end();++it){
         
        Player* player = &(it->second);
        player->update();
		
		if(player->shootCrossHairEvent){
			crosshairs[i].shoot();
			player->shootCrossHairEvent = false;
		}
       
		crosshairs[i].draw(player->getPosition(),colors[player->playerNumber-1],player->isDizzy);
        ++i;
        
     }
   
	if(!SettingManager::Instance()->isMasterServer)
		gl::draw(backup,ci::Rectf(0,0,1920,1080));
}
