//
//  Plaaster.cpp
//  EristoffGameServer
//
//  Created by Kris Temmerman on 15/10/12.
//
//

#include "Plaaster.h"
void Plaaster::setOutro()
{
    particles.clear();
    for (int i=0;i< triangles.size();i++)
    {
                       
              
                
                    
                    PlaasterParticle *p = triangles[i]->particle;
                    p->reset((float )rand()/RAND_MAX*100 ,Vec2f(0,0));
                    particles.push_back(p);
                    
               
      
      
    }


}

void Plaaster::setup(npMesh *base)
{
    baseMesh = base;
    devide();
}
void Plaaster::reset()
{
    particles.clear();
    triangles.clear();
    for (int i=0;i< trianglesRoot.size();i++)
    {
        triangles.push_back(trianglesRoot[i]);
        
    }
    
    updateMainMesh();
}
void Plaaster::update()
{
    for( int i=0;i< particles.size();i++)
    {
    
        particles[i]->update();
    }

}
int Plaaster::shoot(Vec3f pos)
{
	int count=0;
    for (int i=0;i< triangles.size();i++)
    {
        if (triangles[i]->center.x > pos.x -70 && triangles[i]->center.x < pos.x +70  )
        {
            if (triangles[i]->center.z > pos.y -70 && triangles[i]->center.z < pos.y +70  )
            {
                
              
                Vec2f a = Vec2f(triangles[i]->center.x ,triangles[i]->center.z);
                float dist =a.distance(Vec2f(pos.x,pos.y ));
                Vec2f dir =a-Vec2f(pos.x,pos.y );
                dir.normalize();
                
               //if (dist < 70)
                {
                    count ++;
                    
                    
                PlaasterParticle *p = triangles[i]->particle;
                    p->reset(100-dist ,dir);
                particles.push_back(p);
                
            triangles.erase(triangles.begin()+i );
            //    cinder::app::console()<< "delete";
                }
            i--;
            }
        }
    
    }
    //cinder::app::console()<< count <<endl; ;
    updateMainMesh();
	
	return count;

}
void Plaaster::updateMainMesh()
{
    renderMesh->numIndices = triangles.size()*3;
    int count =0;
    for(int i=0;i<triangles.size();i++)
    {
        renderMesh->vertices[count++ ]  = triangles[i]->v1.vertex.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v1.vertex.y ;
        renderMesh->vertices[count++ ]  = triangles[i]->v1.vertex.z ;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v1.normal.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v1.normal.y;
        renderMesh->vertices[count++ ]  = triangles[i]->v1.normal .z;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v1.uv.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v1.uv.y;
        
        
        renderMesh->vertices[count++ ]  = triangles[i]->v2.vertex.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.vertex.y ;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.vertex.z ;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v2.normal.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.normal.y;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.normal .z;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v2.uv.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.uv.y;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v3.vertex.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.vertex.y ;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.vertex.z ;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v3.normal.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.normal.y;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.normal .z;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v3.uv.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.uv.y;
        
        
        
    }
    glBindBuffer(GL_ARRAY_BUFFER, renderMesh->vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0,renderMesh->numVertices*renderMesh->stride*sizeof(float), renderMesh->vertices);
 //glBufferData(GL_ARRAY_BUFFER, renderMesh->numVertices*renderMesh->stride*sizeof(float), renderMesh->vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
void Plaaster::devide()
{
    int numIndices =  baseMesh->numIndices;
    int stride  = baseMesh->stride;
    triangles.clear();
   
    for (int i=0; i<   numIndices; i+=3)
    {
        unsigned int i1  = baseMesh->indices[i];
        unsigned int i2  = baseMesh->indices[i+1];
        unsigned int i3  = baseMesh->indices[i+2];
        
        PlaasterTriangle * plaasterTri = new PlaasterTriangle();
        
        plaasterTri->v1.setData(baseMesh->vertices, i1*stride);
         plaasterTri->v2.setData(baseMesh->vertices, i2*stride);
         plaasterTri->v3.setData(baseMesh->vertices, i3*stride);
        plaasterTri->calculateCenter();
        
        
        PlaasterParticle *p = new PlaasterParticle();
        p->setup(plaasterTri);
        plaasterTri->particle = p;
      //  if ((float)rand()/RAND_MAX >0.5){
        trianglesRoot.push_back (plaasterTri);
        triangles.push_back (plaasterTri);
        //}
    }
    renderMesh =new npMesh();
    renderMesh->numIndices = triangles.size()*3;
    renderMesh->material = baseMesh->material;
    
    renderMesh->indices = new unsigned int[renderMesh->numIndices];
    for (unsigned int i=0;i< renderMesh->numIndices  ;i++)
    {
        renderMesh->indices[i] =i;
    }
    renderMesh->numVertices = triangles.size()*3;
    renderMesh->stride  = 3+3+2;
    renderMesh->vertices = new float [ renderMesh->numVertices *renderMesh->stride];
    
    int count =0;
    for(int i=0;i<triangles.size();i++)
    {
        renderMesh->vertices[count++ ]  = triangles[i]->v1.vertex.x;
         renderMesh->vertices[count++ ]  = triangles[i]->v1.vertex.y ;
         renderMesh->vertices[count++ ]  = triangles[i]->v1.vertex.z ;
        
         renderMesh->vertices[count++ ]  = triangles[i]->v1.normal.x;
         renderMesh->vertices[count++ ]  = triangles[i]->v1.normal.y;
         renderMesh->vertices[count++ ]  = triangles[i]->v1.normal .z;
        
         renderMesh->vertices[count++ ]  = triangles[i]->v1.uv.x;
         renderMesh->vertices[count++ ]  = triangles[i]->v1.uv.y;
        
        
        renderMesh->vertices[count++ ]  = triangles[i]->v2.vertex.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.vertex.y ;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.vertex.z ;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v2.normal.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.normal.y;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.normal .z;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v2.uv.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v2.uv.y;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v3.vertex.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.vertex.y ;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.vertex.z ;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v3.normal.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.normal.y;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.normal .z;
        
        renderMesh->vertices[count++ ]  = triangles[i]->v3.uv.x;
        renderMesh->vertices[count++ ]  = triangles[i]->v3.uv.y;
        
        
    
    }
    renderMesh->createBuffer();
    
    
    
}