
#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/Matrix44.h"

using namespace ci;

using namespace ci::app;

class ProjectionCamera
{

public:
	ProjectionCamera(){};
	
	void set(float x,float y,float z,float w, float h,float f);

	void makeFrustumMatrix(float left,  float right,float bottom, float top,float zNear, float zFar);
	void  makeLookAtViewMatrix(Vec3f camPos ,Vec3f  center,Vec3f up);
	float frustrumAdj;
	cinder::Matrix44f perspectiveMatrix;
	cinder::Matrix44f worldMatrix;
};
