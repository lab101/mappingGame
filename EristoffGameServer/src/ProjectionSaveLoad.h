//
//  ProjectionSaveLoad.h
//  basicApp
//
//  Created by Kris Temmerman on 22/10/12.
//
//

#ifndef basicApp_ProjectionSaveLoad_h
#define basicApp_ProjectionSaveLoad_h

#include "cinder/app/AppBasic.h"
#include "cinder/Filesystem.h"
#include "cinder/Utilities.h"

#include "npCinderAssimpLoader.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MeshGenerator.h"
using namespace ci;
using namespace ci::app;
using namespace boost;
using namespace std;
class ProjectionSaveLoad
{
    public :
    ProjectionSaveLoad(){};
    void load(MeshGenerator &meshGenerator, ProjectionCamera &cam);
    void load(string path,MeshGenerator &meshGenerator, ProjectionCamera &cam);
    void save(const MeshGenerator &meshGenerator, ProjectionCamera &cam);


};

#endif
