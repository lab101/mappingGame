#pragma once
#include "cinder/Vector.h"
#include "string"
#include <Vector>
#include <list>


//#include "vec"

class Player{
	std::string mIpAddress;
    std::string mFirstName;
    std::string mLastName;

	int mScore;
    std::string mUniqueId;
    int mRank;
    

    ci::Vec2f currentPosition;
    
    std::vector<ci::Vec2f> dizzyTrail;
	std::list<ci::Vec2f> dizzyTrailList;
	
    int dizzyVectorFillIndex;
    double dizzyOnTimer;
	float dizzyFadeoutExtraSamples;

public:
	Player(std::string ip,std::string uniqueId,std::string firstname,std::string lastname);
	Player(std::string uniqueID,std::string firstname,std::string lastname,int score);
    Player();

    bool isDizzy;
	bool shootCrossHairEvent;
	int playerNumber;
	
    float size;
    ci::Vec2f normalizedPosition;
	



    const std::string getName();
    const std::string getFirstName();
    const std::string getLastName();
    
    
    int &getScore();
    const int getScoreConst();
    
    void setRank(int rank);
    const int getRank();
    
    const std::string getUniqueId();
//    const std::string getIP();
    const std::string &getIP();

    
    void updatePosition(ci::Vec2f positon);
    const ci::Vec2f getPosition();
    
    void setDizzy(bool dizzyOn);
    
	void shoot();
	void update();
    
    bool hasShot;
    
    
    // sort desc by score
    bool operator < (const Player& incoming) const
    {
        return (mScore > incoming.mScore);
    }
};