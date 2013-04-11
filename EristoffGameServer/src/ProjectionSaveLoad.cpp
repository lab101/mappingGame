//
//  ProjectionSaveLoad.cpp
//  basicApp
//
//  Created by Kris Temmerman on 22/10/12.
//
//

#include "ProjectionSaveLoad.h"
#include "MeshVertex.h"
#include "MeshTriangle.h"
void ProjectionSaveLoad::load(string path, MeshGenerator &meshGenerator,ProjectionCamera &cam)
{
    
    ifstream loadFile;
    
    loadFile.open (path.c_str(), ifstream::in);
    
   
    meshGenerator.triangles.clear();
    meshGenerator.vertices.clear();
        int count =0;
    while (loadFile.good()){
        
        char linedata[512];
       
        loadFile.getline(linedata,512);
        
    
        
        if (linedata[0] =='v')
        {
            
            
            vector<string> output;
            split(output, linedata, is_any_of(" "));
         
            MeshVertex *vertex =new MeshVertex();
            vertex->index = count++;
           
            vertex->posVec.x =lexical_cast<float> (output[1]) ;
            vertex->posVec.y =lexical_cast<float> (output[2]) ;
            vertex->screenVec.z =lexical_cast<float> (output[3]);
            
            vertex->uvVec.x =lexical_cast<float> (output[4] );
            vertex->uvVec.y = lexical_cast<float> (output[5]);
            //  console()<<vertex->uvVec <<endl;
            meshGenerator.vertices.push_back(vertex);
            continue;
        }
        else if (linedata[0] =='t')
        {
            vector<string> output;
            split(output, linedata, is_any_of(" "));
            int i1 =lexical_cast<int> (output[1]) ;
            int i2 =lexical_cast<int> (output[2]) ;
            int i3 =lexical_cast<int> (output[3]) ;
            
            MeshTriangle *t = new MeshTriangle();
            t->v1 =  meshGenerator.vertices[i1];
            t->v2 =  meshGenerator.vertices[i2];
            t->v3 =  meshGenerator.vertices[i3];
            meshGenerator.triangles.push_back(t);
            
            continue;
        }
        else if (linedata[0] =='c')
        {
            vector<string> output;
            split(output, linedata, is_any_of(" "));
            
            
            cam.globalX =lexical_cast<float>( output[1]);
            cam.globalY =lexical_cast<float> (output[2]);
            cam.globalScale =lexical_cast<float> (output[3]);
            
            continue;
        }
        else 
        {
            
            continue;
        }
        
        
        /*  cout << "cfirst = "<<linedata[0]<<endl;
         cout << "f:" << linedata[0]<<endl;
         string linestring;
         stringstream ss;
         ss << linedata;
         ss >> linestring;
         cout << "d:" << linestring<<" "<<linestring.size()<<endl;
         //boost::split(output, linestring, boost::is_any_of(' '));*/
    }


}
void ProjectionSaveLoad::load(MeshGenerator &meshGenerator,ProjectionCamera &cam)
{
    fs::path p= getOpenFilePath();
    //fs::path pl =getSaveFilePath("test.xml");
    
    
    load(p.string(),meshGenerator,cam);
      
   

}
void ProjectionSaveLoad::save(const MeshGenerator &meshGenerator,ProjectionCamera &cam)
{
    string phome = getHomeDirectory().string()+"Desktop/";//;<<endl;
    fs::path pl =getSaveFilePath(phome);
    ofstream saveFile (pl.c_str());
 
    const vector<MeshVertex * >   vertices =meshGenerator.vertices;
    const vector<MeshTriangle * > triangles=meshGenerator.triangles;
    saveFile <<"c "<< cam.globalX<<" "<< cam.globalY<<" "<< cam.globalScale<<"\n";
    
    for (int i=0;i<vertices.size();i++)
    {
        saveFile <<"v "<< (vertices[i]->posVec.x)<<" ";
        saveFile <<(vertices[i]->posVec.y)<<" ";
        
        saveFile <<vertices[i]->screenVec.z<<" ";
        
        saveFile <<vertices[i]->uvVec.x<<" ";
        saveFile <<vertices[i]->uvVec.y<<"\n";
        
    }
    
    
    for (int i=0; i< triangles.size();i++)
    {
        
         saveFile <<"t "<< triangles[i]->v1->index <<" "<< triangles[i]->v2->index << " " <<triangles[i]->v3->index<< "\n";
        

    }

    
    saveFile.close();
}