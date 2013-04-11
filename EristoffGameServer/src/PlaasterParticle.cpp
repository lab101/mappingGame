//
//  PlaasterParticle.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 15/10/12.
//
//

#include "PlaasterParticle.h"
void PlaasterParticle::setup(PlaasterTriangle *triangle){

    partMesh =new npMesh();
    partMesh->stride = 2+3+3;
   xs = x = triangle->center.x;
    ys =y  = triangle->center.y ;
    zs =z = triangle->center.z;

    int count =0;
    partMesh->numVertices=3;
    partMesh->vertices = new float[3*partMesh->stride];
    partMesh->vertices[count++ ]  = triangle->v1.vertex.x -triangle->center.x;
    partMesh->vertices[count++ ]  = triangle->v1.vertex.y  -triangle->center.y;
    partMesh->vertices[count++ ]  = triangle->v1.vertex.z  -triangle->center.z;
    
    partMesh->vertices[count++ ]  = triangle->v1.normal.x;
    partMesh->vertices[count++ ]  = triangle->v1.normal.y;
    partMesh->vertices[count++ ]  = triangle->v1.normal .z;
    
    partMesh->vertices[count++ ]  =triangle->v1.uv.x;
    partMesh->vertices[count++ ]  = triangle->v1.uv.y;
    
    
    partMesh->vertices[count++ ]  =triangle->v2.vertex.x-triangle->center.x;
    partMesh->vertices[count++ ]  = triangle->v2.vertex.y  -triangle->center.y;
    partMesh->vertices[count++ ]  = triangle->v2.vertex.z -triangle->center.z;
    
    partMesh->vertices[count++ ]  = triangle->v2.normal.x;
    partMesh->vertices[count++ ]  = triangle->v2.normal.y;
    partMesh->vertices[count++ ]  = triangle->v2.normal .z;
    
    partMesh->vertices[count++ ]  = triangle->v2.uv.x;
    partMesh->vertices[count++ ]  = triangle->v2.uv.y;
    
    partMesh->vertices[count++ ]  = triangle->v3.vertex.x-triangle->center.x;
    partMesh->vertices[count++ ]  = triangle->v3.vertex.y -triangle->center.y;
    partMesh->vertices[count++ ]  = triangle->v3.vertex.z -triangle->center.z;    
    partMesh->vertices[count++ ]  = triangle->v3.normal.x;
    partMesh->vertices[count++ ]  = triangle->v3.normal.y;
    partMesh->vertices[count++ ]  = triangle->v3.normal .z;
    
    partMesh->vertices[count++ ]  = triangle->v3.uv.x;
    partMesh->vertices[count++ ]  = triangle->v3.uv.y;
    
    partMesh->numIndices=3;
    partMesh->indices=new unsigned int [3];
    partMesh->indices[0] =0;
    partMesh->indices[1] =1;
    partMesh->indices[2] =2;
   // partMesh->createBuffer();
    
  
   // rotX =((float)rand()/RAND_MAX  *dist)/100;
   //rotY = ((float)rand()/RAND_MAX  *dist)/100;
    
}
void PlaasterParticle::reset(float dist,Vec2f dir )
{
    x=xs;
    y=ys;
    z=zs;
    
    speedZ = dist/2+(float)rand()/RAND_MAX *dist;
    speedY = (float)rand()/RAND_MAX *30 *dir.y;
    speedX = (float)rand()/RAND_MAX *30 *dir.x;
    
    rotY = (float)rand()/RAND_MAX; //*dir.y;
    rotX = (float)rand()/RAND_MAX;// *dir.x;
}
void PlaasterParticle::update(){

    if (z>400)return;
   z+=speedY;
   y+=speedZ;
   x+=speedX;
    speedX*=0.9;
     speedZ*=0.9;
    speedY +=2;

    partMesh->objectMatrix.setToIdentity();
  partMesh->objectMatrix.translate(Vec3f(x,z,y));
    partMesh->objectMatrix.rotate(Vec3f::xAxis(), rotX);
partMesh->objectMatrix.rotate(Vec3f::yAxis(), rotY);




}
