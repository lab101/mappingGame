#include  "Player.h"
#include "SettingManager.h"
#include "cinder/app/AppBasic.h"
#include <algorithm>

using namespace std;
using namespace ci;
using namespace ci::app;

Player::Player(string ip,string uniqueId,string firstname,string lastname){
	mIpAddress = ip;
	mFirstName = firstname;
	mLastName = lastname;
    mUniqueId = uniqueId;
	size = 0;
	mScore = 0;
	
	shootCrossHairEvent = false;
	
    isDizzy = false;
    dizzyVectorFillIndex = -1;
    dizzyTrail.reserve(SettingManager::Instance()->dizzyTrailSamples);
    dizzyOnTimer = -1;
	dizzyFadeoutExtraSamples = 0;
    
    mRank = 0;
}

// used to load scores
Player::Player(string uniqueId,string firstname,string lastname,int score){
	mFirstName = firstname;
	mLastName = lastname;
	mScore = score;
    mUniqueId = uniqueId;
}

Player::Player(){
    size = 0;
    hasShot =false;
}

const std::string Player::getName(){
    return mFirstName + " " + mLastName;
}

const std::string Player::getFirstName(){
    return mFirstName;
}

const std::string Player::getLastName(){
    return mLastName;
}



int& Player::getScore(){
    return mScore;
}

const int Player::getScoreConst(){
    return mScore;
}


const string Player::getUniqueId(){
    return mUniqueId;
}


const std::string &Player::getIP(){
    return mIpAddress;
}

void Player::updatePosition(ci::Vec2f position){
    currentPosition = position;
  //console()<< position;
	
    if(isDizzy){
		
		if(dizzyFadeoutExtraSamples > 0 ){
			///gete
			dizzyFadeoutExtraSamples += 1.5;
			//std::cout << "f" << dizzyFadeoutExtraSamples << std::endl;

		}
		if(dizzyFadeoutExtraSamples > 300){
			setDizzy(false);
			std::cout << "fadeout done" << std::endl;
			dizzyFadeoutExtraSamples = 0;
		}

		

//        if(++dizzyVectorFillIndex >= SettingManager::Instance()->dizzyTrailSamples){
//			dizzyVectorFillIndex = 0;
//		}
//		
//        if(dizzyVectorFillIndex < SettingManager::Instance()->dizzyTrailSamples){
//            dizzyTrail.push_back(position);
//        }else{           
//            dizzyTrail[dizzyVectorFillIndex] = position;
//        }
        dizzyTrailList.push_front(currentPosition);
		if(dizzyTrailList.size() > SettingManager::Instance()->dizzyTrailSamples) dizzyTrailList.pop_back();
    }
}

const ci::Vec2f Player::getPosition(){
    if(!isDizzy && dizzyFadeoutExtraSamples ==0) return currentPosition;

    Vec2f dizzyPosition(0,0);
	
//	int samples = std::min(SettingManager::Instance()->dizzyTrailSamples,(int)dizzyTrail.size());
//
//	int index =  std::min(dizzyVectorFillIndex,(int)dizzyTrail.size());
//	for(int i = 0 ; i < samples;++i){
//		dizzyPosition += dizzyTrail.at(index);
//		
//		index++;
//		if(index >= dizzyTrail.size()) index = 0;
//	}
	
	
	for (list<Vec2f>::const_iterator it = dizzyTrailList.begin(); it != dizzyTrailList.end(); ++it) {
		 dizzyPosition += (*it);
	}
	
	int samples = min( (int)dizzyTrailList.size(),SettingManager::Instance()->dizzyTrailSamples);
	samples += 	(int) dizzyFadeoutExtraSamples;
	dizzyPosition += (currentPosition * (int) dizzyFadeoutExtraSamples);
//	std::cout << dizzyVectorFillIndex << ":" << samples << endl;;
//    for (vector<Vec2f>::const_iterator it = dizzyTrail.begin(); it != dizzyTrail.end(); ++it) {
//            dizzyPosition += (*it);
//            ++ samples;
//    }
    
    dizzyPosition /= samples;
    return dizzyPosition;
}

void Player::setRank(int rank)
{
    mRank = rank;
}

const int Player::getRank(){
    return mRank;
}

void Player::setDizzy(bool dizzyOn){
    isDizzy = dizzyOn;
    
    if(isDizzy){
        dizzyTrailList.clear();
        dizzyOnTimer = getElapsedSeconds();
		dizzyFadeoutExtraSamples = 0;
    }
}

void Player::shoot(){
 //   size += 60;
    //cout << position.x << endl;
    hasShot =true;
	shootCrossHairEvent = true;
  
}

void Player::update(){
//    if(size > 0){
//		size -= size / 10.0;
//	}
//    
    if(dizzyOnTimer > 0 && (getElapsedSeconds() - dizzyOnTimer) > SettingManager::Instance()->dizzyTrailTime)
    {
        dizzyOnTimer = -1;
		dizzyFadeoutExtraSamples = 1;
	}
    //cout << position.x << endl;
}