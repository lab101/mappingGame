#include "NetworkController.h"
#include "SettingManager.h"
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <iostream>

#include "GameController.h";

using boost::asio::ip::tcp;


using namespace std;
using namespace ci;
using namespace ci::osc;


void NetworkController::setup(){
	listener.setup(UDP_PORT);

	// get current ip adress
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(boost::asio::ip::host_name(),"");
	tcp::resolver::iterator it=resolver.resolve(query);
	
	std::string currentIP;
	while(it!=tcp::resolver::iterator())
	{
		boost::asio::ip::address addr=(it++)->endpoint().address();
		if(addr.is_v4())
			currentIP = addr.to_string();
	}
	

	for(int i=0;i < SettingManager::Instance()->servers.size();++i){
		if(currentIP != SettingManager::Instance()->servers[i]){
			ipSlaveServer = SettingManager::Instance()->servers[i];
			break;
		}
	}
	
	slaveServer.setup(ipSlaveServer,UDP_PORT);

	std::cout << "slave server " << ipSlaveServer << std::endl;
	
}

void NetworkController::reset(){

	clientConnections.clear();

}

void NetworkController::updateClient(Player* player,PrizeType prizeType){
    // send score
    
    if(!SettingManager::Instance()->isMasterServer) return;
    
	ci::osc::Message message;
    message.setAddress(MESG_SERVER_CLIENT_UPDATE);
    
    message.addIntArg(prizeType);
    message.addIntArg(player->getScoreConst());
    
    
	sendOscMessageToClient(player->getIP(),message);
	
	// send to backup server
	ci::osc::Message messageBackup;
    messageBackup.setAddress(MESG_SERVER_SLAVE_UPDATE);
    
	messageBackup.addStringArg(player->getIP());
    messageBackup.addIntArg(player->getScoreConst());
	
	sendOscMessageToSlaveServer(messageBackup);
}


void NetworkController::update(){
	while (listener.hasWaitingMessages()) {
		Message message;
		listener.getNextMessage(&message);
		
        string ip = message.getRemoteIp();
        
		if(message.getAddress() == MESG_CLIENT_NEW_PLAYER){
			string uniqueId = message.getArgAsString(0);
			string firstname = message.getArgAsString(1);
			string lastname = message.getArgAsString(2);

            cout << "INCOMING PLAYER " << firstname << " " << lastname << endl;
            
            // add new client connection
            std::map<string,Sender>::iterator it = clientConnections.find(ip);
            if(it==clientConnections.end()){
                clientConnections.insert(pair<std::string,ci::osc::Sender>(ip,Sender()));
                clientConnections[ip].setup(ip,UDP_PORT);
            }
            
            sNewPlayer(ip,uniqueId,firstname,lastname);
              
		}else if(message.getAddress() == MESG_CLIENT_UPDATE_PLAYER){
			
            bool shoot  = (message.getNumArgs() > 2);
            sUpdatePlayer(message.getRemoteIp(),Vec2f(message.getArgAsFloat(1),message.getArgAsFloat(0)),shoot);
		}else if(message.getAddress() == MESG_SERVER_SLAVE_UPDATE){
			
			if(message.getNumArgs() == 2)
			{
				string playerIp = message.getArgAsString(0);
				int newScore = message.getArgAsInt32(1);
				
				sUpdatePlayerScore(playerIp,newScore);
			}
		}else if(message.getAddress() == MESG_SERVER_SLAVE_SCORES){
			
			std::vector<Player> incomingPlayers;
			
			//for(int i=0;i < message.getNumArgs();i+=4){
				string uniqueId = message.getArgAsString(0);
				string firstName = message.getArgAsString(1);
				string lastName = message.getArgAsString(2);
				int score = message.getArgAsInt32(3);
				
				bool firstElement = message.getNumArgs() > 4;
				Player player(uniqueId,firstName,lastName,score);
				incomingPlayers.push_back(player);
				
				std::cout << firstName << " " << toString(score) << std::endl;
			//}
			//std::cout << "incmoing " <<  incomingPlayers.size() << std::endl;

			sWriteScores(incomingPlayers,firstElement);
			
			
		}
		
		
	}
}

void NetworkController::sendScores(std::vector<Player> &players){
	
	// send to backup server
	
	bool firstElement = true;
	for(std::vector<Player>::iterator it = players.begin();it != players.end();++it){

		ci::osc::Message messageBackup;
		messageBackup.setAddress(MESG_SERVER_SLAVE_SCORES);

		messageBackup.addStringArg(it->getUniqueId() );
		messageBackup.addStringArg(it->getFirstName());
		messageBackup.addStringArg(it->getLastName());
		messageBackup.addIntArg(it->getScoreConst());
		if(firstElement){
			messageBackup.addIntArg(1);
			firstElement = false;
		}
		
		sendOscMessageToSlaveServer(messageBackup);
	}
}

void NetworkController::sendAcceptedToClient(string ip){
    //SEND message back for ok
    Message returnMessage;
    returnMessage.setAddress(MESG_SERVER_PLAYER_ACCEPTED);
    
    sendOscMessageToClient(ip,returnMessage);

}


void NetworkController::sendStartGame(){
    if(!SettingManager::Instance()->isMasterServer) return;
    
    for(std::map<std::string,ci::osc::Sender>::const_iterator it = clientConnections.begin();it != clientConnections.end();++it){
        ci::osc::Message message;
        
        message.addIntArg(SettingManager::Instance()->totalGameTime + SettingManager::Instance()->totalOutroTime);
        message.addIntArg(GameController::players[it->first].playerNumber);
        
        message.setAddress(MESG_SERVER_START_GAME);
        
        message.setRemoteEndpoint(it->first, UDP_PORT);
        Sender sender = (it->second);
        sender.sendMessage(message);
	}
}


void NetworkController::sendNewGame(){
    if(!SettingManager::Instance()->isMasterServer) return;

	ci::osc::Message message;
    message.setAddress(MESG_SERVER_NEW_GAME);
    
	sendOscMessageToClients(message);
}


void NetworkController::sendGameOver(){
    if(!SettingManager::Instance()->isMasterServer) return;

	ci::osc::Message message;
	message.setAddress(MESG_SERVER_GAMEOVER);

	sendOscMessageToClients(message);
}


void NetworkController::sendOscMessageToClients(ci::osc::Message message){
    
	for(std::map<std::string,ci::osc::Sender>::const_iterator it = clientConnections.begin();it != clientConnections.end();++it){
        message.setRemoteEndpoint(it->first, UDP_PORT);
        Sender sender = (it->second);
        sender.sendMessage(message);
	}
}



void NetworkController::sendOscMessageToClient(const std::string& ip,ci::osc::Message message){
    clientConnections.find(ip);
    
    std::map<string,Sender>::iterator it = clientConnections.find(ip);
    
    if(it!=clientConnections.end()){
        message.setRemoteEndpoint(it->first, UDP_PORT);

        (it->second).sendMessage(message);
    }
}


void NetworkController::sendOscMessageToSlaveServer(ci::osc::Message message){
	message.setRemoteEndpoint(ipSlaveServer, UDP_PORT);
	slaveServer.sendMessage(message);
	
}

