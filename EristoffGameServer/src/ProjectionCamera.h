
#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/Matrix44.h"
#include "cinder/Quaternion.h"
using namespace ci;

using namespace ci::app;

class ProjectionCamera
{

public:
	ProjectionCamera(){lightPos =  Vec3<float>(300,300,2000);lightPosTar=  Vec3<float>(200,100,2000);globalX =0;globalY=0;globalScale =1;};
	
	void set(float x,float y,float z,float w, float h,float buildingOffsetX,float buildingOffsetY);

	void makeFrustumMatrix(float left,  float right,float bottom, float top,float zNear, float zFar,Matrix44f &_perspectiveMatrix);
	void  makeLookAtViewMatrix(Vec3f camPos ,Vec3f  center,Vec3f up,Matrix44f &_worldMatrix);
    void setShadowProjection();
    void setShadowModel();
	cinder::Matrix44f perspectiveMatrix;
    
    cinder::Matrix44f offMatrix;
    cinder::Matrix44f lookatMatrix;
	cinder::Matrix44f worldMatrix;
    
    
    cinder::Matrix44f worldMatrixInv;
    cinder::Matrix44f perspectiveMatrixInv;
    cinder::Matrix44f worldMatrixShadow;
     cinder::Matrix44f perspectiveMatrixShadow;
    float _buildingOffsetY;
    float _buildingOffsetX;
    Vec3<float> lightPos;
      Vec3<float> lightPosTar;
    void moveLight();
    
    float globalX;
    float globalY;
    float globalScale;
  
};
