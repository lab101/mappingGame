//
//  PrizeController.cpp
//  EristoffGameServer
//
//  Created by Kris Meeusen on 09/10/12.
//
//

#include "PrizeController.h"
#include <boost/assign.hpp>

PrizeController*  PrizeController::instance = NULL;


PrizeController* PrizeController::Instance(){
    if(instance == NULL)
    {
        instance = new PrizeController();
    }
    
    return instance;
}


PrizeController::PrizeController(){
	// create prize sets
	prizeSets.reserve(5);
	
	currentPrizeSetIndex = 0;
	currentPrizeIndex = 0;
	
	currentTimeSetIndex = 0;
	currentTimeIndex = 0;
	
	//prize set 1
	std::vector<PrizeType> prizeSet1 =  boost::assign::list_of
	(POINTS10)(BAD)(POINTS50)(BAD)(POINTS25)(BAD)(POINTS10)(POINTS25)(BAD)(POINTS10)
	(POINTS10)(POINTS25)(POINTS10)(POINTS10)(BAD)(POINTS10)(BAD)(POINTS10)(POINTS10)(POINTS10)
	(BAD)(POINTS10)(BAD)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(BAD)(POINTS10)
	(POINTS10)(BAD)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(BAD)(POINTS10)
	(POINTS50)(BAD)(POINTS10)(BAD)(POINTS10)(BAD)(POINTS10)(POINTS10)(POINTS10)(POINTS10)
	(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10)
	(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10)
	(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10)
	(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10)
	(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS50)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10);
	
	//prize set 2
	std::vector<PrizeType> prizeSet2 =  boost::assign::list_of
	(POINTS10)(POINTS50)(POINTS10)(BAD)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS10)
	(POINTS10)(POINTS10)(POINTS10)(BAD)(POINTS10)(POINTS10)(POINTS10)(POINTS10)(POINTS25)(POINTS10)
	(POINTS25)(POINTS10)(POINTS10)(BAD)(POINTS10)(POINTS25)(POINTS10)(POINTS25)(POINTS10)(POINTS10)
	(POINTS25)(POINTS50)(POINTS10)(BAD)(POINTS10)(POINTS10)(POINTS25)(POINTS50)(POINTS50)(POINTS10)
	(POINTS25)(POINTS50)(POINTS50)(BAD)(POINTS50)(POINTS10)(POINTS25)(POINTS25)(POINTS10)(POINTS25)
	(POINTS25)(POINTS10)(POINTS10)(BAD)(POINTS10)(POINTS10)(POINTS25)(POINTS50)(POINTS10)(POINTS10)
	(POINTS25)(POINTS10)(POINTS10)(BAD)(POINTS10)(POINTS10)(POINTS25)(POINTS10)(POINTS25)(POINTS10)
	(POINTS25)(POINTS10)(POINTS10)(BAD)(POINTS25)(POINTS10)(POINTS25)(POINTS10)(POINTS10)(POINTS25)
	(POINTS25)(POINTS50)(POINTS10)(BAD)(POINTS10)(POINTS50)(POINTS25)(POINTS10)(POINTS50)(POINTS10)
	(POINTS50)(POINTS10)(POINTS10)(BAD)(POINTS25)(POINTS50)(POINTS25)(POINTS10)(POINTS25)(POINTS10);
	
	//prizeSets.push_back(prizeSet1);
	prizeSets.push_back(prizeSet2);
	
	std::vector<int> timeSet1 = boost::assign::list_of
	(4)(2)(4)(9)(4)(2)(9)(2)(10)(2)
	(4)(4)(6)(12)(4)(4)(4)(2)(4)(4)
	(4)(11)(4)(4)(4)(2)(2)(4)(8)(4)
	(4)(4)(6)(4)(4)(4)(4)(8)(4)(4)
	(4)(4)(4)(6)(4)(4)(4)(4)(4)(4)
	(4)(4)(2)(2)(2)(6)(2)(4)(4)(4)
	(4)(8)(4)(4)(2)(12)(12)(12)(12)(4)
	(4)(4)(4)(4)(4)(4)(4)(4)(4)(4)
	(4)(4)(4)(2)(2)(2)(4)(4)(4)(4)
	(4)(4)(4)(3)(4)(4)(4)(8)(8)(4)
	(4)(8)(4)(4)(8)(4)(2)(4)(4)(4);

	
	std::vector<int> timeSet2 = boost::assign::list_of
	(4)(4)(6)(12)(4)(4)(4)(2)(4)(4)
	(4)(4)(6)(4)(4)(4)(4)(8)(4)(4)
	(4)(2)(4)(9)(4)(2)(9)(2)(10)(2)
	(4)(11)(4)(4)(4)(2)(2)(4)(8)(4)
	(4)(4)(4)(6)(4)(4)(4)(4)(4)(4)
	(4)(4)(4)(3)(4)(12)(12)(12)(12)(4)
	(4)(4)(2)(2)(2)(6)(2)(4)(4)(4)
	(2)(2)(2)(2)(2)(2)(2)(4)(8)(4)
	(4)(4)(4)(4)(4)(4)(4)(4)(4)(4)
	(4)(8)(4)(4)(2)(12)(4)(8)(8)(4)
	(4)(8)(4)(4)(8)(4)(2)(4)(4)(4);

	timeSets.push_back(timeSet1);
	timeSets.push_back(timeSet2);

	

}

void PrizeController::newGame(){
	currentPrizeIndex = 0;
	currentPrizeSetIndex = 0;
	currentTimeIndex=0;
	
	if(++currentTimeSetIndex >= timeSets.size()) currentTimeSetIndex = 0;;
}

WindowData PrizeController::getNextPrize(){
	WindowData data;
	data.prizeType = prizeSets[currentPrizeSetIndex][currentPrizeIndex];
	data.windowDelay =  timeSets[currentTimeSetIndex][currentTimeIndex];
	
	if(++currentPrizeIndex >= prizeSets[currentPrizeSetIndex].size()) currentPrizeIndex = 0;;
	if(++currentTimeIndex >= timeSets[currentTimeSetIndex].size()) currentTimeIndex = 0;;
	
	return data;
	
}



