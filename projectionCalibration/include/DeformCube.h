#pragma once

#include "cinder/app/AppBasic.h"

#include "cinder/Vector.h"

using namespace ci;


using namespace ci::app;
using namespace std;


class DeformCube
{
public:
	DeformCube();
	void setup(float x,float y ,float sizeW,float sizeH,float d);
	void getVertices(float *vertices, int start);


	Vec3f *TLFront;
	Vec3f *TRFront;
	Vec3f *BLFront;
	Vec3f *BRFront;


	Vec3f *TLBack;
	Vec3f *TRBack;
	Vec3f *BLBack;
	Vec3f *BRBack;
};