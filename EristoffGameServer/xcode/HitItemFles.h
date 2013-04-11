//
//  HitItemFles.h
//  EristoffGameServer
//
//  Created by Kris Temmerman on 17/10/12.
//
//

#ifndef EristoffGameServer_HitItemFles_h
#define EristoffGameServer_HitItemFles_h

#include "npMesh.h"
#include "cinder/Timeline.h"
class HitItemFles
{
public:
    HitItemFles(){
		used =false;
        x=0;
        y=0;
        z=0;
        
        rotX=0;
        rotY=0;
        rotZ=0;
		openTimer = -1;
        
        
    }
   
    void update();
    void hideComplete(){x =0; y=-1500;z=0;rotX =0;rotY=0;rotZ=0;scalef=0;
		update();used =true;std::cout << "hide complete" << std::endl;
};
    void updateFrame();
     void show();
    void hide();
     void hit() ;
    
    int ItemID;
    npMesh *hitMesh;
    npMesh *visualMesh1;
     npMesh *visualMesh2;
    bool used;
	bool isHit;
	
    Vec3<float> basePos;
    
    float x;
    float y;
    float z;
    
    float rotX;
    float rotY;
    float rotZ;
    
    Anim<float> yPos;
    Anim<float> yRotAnim;
    Anim<float> zRotAnim;
	Anim<float> zPos;
	Anim<float> scalef;
	float openTimer;
	float openDelay;
};



#endif
