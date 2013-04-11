
#include "ProjectionCamera.h"

void ProjectionCamera::moveLight()
{
    //console()<< "moveLight()";
   lightPosTar.x = (((float )rand()/RAND_MAX)-0.5 )*2;
 lightPosTar.y = ((float )rand()/RAND_MAX)+0.1;
    lightPosTar.z = -1;
    lightPosTar.normalize();
    lightPosTar *= -2000;
}
void ProjectionCamera::set(float x,float y,float z,float w, float h,float buildingOffsetX,float buildingOffsetY)
{

    lightPos.x +=(lightPosTar.x-lightPos.x)/20;
    lightPos.y  +=(lightPosTar.y-lightPos.y)/20;
    lightPos.z +=(lightPosTar.z-lightPos.z)/20;
    
    _buildingOffsetY=buildingOffsetY;
    _buildingOffsetX=buildingOffsetX;
	float halfProjectionWidth =w/2;
	float halfProjectionHeight =h/2;
	Vec3f  projectrorPos;
	projectrorPos.x =x;
	projectrorPos.y =y;
	projectrorPos.z=z;


	float left = (halfProjectionWidth + projectrorPos.x) / projectrorPos.z ;
	float right = (-halfProjectionWidth + projectrorPos.x) / projectrorPos.z;
	float bottom =  (-halfProjectionHeight + projectrorPos.y) / projectrorPos.z;
	float top =  (halfProjectionHeight  + projectrorPos.y) / projectrorPos.z;


	
	makeFrustumMatrix(left, right,top,bottom, 1,5000,perspectiveMatrix);

    makeLookAtViewMatrix(Vec3f(-projectrorPos.x,-projectrorPos.y,projectrorPos.z ), Vec3f(-projectrorPos.x,-projectrorPos.y,0), Vec3f(0,1,0),lookatMatrix);
	
   
    
	offMatrix.setToIdentity();
	offMatrix.translate(Vec3f(-buildingOffsetX,-buildingOffsetY,0));
   // offMatrix.rotate(Vec3f(0,1,0),3.14 );
    
    worldMatrix = offMatrix*lookatMatrix;

    cinder::Matrix44f addJustment;
    addJustment.setToIdentity();
      addJustment.scale (Vec3f(globalScale,globalScale,globalScale));
    addJustment.translate(Vec3<float>(globalX,globalY,0));
 
    perspectiveMatrix = addJustment *perspectiveMatrix;
    
    perspectiveMatrixInv =worldMatrix*perspectiveMatrix;
    perspectiveMatrixInv.invert();
    //console() << perspectiveMatrix<<std::endl;
    //console() << perspectiveMatrixInv<<std::endl;
    
    setShadowModel();
   //worldMatrixShadow.translate(Vec3f( buildingOffsetX,100,0));
    setShadowProjection();
	//makeFrustumMatrix(left, right,top,bottom, 1,8000,perspectiveMatrixShadow);
    // 	worldMatrixShadow.setToIdentity();
   // worldMatrixShadow.translate(Vec3f(0,-1000,0));

}

void ProjectionCamera::makeFrustumMatrix(float left,  float right,float bottom, float top,float zNear, float zFar,Matrix44f &_perspectiveMatrix)
{
  

	float  A = (right+left)/(right-left);
	float  B = (top+bottom)/(top-bottom);
    float  C = -(zFar+zNear)/(zFar-zNear)/(zFar+zNear);
    float  D = -2.0f*zFar*zNear/(zFar-zNear);
 

 
	_perspectiveMatrix.set(2.0*zNear/(right-left),0,0,0,0, 2.0*zNear/(top-bottom),0,0,A,B,C,-1,0,0,D,0);
         
}
      
void  ProjectionCamera::makeLookAtViewMatrix(Vec3f camPos ,Vec3f  center,Vec3f up,Matrix44f &_lookatMatrix)
{
  Vec3f zaxis = camPos-center;
    zaxis.normalize();
    Vec3f xaxis = up.cross( zaxis);
    xaxis.normalize();
    Vec3f  yaxis  =zaxis.cross(    xaxis);
          
	_lookatMatrix.set(xaxis.x,yaxis.x,zaxis.x,0,xaxis.y,yaxis.y,zaxis.y,0,xaxis.z,yaxis.z,zaxis.z,0,-xaxis.dot( camPos),-yaxis.dot( camPos),-zaxis.dot( camPos),1);
	
}
void ProjectionCamera::setShadowModel()
{
    
    
    Vec3f lightPosLocal =Vec3f  ( _buildingOffsetX,_buildingOffsetY,0)+lightPos;
    
    Vec3f mViewDirection  =-(lightPos);
    
    Quatf mOrientation = Quatf( Matrix44f::alignZAxisWithTarget( -mViewDirection, Vec3f::zAxis() ) ).normalized();
	 Vec3f mW = -mViewDirection.normalized();
	 Vec3f mU = mOrientation * Vec3f::xAxis();
 Vec3f 	mV = mOrientation * Vec3f::yAxis();
	
	Vec3f d( -lightPosLocal.dot( mU ), -lightPosLocal.dot( mV ), -lightPosLocal.dot( mW ) );
	float *m = worldMatrixShadow.m;
	m[ 0] = mU.x; m[ 4] = mU.y; m[ 8] = mU.z; m[12] =  d.x;
	m[ 1] = mV.x; m[ 5] = mV.y; m[ 9] = mV.z; m[13] =  d.y;
	m[ 2] = mW.x; m[ 6] = mW.y; m[10] = mW.z; m[14] =  d.z;
	m[ 3] = 0.0f; m[ 7] = 0.0f; m[11] = 0.0f; m[15] = 1.0f;
    
}
void ProjectionCamera::setShadowProjection()
{
    
    float  mFov			= 70;
    float	mAspectRatio	= 1;
	float mNearClip		= 1000;
	float mFarClip		= 3000;
    
    
    
	float mFrustumTop		=  mNearClip * math<float>::tan( (float)M_PI / 180.0f * mFov * 0.5f );
	float mFrustumBottom	= -mFrustumTop;
	float mFrustumRight	=  mFrustumTop * mAspectRatio;
	float mFrustumLeft	= -mFrustumRight;
    
	float *m =  perspectiveMatrixShadow.m;
	m[ 0] =  2.0f * mNearClip / ( mFrustumRight - mFrustumLeft );
	m[ 4] =  0.0f;
	m[ 8] =  ( mFrustumRight + mFrustumLeft ) / ( mFrustumRight - mFrustumLeft );
	m[12] =  0.0f;
    
	m[ 1] =  0.0f;
	m[ 5] =  2.0f * mNearClip / ( mFrustumTop - mFrustumBottom );
	m[ 9] =  ( mFrustumTop + mFrustumBottom ) / ( mFrustumTop - mFrustumBottom );
	m[13] =  0.0f;
    
	m[ 2] =  0.0f;
	m[ 6] =  0.0f;
	m[10] = -( mFarClip + mNearClip ) / ( mFarClip - mNearClip );
	m[14] = -2.0f * mFarClip * mNearClip / ( mFarClip - mNearClip );
    
	m[ 3] =  0.0f;
	m[ 7] =  0.0f;
	m[11] = -1.0f;
	m[15] =  0.0f;
    /*
	m = mInverseProjectionMatrix.m;
	m[ 0] =  ( mFrustumRight - mFrustumLeft ) / ( 2.0f * mNearClip );
	m[ 4] =  0.0f;
	m[ 8] =  0.0f;
	m[12] =  ( mFrustumRight + mFrustumLeft ) / ( 2.0f * mNearClip );
    
	m[ 1] =  0.0f;
	m[ 5] =  ( mFrustumTop - mFrustumBottom ) / ( 2.0f * mNearClip );
	m[ 9] =  0.0f;
	m[13] =  ( mFrustumTop + mFrustumBottom ) / ( 2.0f * mNearClip );
    
	m[ 2] =  0.0f;
	m[ 6] =  0.0f;
	m[10] =  0.0f;
	m[14] = -1.0f;
    
	m[ 3] =  0.0f;
	m[ 7] =  0.0f;
	m[11] = -( mFarClip - mNearClip ) / ( 2.0f * mFarClip*mNearClip );
	m[15] =  ( mFarClip + mNearClip ) / ( 2.0f * mFarClip*mNearClip );*/
}

