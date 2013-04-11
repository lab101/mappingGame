//
//  HitItemFles.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 17/10/12.
//
//

#include "HitItemFles.h"
#include "cinder/Rand.h"
#include "SoundController.h"
#include "SettingManager.h"

using namespace ci;
using namespace ci::app;

void HitItemFles:: update()
{
	
	if (used) return;
	
	if(openTimer > 0 && (getElapsedSeconds() - openTimer) > openDelay){
		//used = true;
		openTimer = -1;
		timeline().apply(&yRotAnim,9.3f,8.1f,EaseInCubic());
		timeline().apply(&yPos,400.0f,SettingManager::Instance()->bottleDropSpeed,EaseInCubic()).finishFn( std::bind(&HitItemFles::hide, this));
		SoundController::Instance()->Parachutte();
		
		cout << "start bottle : " << x  << std::endl;
	}
	

	
	
	
    updateFrame();
    visualMesh1->objectMatrixModel.setToIdentity();
	
    visualMesh1->objectMatrix.setToIdentity();
    visualMesh1->objectMatrix.translate(Vec3<float>(basePos.x+x,basePos.y+y,basePos.z+z));
	visualMesh1->objectMatrix.scale(Vec3<float>(scalef,scalef,scalef));

    visualMesh1->objectMatrix.rotate(Vec3<float>(0,0,1),rotZ);
    visualMesh1->objectMatrix.rotate(Vec3<float>(0,1,0),rotY);
    visualMesh1->objectMatrix.rotate(Vec3<float>(1,0,0),rotX);
    visualMesh2->objectMatrix  =  visualMesh1->objectMatrix;
    hitMesh->objectMatrix  =  visualMesh1->objectMatrix;
    
    visualMesh2->objectMatrix.translate(Vec3<float>(0,0,250));
	hitMesh->objectMatrix.translate(Vec3<float>(0,0,0));
    visualMesh1->resolveModelMatrix();
	visualMesh2->resolveModelMatrix();
    hitMesh->resolveModelMatrix();
}





void HitItemFles::updateFrame()
{
	if(yPos > -1000 && !isHit)	x +=  sin(getElapsedSeconds() * 1.2 ) * 5.7;

    if(!isHit) {
		rotZ =sin(getElapsedSeconds()* 2) / 6.0;
	}else{
		rotZ = zRotAnim;
	}
    rotY = yRotAnim;
    rotX =3.1415/2;
	y = yPos;
	z = zPos;
}

void HitItemFles::show()
{
	
	used = false;
	isHit = false;
	
	openTimer = getElapsedSeconds();
	openDelay= ci::randFloat(20,38);
	scalef = 1;

	yPos = -1520;
	zPos = 300;
	yRotAnim=0;
	x = ci::randFloat(700.0f,1200.0f);
	
	std::cout << "-----fles show---------" << x << std::endl;
	
	updateFrame();
	
	
	
	//	timeline().apply(&zPos,120.0f,0.3f,EaseOutCubic()).delay(7.0f);
    
}
void HitItemFles::hide()
{
	hideComplete();
    openTimer = -1;
	//	timeline().apply(&zPos,-100.0f,0.1f,EaseOutCubic());
	//	timeline().apply(&yPos,0.0f,0.2f,EaseOutCubic()).finishFn( std::bind( &HitItemFles::hideComplete, this));
}

void HitItemFles::hit()
{
    openTimer = -1;

	if(isHit) return;
//<<<<<<< HEAD
	//timeline().apply(&yPos,400.0f,1.1f,EaseInCubic()).finishFn( std::bind(&HitItemFles::hide, this));
//	timeline().apply(&yRotAnim,26.0f,2.1f,EaseInCubic());
  //  	timeline().apply(&scalef,0.0f,0.5f,EaseInBack()).delay(1);
	//timeline().apply(&zPos,626.0f,0.2f,EaseInCubic());
//=======
	
//>>>>>>> 9386f00f5760c072aceb3b3b029b837c4c0eb920
	timeline().removeTarget(&yPos);
	std::cout << "-----hit---------" << y << std::endl;

	if(y > -200){
		timeline().apply(&yPos, yPos.value() - 200, 0.5f,EaseInCubic());
		std::cout << "-----correction---------" << y << std::endl;

	}else{
		timeline().apply(&yPos, yPos.value(), 0.1f,EaseInCubic());

	}
		
	
	//timeline().apply(&yPos,400.0f,1.1f,EaseInCubic()).finishFn( std::bind(&HitItemFles::hide, this));
	timeline().apply(&yRotAnim,36.0f,3.1f,EaseInCubic());
	// zet fles terug recht voor oke belichting
	zRotAnim = rotZ;
	timeline().apply(&zRotAnim,.0f,1.1f,EaseInCubic());
	timeline().apply(&zPos,626.0f,0.2f,EaseInCubic());
	timeline().apply(&scalef,1.5f,0.2f,EaseInCubic());
	
	// animatie go back
	timeline().appendTo(&zPos,-300.0f,0.6f,EaseInCubic()).delay(2);
	timeline().appendTo(&scalef,0.0f,0.6f,EaseInCubic()).delay(2.2).finishFn( std::bind(&HitItemFles::hide, this));

	
	//timeline().apply(&yPos,400.0f,1.1f,EaseInCubic()).delay(2).finishFn( std::bind(&HitItemFles::hide, this));
	isHit = true;
	
    
}