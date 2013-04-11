//
//  PlaasterTriangle.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 15/10/12.
//
//

#include "PlaasterTriangle.h"
void PlaasterTriangle::calculateCenter()
{

    center =  v1.vertex + v2.vertex +v3.vertex;
    center/=3.0f;

}