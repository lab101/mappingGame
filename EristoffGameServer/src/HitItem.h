//
//  HitItem.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 04/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef EristoffGameServer_HitItem_h
#define EristoffGameServer_HitItem_h
#include "npMesh.h"
class HitItem
{
public:
    HitItem(){used =false;
        x=0;
        y=0;
        z=0;
        
        rotX=0;
        rotY=0;
        rotZ=0;
    
    }
    void update();
    void hideComplete(){used =false;x =0; y=0;z=0;rotX =0;rotY=0;rotZ=0;};
     virtual void updateFrame()=0;
    virtual void show()=0;
    virtual void hide()=0;
    virtual void hit() =0;
  
    int ItemID;
    npMesh *hitMesh;
    npMesh *visualMesh;
    bool used;
    Vec3<float> basePos;
    
    float x;
    float y;
    float z;
    
    float rotX;
    float rotY;
    float rotZ;
};


#endif
