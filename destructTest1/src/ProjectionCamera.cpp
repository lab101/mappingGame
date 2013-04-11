
#include "ProjectionCamera.h"


void ProjectionCamera::setup()
{
	float halfProjectionWidth =1000;
	float halfProjectionHeight =1000;
	Vec3f  projectrorPos;
	projectrorPos.x = 0;
	projectrorPos.y =-100;
	projectrorPos.z= 1000;


	float left = (halfProjectionWidth + projectrorPos.x) / projectrorPos.z ;
	float right = (-halfProjectionWidth + projectrorPos.x) / projectrorPos.z;
	float bottom =  (-halfProjectionHeight + projectrorPos.y) / projectrorPos.z;
	float top =  (halfProjectionHeight  + projectrorPos.y) / projectrorPos.z;

	worldMatrix.translate(Vec3f(100,200,20));
	

	Vec4f a =worldMatrix.postMultiply(Vec4f(0,0,0,1));
	
	makeFrustumMatrix(left, right,top,bottom, 1, 2000);

    makeLookAtViewMatrix(Vec3f(-projectrorPos.x,-projectrorPos.y,projectrorPos.z ), Vec3f(-projectrorPos.x,-projectrorPos.y,0), Vec3f(0,1,0));
	
		console()<<"test:  "<<	worldMatrix<<std::endl<<	perspectiveMatrix <<std::endl;

}

void ProjectionCamera::makeFrustumMatrix(float left,  float right,float bottom, float top,float zNear, float zFar)
{
  

	float  A = (right+left)/(right-left);
	float  B = (top+bottom)/(top-bottom);
    float  C = -(zFar+zNear)/(zFar-zNear);
    float  D = -2.0f*zFar*zNear/(zFar-zNear);
 

 
	perspectiveMatrix.set(2.0*zNear/(right-left),0,0,0,0, 2.0*zNear/(top-bottom),0,0,A,B,C,-1,0,0,D,0);
         
}
      
void  ProjectionCamera::makeLookAtViewMatrix(Vec3f camPos ,Vec3f  center,Vec3f up)
{
  Vec3f zaxis = camPos-center;
    zaxis.normalize();
    Vec3f xaxis = up.cross( zaxis);
    xaxis.normalize();
    Vec3f  yaxis  =zaxis.cross(    xaxis);
          
	worldMatrix.set(xaxis.x,yaxis.x,zaxis.x,0,xaxis.y,yaxis.y,zaxis.y,0,xaxis.z,yaxis.z,zaxis.z,0,-xaxis.dot( camPos),-yaxis.dot( camPos),-zaxis.dot( camPos),1);
	
}
