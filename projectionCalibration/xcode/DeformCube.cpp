#include "DeformCube.h"

DeformCube::DeformCube()
{


}

void DeformCube::setup(float x, float y,float width, float height, float depth)
{
	float z = (((float)rand()/RAND_MAX)-0.5)*1000;

	TRFront=new Vec3f(x ,y , 0.0f+z );
	TLFront =new Vec3f(x+width ,y ,0.0f+z );
	BRFront=new Vec3f( x,y+height , 0.0f +z);
	BLFront=new Vec3f( x+width,y+height, 0.0f +z);
	

	TRBack=new Vec3f(x,y ,depth +z);
	TLBack=new Vec3f(x+width,y,depth +z);
	BRBack=new Vec3f( x,y+height,depth +z);
	BLBack=new Vec3f( x+width,y+height , depth +z);
	


}

void DeformCube::getVertices(float *vertices, int start)
{
	// front plane
	//console() << ""<<*TLFront <<std::endl;
	vertices[start++]=TLFront->x;
	vertices[start++]=TLFront->y;
	vertices[start++]=TLFront->z;

	vertices[start++]=TRFront->x;
	vertices[start++]=TRFront->y;
	vertices[start++]=TRFront->z;

	vertices[start++]=BRFront->x;
	vertices[start++]=BRFront->y;
	vertices[start++]=BRFront->z;

	vertices[start++]=BLFront->x;
	vertices[start++]=BLFront->y;
	vertices[start++]=BLFront->z;


		// back plane

	vertices[start++]=TLFront->x;
	vertices[start++]=TLFront->y;
	vertices[start++]=TLFront->z;

	vertices[start++]=TRFront->x;
	vertices[start++]=TRFront->y;
	vertices[start++]=TRFront->z;

	vertices[start++]=BRFront->x;
	vertices[start++]=BRFront->y;
	vertices[start++]=BRFront->z;

	vertices[start++]=BLFront->x;
	vertices[start++]=BLFront->y;
	vertices[start++]=BLFront->z;


		// front plane

	vertices[start++]=TLFront->x;
	vertices[start++]=TLFront->y;
	vertices[start++]=TLFront->z;

	vertices[start++]=TRFront->x;
	vertices[start++]=TRFront->y;
	vertices[start++]=TRFront->z;

	vertices[start++]=BRFront->x;
	vertices[start++]=BRFront->y;
	vertices[start++]=BRFront->z;

	vertices[start++]=BLFront->x;
	vertices[start++]=BLFront->y;
	vertices[start++]=BLFront->z;


		// front plane

	vertices[start++]=TLFront->x;
	vertices[start++]=TLFront->y;
	vertices[start++]=TLFront->z;

	vertices[start++]=TRFront->x;
	vertices[start++]=TRFront->y;
	vertices[start++]=TRFront->z;

	vertices[start++]=BRFront->x;
	vertices[start++]=BRFront->y;
	vertices[start++]=BRFront->z;

	vertices[start++]=BLFront->x;
	vertices[start++]=BLFront->y;
	vertices[start++]=BLFront->z;


		// front plane

	vertices[start++]=TLFront->x;
	vertices[start++]=TLFront->y;
	vertices[start++]=TLFront->z;

	vertices[start++]=TRFront->x;
	vertices[start++]=TRFront->y;
	vertices[start++]=TRFront->z;

	vertices[start++]=BRFront->x;
	vertices[start++]=BRFront->y;
	vertices[start++]=BRFront->z;

	vertices[start++]=BLFront->x;
	vertices[start++]=BLFront->y;
	vertices[start++]=BLFront->z;


		// front plane

	vertices[start++]=TLFront->x;
	vertices[start++]=TLFront->y;
	vertices[start++]=TLFront->z;

	vertices[start++]=TRFront->x;
	vertices[start++]=TRFront->y;
	vertices[start++]=TRFront->z;

	vertices[start++]=BRFront->x;
	vertices[start++]=BRFront->y;
	vertices[start++]=BRFront->z;

	vertices[start++]=BLFront->x;
	vertices[start++]=BLFront->y;
	vertices[start++]=BLFront->z;
}