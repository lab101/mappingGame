//
//  PrizeController.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 09/10/12.
//
//

#ifndef __EristoffGameServer__PrizeController__
#define __EristoffGameServer__PrizeController__

#include <iostream>
#include "AppConstants.h"
#include <Vector>

class WindowData{
public:
	PrizeType prizeType;
	int windowDelay;
};

class PrizeController{
	
private:
    static PrizeController* instance;
	std::vector<std::vector<PrizeType> > prizeSets;
	std::vector<std::vector<int> > timeSets;
	
	int currentPrizeSetIndex;
	int currentPrizeIndex;

	int currentTimeSetIndex;
	int currentTimeIndex;

	
public:
	
    static PrizeController* Instance();
	WindowData getNextPrize();
	PrizeController();
	void newGame();

	
	
};


#endif /* defined(__EristoffGameServer__PrizeController__) */
