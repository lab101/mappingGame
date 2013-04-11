#pragma once
#include "OscSender.h"
#include "OscListener.h"
#include "cinder/Vector.h"
#include <boost/signals2.hpp>
#include "Player.h"
#include <map>
#include "AppConstants.h"


class NetworkController
{
	ci::osc::Listener listener;
    std::map<std::string,ci::osc::Sender> clientConnections;

	ci::osc::Sender slaveServer;
	std::string ipSlaveServer;

   // std::map<std::string ip,std::string> clientConnections;
	void sendOscMessageToClients(ci::osc::Message message);
    void sendOscMessageToClient(const std::string& ip,ci::osc::Message message);
	void sendOscMessageToSlaveServer(ci::osc::Message message);


public:
	void setup();
	void update();
	void reset();
	
	void sendNewGame();
	void sendGameOver();
    void sendStartGame();
	
	void sendScores(std::vector<Player> &players);
    
    void sendAcceptedToClient(std::string ip);

    boost::signals2::signal<void(const std::string ip,ci::Vec2f,bool shoot)> sUpdatePlayer;
    boost::signals2::signal<void(const std::string ip,const std::string uniqueId,const std::string firstname,const std::string lastname)> sNewPlayer;
	boost::signals2::signal<void(const std::string ip,int score)> sUpdatePlayerScore;
	boost::signals2::signal<void(std::vector<Player> players,bool isFirstElement)> sWriteScores;

	

	//boost::signals2::signal<void ()> sig;

    void updateClient(Player* player,PrizeType prizeType);
};