#pragma once


#include <map>
#include "cinder/Vector.h"
#include "Player.h"
#include <boost/signals2.hpp>
#include "Window.h"
#include "ScoreController.h"

enum GAME_STATE{
	WAITING,
    INTRO,
	GAME,
	GAMEOVER,
	OUTRO_DELAYED,
	OUTRO
};


class GameController
{
    
protected:
    GameController();
    
    
private:
    static GameController* instance;
    float startTime;
	
	
public:
	
    static GameController* Instance();
	
	void addPlayer(const std::string ip,const std::string uniqueId,const std::string firstname,const std::string lastname);
	
	void updatePlayer(std::string ip,ci::Vec2f position,bool shoot);
	void updatePlayerScore(std::string ip,int score);
    void update();
    void setup();
	void reset();
    
    void startCountdown();
	
	
	void hit(Player* player,PrizeType prize);
	
	bool isActivePlayer(std::string uniqueId);
	
	int getRemainingTime();
	float windowWidth;
	float windowHeight;
	
	
	
	static std::map<std::string,Player> players;
	
	boost::signals2::signal<void()> sStartIntro;
	boost::signals2::signal<void()> sStartOutro;
	boost::signals2::signal<void()> sNewGame;
    
    boost::signals2::signal<void(Player* player,const PrizeType prize)> sUpdateClient;
	boost::signals2::signal<void(std::string)> sClientAccepted;
	
    
    GAME_STATE currentGameState;
    
    ScoreController scoreController;
    
    // timers
    double outroTimer;
	bool countDownSoundStarted;
	
	
	
};