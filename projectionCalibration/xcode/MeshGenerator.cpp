//
//  MeshGenerator.cpp
//  basicApp
//
//  Created by Kris Temmerman on 06/10/12.
//
//

#include "MeshGenerator.h"

void MeshGenerator::setup()
{
    singlePoint =false;
  
	
    renderer.setup();
    
    
    selectLines.push_back(Vec2<float>(0,0));
selectLines.push_back(Vec2<float>(1,1));
    
    mouseStart.x =0;
    mouseStop.x =0;
    mouseStart.y  =0;
    mouseStop.y  =0;
    mouseBL.x = 0;
     mouseBL.y = 0;
    mouseTR.x = 0;
        mouseTR.y = 0;
   
}
void MeshGenerator::init(npMesh *_mesh, ProjectionCamera *cam)
{
    mesh  = _mesh;
    vertices.clear();
    triangles.clear();
    
    int stride  = mesh->stride;
  
    for(int i=0;i<mesh->numVertices*stride;i+=stride)
    {
        MeshVertex *v =new MeshVertex();
        v->startVec.x =mesh->vertices[i];
        v->startVec.y =mesh->vertices[i+1];
        v->startVec.z =mesh->vertices[i+2];
        v->startVec.w =1;
       
        v->projectedVec =  cam->perspectiveMatrix.postMultiply( cam->worldMatrix.postMultiply(mesh->objectMatrix.postMultiply( v->startVec)));
       v->posVec.x = v->screenVec.x =  v->projectedVec.x /v->projectedVec.w/2+0.5;
        v->posVec.y = v->screenVec.y  = v->projectedVec.y /v->projectedVec.w /-2+0.5;
         v->screenVec.z = v->projectedVec.z /v->projectedVec.w;
        //console() << "vec "<< v->screenVec<< " " << v->startVec<< endl;
        v->uvVec.x =  v->posVec.x;
        v->uvVec.y=1.0f-v->posVec.y ;
        vertices.push_back(v);
    
    
    }
    for(int i=0;i<mesh->numIndices;i+=3)
    {
        MeshTriangle *t =new MeshTriangle();
        t->v1 =   vertices[mesh->indices[i]];
      
        t->v2 =   vertices[mesh->indices[i+1]];
        
        t->v3 =   vertices[mesh->indices[i+2]];
        
        t->calculateNormal();
       if ( t->normal.z <0) continue;
        
        t->v1->useCount++;
        t->v3->useCount++;
        t->v2->useCount++;
        triangles.push_back(t );
        
        
    }
    for(int i=0;i<vertices.size();i++)
    {
        if (vertices[i]->useCount ==0)
        {
            vertices.erase(vertices.begin()+i);
            i--;
        }
    
    }
    for(int i=0;i<vertices.size();i++)
    {
        vertices[i]->index =i;
    }

}

void MeshGenerator::mouseDown(int x,int y )
{
    if (! singlePoint)
    {
         mouseTR.x =  mouseBL.x= mouseStop.x = mouseStart.x =(float )x /screenW ;
        mouseTR.y =  mouseBL.y= mouseStop.y = mouseStart.y  =(float )y /screenH;
    
    }
   
}

void MeshGenerator::mouseUp(int x,int y)
{
    selectItems(shiftDown);
        
    mouseStart.x =0;
    mouseStop.x =0;
    mouseStart.y  =0;
    mouseStop.y  =0;
    mouseBL.x = 0;
    mouseBL.y = 0;
    mouseTR.x = 0;
    mouseTR.y = 0;

}
void MeshGenerator::mouseMove(int x,int y)
{
    if (! singlePoint)
    {
        mouseTR.x = mouseStop.x  =(float )x /screenW ;
          mouseBL.y= mouseStop.y   =(float )y /screenH;

    }
    
}
void MeshGenerator::selectSingle(int x,int y)
{
    
    
}
void MeshGenerator::moveSelected(int x,int y)
{
    float xMove = (float )x /screenW/4;
    float yMove = (float )y /screenH/4;
    ///console() << yMove << " " << xMove;
    
    
    for (int i=0;i<vertices.size();i++)
    {
        if (vertices[i]->isSelected)
        {
            vertices[i]->posVec.x +=xMove;
            vertices[i]->posVec.y +=yMove;
            
        
        };
    }
    
}

void MeshGenerator::update()
{
    selectLines.clear();
    selectLines.push_back(mouseStart);
    selectLines.push_back(mouseTR);
    
    selectLines.push_back(mouseTR);
    selectLines.push_back(mouseStop);
    
    selectLines.push_back(mouseStop);
    selectLines.push_back(mouseBL);
    
    selectLines.push_back(mouseBL);
    selectLines.push_back(mouseStart);
    
    
    pointLines.clear();
     pointLinesSelected.clear();
    for(int i=0;i<vertices.size();i++)
    {
        addPoint(vertices[i]->posVec,vertices[i]->isSelected);
    
    }
    
    triangleLines.clear();
    for(int i=0;i<triangles.size();i++)
    {
        addTriangle(triangles[i]);
        
    }
}

void MeshGenerator::draw()
{
    renderer.startFlat();
    renderer.r =1.0;renderer.g =1.0;renderer.b=1.0;
    renderer.drawFlat(triangleLines,GL_LINES);
    
    
    renderer.r =0.5;renderer.g =1;renderer.b=1;
        renderer.drawFlat(pointLines,GL_LINES);
    glLineWidth(2);
    renderer.r =1;renderer.g =1;renderer.b=1;
    renderer.drawFlat(pointLinesSelected,GL_LINES);
    glLineWidth(1);
    renderer.r =1;renderer.g =1;renderer.b=1;
    renderer.drawFlat(selectLines,GL_LINES);
    
    
    renderer.stop();

}
void MeshGenerator::addTriangle(MeshTriangle *t)
{
    triangleLines.push_back(t->v1->posVec);
 triangleLines.push_back(t->v2->posVec);
    
    triangleLines.push_back(t->v2->posVec);
    triangleLines.push_back(t->v3->posVec);
    
    triangleLines.push_back(t->v3->posVec);
    triangleLines.push_back(t->v1->posVec);
}

void MeshGenerator::addPoint(Vec2<float> p,bool sel)
{

    float psx =0.004;
    float psy =0.005;
    if (sel){
    pointLinesSelected.push_back(Vec2<float> (p.x-psx,p.y-psy));
  pointLinesSelected.push_back(Vec2<float> (p.x+psx,p.y+psy));
    pointLinesSelected.push_back(Vec2<float> (p.x-psx,p.y+psy));
   pointLinesSelected.push_back(Vec2<float> (p.x+psx,p.y-psy));
    }else
    {
        pointLines.push_back(Vec2<float> (p.x-psx,p.y-psy));
        pointLines.push_back(Vec2<float> (p.x+psx,p.y+psy));
        pointLines.push_back(Vec2<float> (p.x-psx,p.y+psy));
        pointLines.push_back(Vec2<float> (p.x+psx,p.y-psy));

    
    }

}

void MeshGenerator::selectItems(bool shiftDown)
{
    
    if (!shiftDown && !ctrlDown) {
        for (int i=0;i<vertices.size();i++)
        {
            vertices[i]->isSelected =false;
        }
    
    }
    float xMin = min( mouseStart.x,mouseStop.x);
     float xMax = max ( mouseStart.x,mouseStop.x);
    float yMin = min( mouseStart.y,mouseStop.y);
    float yMax = max ( mouseStart.y,mouseStop.y);
if (!ctrlDown) {
    for (int i=0;i<vertices.size();i++)
    {
        float vx   = vertices[i]->posVec.x;
        
        if (vx<xMin) continue;
        if (vx>xMax) continue;
     
        float vy   = vertices[i]->posVec.y;
        if (vy<yMin) continue;
        if (vy>yMax) continue;
       vertices[i]->isSelected =true;
    
    }
}else
{

    for (int i=0;i<vertices.size();i++)
    {
        float vx   = vertices[i]->posVec.x;
        
        if (vx<xMin) continue;
        if (vx>xMax) continue;
        
        float vy   = vertices[i]->posVec.y;
        if (vy<yMin) continue;
        if (vy>yMax) continue;
        vertices[i]->isSelected =false ;
        
    }


}







}

void MeshGenerator::updateRenderer(ProjectionRenderer &projectionRenderer)
{
    projectionRenderer.numIndices =triangles.size()*3;
    
    delete []    projectionRenderer.indices;
      delete []    projectionRenderer.vertices;
    
    projectionRenderer.indices = new unsigned int[ projectionRenderer.numIndices ];
    
    int count =0;
    for (int i=0; i< triangles.size();i++)
    {
        projectionRenderer.indices[count++] =triangles[i]->v1->index;
    projectionRenderer.indices[count++] =triangles[i]->v2->index;
        projectionRenderer.indices[count++] =triangles[i]->v3->index;
    }
    
    
    projectionRenderer.vertices = new float[vertices.size()*5];
    
   count = 0;
    for (int i=0;i<vertices.size();i++)
    {
        projectionRenderer.vertices[count++] = (vertices[i]->posVec.x*2 -1);
        projectionRenderer.vertices[count++] =(vertices[i]->posVec.y*2 -1)*-1;

        projectionRenderer.vertices[count++] =vertices[i]->screenVec.z;

               projectionRenderer.vertices[count++] =vertices[i]->uvVec.x;
           projectionRenderer.vertices[count++] =vertices[i]->uvVec.y;
    }
   // int numV = vertices.size()*5;
    //console() << "float vert["<< numV<<"] = {";
    //for (int i=0;i<numV;i++)
   // {
     //   console() <<projectionRenderer.vertices[i ] <<",";
    //}
    
   
}

void MeshGenerator::save(ProjectionRenderer &projectionRenderer)
{
    projectionRenderer.numIndices =triangles.size()*3;
    
    delete []    projectionRenderer.indices;
    delete []    projectionRenderer.vertices;
    
    projectionRenderer.indices = new unsigned int[ projectionRenderer.numIndices ];
    
    int count =0;
    for (int i=0; i< triangles.size();i++)
    {
        projectionRenderer.indices[count++] =triangles[i]->v1->index;
        projectionRenderer.indices[count++] =triangles[i]->v2->index;
        projectionRenderer.indices[count++] =triangles[i]->v3->index;
    }
    
    
    projectionRenderer.vertices = new float[vertices.size()*5];
    
    count = 0;
    for (int i=0;i<vertices.size();i++)
    {
        projectionRenderer.vertices[count++] = (vertices[i]->posVec.x*2 -1);
        projectionRenderer.vertices[count++] =(vertices[i]->posVec.y*2 -1)*-1;
        
        projectionRenderer.vertices[count++] =vertices[i]->screenVec.z;
        
        projectionRenderer.vertices[count++] =vertices[i]->uvVec.x;
        projectionRenderer.vertices[count++] =vertices[i]->uvVec.y;
    }
    int numV = vertices.size()*5;
     console() << "int numV="<< numV<<";"<<endl ;
    console() << "float vert["<< numV<<"] = {";
    for (int i=0;i<numV;i++)
    {
    console() <<projectionRenderer.vertices[i ] <<",";
    }
    console() <<"};"<<endl<<endl;
    
    int numI =projectionRenderer.numIndices;
    
    console() << "int numI="<< numI<<";"<<endl ;
    console() << "unsigned int ind["<< numI<<"] = {";
    for (int i=0;i<numI;i++)
    {
        console() <<projectionRenderer.indices[i ] <<",";
    }
     console() <<"};"<<endl<<endl;
}
