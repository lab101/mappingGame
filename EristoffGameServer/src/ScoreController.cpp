//
//  ScoreController.cpp
//  EristoffGameServer
//
//  Created by Kris Meeusen on 02/10/12.
//
//

#include "ScoreController.h"
#include <string>
#include <boost/algorithm/string.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "cinder/app/AppBasic.h"

using namespace std;
using namespace boost::gregorian;

ScoreController*  ScoreController::instance = NULL;

ScoreController::ScoreController(){
	fileName = ci::app::getAppPath().string() + "//..//players.csv";

	readAllPlayers();
}

ScoreController* ScoreController::Instance(){
    if(instance == NULL)
    {
        instance = new ScoreController();
    }
    
    return instance;
}

std::vector<Player>& ScoreController::getScores(){
	return scores;
}


void ScoreController::readAllPlayers(){
	
	std::cout << ci::app::getAppPath();
    ifstream fileStream(fileName.c_str());
    
    std::string line;

    if (fileStream.is_open()) {
        while ( fileStream.good() )
        {
            getline(fileStream,line);
            
            std::vector<std::string> playerData;
            boost::split(playerData, line, boost::is_any_of(";"));
            
            if(playerData.size() >= 3){
                int score = boost::lexical_cast<int>(playerData[3]);
                Player player(playerData[0],playerData[1],playerData[2],score);
                scores.push_back(player);
            }

           // cout << line << endl;
        }
        
        fileStream.close();

    }else{
        cout << "no scores.csv ?" << std::endl;
    }
    
    sortAndSetRankings();

}


void ScoreController::resetPlayers(std::vector<Player> players,bool firstElement){
	ofstream fileStream;
    fileStream.open(fileName.c_str(),firstElement ?  ios::trunc : ios::app );
	
	//std::cout << "incmoing " <<  players.size() << std::endl;
	if(firstElement)scores.clear();
	
    // write csv to file
    for(std::vector<Player>::iterator it = players.begin();it != players.end();++it){
        
        Player player = *(it);
        
        std::string date = to_iso_extended_string(boost::posix_time::microsec_clock::local_time());
        fileStream <<  player.getUniqueId() <<  ";" <<  player.getFirstName() << ";" <<  player.getLastName() <<  ";" << player.getScore() << ";" << date << ";" << std::endl;
        scores.push_back(player);
    }
    
    fileStream.close();

}


void ScoreController::addPlayers(std::map<std::string,Player> *players){
    
    ofstream fileStream;
    fileStream.open(fileName.c_str(), ios::app);
	
	// write csv to file
    for(std::map<std::string,Player>::iterator it = players->begin();it != players->end();++it){
        
        Player* player = &(it->second);
        
        std::string date = to_iso_extended_string(boost::posix_time::microsec_clock::local_time());
        fileStream <<  player->getUniqueId() <<  ";" <<  player->getFirstName() << ";" <<  player->getLastName() <<  ";" << player->getScore() << ";" << date << ";" << std::endl;
        scores.push_back(it->second);
    }
    
    fileStream.close();
    
    sortAndSetRankings();
    
    
    // update rankings in current temp player objects
    for(std::map<std::string,Player>::iterator it = players->begin();it != players->end();++it){        
        Player* tmpPlayer = &(it->second);
        
        for (vector<Player>::iterator it = scores.begin(); it != scores.end(); ++it) {
            if (tmpPlayer->getUniqueId() == it->getUniqueId()) {
                tmpPlayer->setRank(it->getRank());
                //std::cout << tmpPlayer->getName() << " rank : " << tmpPlayer->getRank() << std::endl;
                break;
            }
        }

    }

}


void ScoreController::sortAndSetRankings(){
    sort(scores.begin(),scores.end());

    int i=0;
    for (vector<Player>::iterator it = scores.begin(); it != scores.end(); ++it) {
        (*it).setRank(++i);
    }
}
