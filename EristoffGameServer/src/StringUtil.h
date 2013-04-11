//
//  StringUtil.h
//  EristoffGameServer
//
//  Created by Kris Meeusen on 16/10/12.
//
//

#ifndef EristoffGameServer_StringUtil_h
#define EristoffGameServer_StringUtil_h

std::string trimToLength(std::string input,int maxLength){
	if (input.size() > maxLength) {
		input = input.substr(0,maxLength);
	}
	
	return input;
}

#endif
