//
//  MeshGenerator.h
//  basicApp
//
//  Created by Kris Temmerman on 06/10/12.
//
//

#ifndef basicApp_MeshGenerator_h
#define basicApp_MeshGenerator_h

#include "npMesh.h"
#include "ProjectionCamera.h"


#include "cinder/Vector.h"

#include "MeshVertex.h"
#include "MeshTriangle.h"
#include "cinder/params/Params.h"
#include "ColorMeshRenderer.h"
#include "ProjectionRenderer.h"
using namespace cinder;
using namespace ci;
using namespace std;
class MeshGenerator
{
public:
    MeshGenerator()
    {
        shiftDown =false;
     ctrlDown =false;
    };
    void setup();
   void init(npMesh *mesh, ProjectionCamera *cam);
   
    void mouseDown(int x,int y );
 
    void mouseUp(int x,int y);
    
    void mouseMove(int x,int y);
  
    void selectSingle(int x,int y);
   
    void moveSelected(int x,int y);
    void update();
    void draw();
    void selectItems(bool shiftDown);
    params::InterfaceGl		mParams;
    bool singlePoint ;
    void updateRenderer(ProjectionRenderer &projectionRenderer);
    
    vector<MeshVertex * > vertices;
    vector<MeshTriangle * > triangles;
    
    void addPoint(Vec2<float> p,bool sel);
     void addTriangle(MeshTriangle *t);
    
    ColorMeshRenderer renderer;
    vector<Vec2<float> > selectLines;
     vector<Vec2<float> > pointLines;
        vector<Vec2<float> > pointLinesSelected;
    vector<Vec2<float> >    triangleLines;
    Vec2<float> mouseStart;
     Vec2<float> mouseBL;
    Vec2<float> mouseTR;
    Vec2<float> mouseStop;
    bool shiftDown;
    bool ctrlDown;
    float screenH;
    float screenW;
    
    npMesh *mesh;
    
    void save(ProjectionRenderer &projectionRenderer);
};

#endif
