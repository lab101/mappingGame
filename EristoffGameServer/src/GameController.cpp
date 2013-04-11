#include "GameController.h"
#include "cinder/app/AppBasic.h"
#include <string>
#include "AppConstants.h"
#include "SettingManager.h"
#include "SoundController.h"

using namespace std;
using namespace ci;
using namespace app;

std::map<std::string,Player> GameController::players;

GameController*  GameController::instance = NULL;


GameController* GameController::Instance(){
    if(instance == NULL)
    {
        instance = new GameController();
    }
    
    return instance;
}

GameController::GameController(){
    GameController::players.clear();
	
	currentGameState = WAITING;
    outroTimer = -1;
	countDownSoundStarted = false;
	
}

void GameController::setup(){
		
}

bool GameController::isActivePlayer(std::string uniqueId){
	for(std::map<std::string,Player>::iterator it = GameController::players.begin();it != GameController::players.end();++it){
		
		if(it->second.getUniqueId() == uniqueId){
			return true;
		}
	}
	return false;
	
	//std::map<std::string,Player>::iterator itFound =  GameController::players.find(uniqueId);
	//    return itFound!=GameController::players.end();
	
}


void GameController::addPlayer(std::string ip,std::string uniqueId,std::string firstname,std::string lastname){
    
    if(currentGameState == WAITING)
    {
        Player newPlayer(ip,uniqueId,firstname,lastname);
		newPlayer.playerNumber = GameController::players.size() + 1;
        GameController::players.insert(pair<std::string,Player>(ip,newPlayer));
        cout << "incoming event " << newPlayer.getName() << " " <<  GameController::players.size() << endl;
        
        sClientAccepted(ip);
    }
}


void GameController::updatePlayer(std::string ip,ci::Vec2f position,bool shoot){
	
	//console()<< position;
    if(currentGameState == OUTRO)
        return;
    
    
    std::map<std::string,Player>::iterator itFound =  GameController::players.find(ip);
    if(itFound!=GameController::players.end()){
		Player* player = &itFound->second;
		Vec2f newPos = Vec2f(windowWidth / 2.0 + position.x * - windowWidth * SettingManager::Instance()->gyroscopeMultiplier,windowHeight/2.0 + position.y * windowHeight * SettingManager::Instance()->gyroscopeMultiplier);
		
        newPos.x = math<float>::clamp(newPos.x,SettingManager::Instance()->boundingBox.x1,SettingManager::Instance()->boundingBox.x2);
        newPos.y = math<float>::clamp(newPos.y,SettingManager::Instance()->boundingBox.y1,SettingManager::Instance()->boundingBox.y2);
        
        //console()<<" v " <<newPos<<endl;
        player->updatePosition(newPos);
		
        if(currentGameState == GAME && shoot){
			player->shoot();
			player->normalizedPosition.set(position.x * -SettingManager::Instance()->gyroscopeMultiplier,position.y);
			//std::cout << player->normalizedPosition << std::endl;
			SoundController::Instance()->Shoot(player->normalizedPosition.x);
		}
    }
}

void GameController::updatePlayerScore(std::string ip,int score){
	std::map<std::string,Player>::iterator itFound =  GameController::players.find(ip);
    if(itFound!=GameController::players.end()){
		Player* player = &itFound->second;
		player->getScore() = score;
	}

}



void GameController::hit(Player* player,PrizeType prize){

	// only master server does the score because of lag etc.
	if(!SettingManager::Instance()->isMasterServer)
		return;

	if(prize == BAD){
		std::cout<< "set BAD" << std::endl;
		player->setDizzy(true);
	}else if(prize == BOTTLE){
		//std::cout<< "set BOTTLE" << std::endl;
		//player->setBottle();
	}else{
        player->getScore() += prize;
    }
	
	// send update to client
	sUpdateClient(player,prize);
	
}




int GameController::getRemainingTime(){
	return SettingManager::Instance()->totalGameTime - (app::getElapsedSeconds() - startTime);
}


void GameController::startCountdown(){
    startTime =  ci::app::getElapsedSeconds();
    currentGameState = GAME;
	countDownSoundStarted = false;
	
	for(std::map<std::string,Player>::iterator it = GameController::players.begin();it != GameController::players.end();++it){
		it->second.hasShot = false;
	}

	
}

void GameController::update(){
	if(currentGameState == WAITING &&  GameController::players.size() >= SettingManager::Instance()->totalPlayers)
	{
		currentGameState = INTRO;
		sStartIntro();
	}
	
	if(!countDownSoundStarted && currentGameState == GAME && (app::getElapsedSeconds() - startTime) > (SettingManager::Instance()->totalGameTime -5)){
		countDownSoundStarted = true;
		SoundController::Instance()->CountDown();
	}
	
	if(currentGameState == GAME && app::getElapsedSeconds() - startTime >= SettingManager::Instance()->totalGameTime){
        
        // write scores to log
        ScoreController::Instance()->addPlayers(&GameController::players);
        
		currentGameState = OUTRO_DELAYED;
        outroTimer = app::getElapsedSeconds();
		sStartOutro();
	}
    
	//    if (outroTimer > 0 && (app::getElapsedSeconds() - outroTimer) > SettingManager::Instance()->totalOutroTime) {
	//        GameController::Instance()->reset();
	//        outroTimer = -1;
	//        sNewGame();
	//
	//    }
	
	
	
}


void GameController::reset(){
	players.clear();
	currentGameState = WAITING;
}