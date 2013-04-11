//
//  ScoreController.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 02/10/12.
//
//

#ifndef EristoffGameServer_ScoreController_h
#define EristoffGameServer_ScoreController_h



#include "Player.h"
#include <Vector.h>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;


class ScoreController{
private:
    std::vector<Player> scores;
	std::string fileName;
	void readAllPlayers();

    void sortAndSetRankings();
    
    static ScoreController* instance;

public:
    void addPlayers(std::map<std::string,Player>* players);
	void resetPlayers(std::vector<Player> players,bool firstElement);

    static ScoreController* Instance();
	
    ScoreController();
	std::vector<Player>& getScores();
};




#endif
