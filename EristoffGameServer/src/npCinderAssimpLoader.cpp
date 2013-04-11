
#include "npCinderAssimpLoader.h"
#include "aiConfig.h"
#include "aiPostProcess.h"


void npCinderAssimpLoader::load(string fileName)
{
	//console() << "loading:" << fileName << endl;
    unsigned int flags = aiProcess_FlipUVs  | aiProcess_Triangulate ;// aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_FlipUVs ;// | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ImproveCacheLocality | aiProcess_OptimizeGraph |aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices |
		//	aiProcess_RemoveRedundantMaterials|aiProcess_CalcTangentSpace ;
	
    scene = aiImportFile(fileName.c_str(), flags);
  
    
	if(scene)
	{
       //console() << "load "<<fileName <<" "<< aiGetErrorString();
			processScene();
	
	}else
	{
		console() << "didn't load "<<fileName <<" "<< aiGetErrorString();
	
	}

}

void npCinderAssimpLoader::parseNode(aiNode *node)
{
      string name("");
    name.insert(0, node->mName.data, node->mName.length);
   // console()<<scene->mNumMeshes << " name: " << name<<endl;

    
    
    for (unsigned int j = 0; j < node->mNumMeshes; ++j)
    {
        makeMesh(scene->mMeshes[node->mMeshes[node->mNumMeshes-1]], name,node->mTransformation);
    }
    
    
    
    for (unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        
        
        parseNode(node->mChildren[i]);
        
        /*
        string name("");
        name.insert(0, node->name.data, scene->mRootNode->mChildren[i]->mName.length);
        console() << "name: " << name<<endl;
        */
        
        /*if (scene->mRootNode->mChildren[i]->mNumMeshes>0)
        {
            for (unsigned int j = 0; j < scene->mRootNode->mChildren[i]->mNumMeshes; ++j)
            {
                makeMesh(scene->mMeshes[scene->mRootNode->mChildren[i]->mMeshes[scene->mRootNode->mChildren[i]->mNumMeshes-1]], name,scene->mRootNode->mChildren[i]->mTransformation);
            }
        }*/
        
    }


}
void npCinderAssimpLoader::processScene()
{
   // console()<< scene->HasAnimations()<<"?"<< endl;
    parseNode( scene->mRootNode);
    
    return;
       
    
	/*for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		
		aiMesh* mesh = scene->mMeshes[i];
        string name("");
        name.insert(0, mesh->mName.data, mesh->mName.length);

			console() << "implement bones "<< name<<endl;
		if (mesh->HasBones())
		{	 

			console() << "implement bones "<<endl;
				// makeBoneMesh(mesh); 
				// getAnime();
		}
		else
		{ 
			//makeMesh( mesh );
		}

	}*/
}

	
void  npCinderAssimpLoader::makeMesh(aiMesh *mesh, string name,aiMatrix4x4 	&mTransformation)
{

	npMesh * npmesh = new npMesh();

    
    npmesh->name = name;
	aiQuaternion	rotation;
    aiVector3D 	position ;
    aiVector3D scaling;
    //mTransformation.DecomposeNoScaling(rotation,position);
  mTransformation.Decompose(scaling, rotation, 	position );
    aiMatrix3x3  rotMatrix = rotation.GetMatrix();
   aiMatrix3x3  nMatrix = rotMatrix.Inverse();
      //console() <<endl<<"mesh "<< name << rotation.x<< rotation.y<< rotation.z  << " "<< position.x << " "<< position.y <<" "<< position.z << scaling.x << " "<< scaling.y <<" "<< scaling.z<<endl ;
    if (!blender)
    {
        npmesh->objectMatrixModel.translate(Vec3<float>(-position.x/100,-position.y/100,position.z/100));
        npmesh->basePos =Vec3<float>(-position.x/10,-position.y/10,position.z/10);
    }else
    {
    
     npmesh->objectMatrixModel.translate(Vec3<float>(-position.x,-position.y,position.z));
         npmesh->basePos =Vec3<float>(-position.x,-position.y,position.z);
    }
 //  console()<< name << endl<< npmesh->objectMatrix<<" "<<endl  << position.x <<" " << position.y<<" " << position.z<< endl ;
    
	meshes.push_back( npmesh );
	npmesh->stride = 3;
	bool hasNormals  =true;
	if(!mesh->HasNormals() )
	{
		hasNormals  =false;
		//console() << "warning: missing normals in mesh" <<endl;

	}
	bool hasTextureCoords =true;
	if (!mesh->HasTextureCoords(0))
	{
		hasTextureCoords  =false;
		//console()<<endl << "warning: missing textcords in mesh :" << name <<endl;
		
	}
		bool hasTangents =true;
	if (!mesh->HasTangentsAndBitangents())
	{
		hasTangents =false;
	//	console() << "warning: missing tangents in mesh" <<endl;
		
	}
	
	npmesh->numVertices = mesh->mNumVertices;
	npmesh->stride = 3+3+2;
	npmesh->vertices =new float[npmesh->numVertices*npmesh->stride ];

	float x ;
	float y ;
	float z ;

	float xMin =100000 ;
	float yMin =100000 ;
	float zMin	=100000 ;

	float xMax=-100000 ;
	float yMax=-100000 ;
	float zMax=-100000 ;
    preMatrixNormal =preMatrix;
    preMatrixNormal.invert();

	int count =0;
	for (int i=0;i<mesh->mNumVertices;i++)
	{
        aiVector3D Rpos = nMatrix*mesh->mVertices[i];
        Vec4<float> f( Rpos.x, Rpos.y, Rpos.z,1);
        //Vec4<float> f(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z,1);
        
        Vec4<float> r =   preMatrix.postMultiply(f);
        if (blender)
        {
            r = f;
        }
        
        
        
        
		x = r.x;//mesh->mVertices[i].x;
		y =	r.y;//mesh->mVertices[i].y;
		z = r.z;//mesh->mVertices[i].z ;

		if (x <xMin) xMin =x;
		if (y <yMin) yMin =y;
		if (z <zMin) zMin =z;

		if (x >xMax) xMax =x;
		if (y >yMax) yMax =y;
		if (z >zMax) zMax =z;

		npmesh->vertices[count++] = -x ;
		npmesh->vertices[count++] = z ;
		npmesh->vertices[count++] = y ;
		if (hasNormals)
		{
            
           aiVector3D n =  nMatrix*mesh->mNormals[i];
            Vec4<float> f(n.x,n.y,n.z,1);
            
            //Vec4<float> r =   preMatrixNormal.postMultiply(f);
            

			npmesh->vertices[count++] = -f.x;
			npmesh->vertices[count++] = f.z;
			npmesh->vertices[count++] =f.y;

			
		}else
		{
			count+=3;
		}

		if (hasTangents)
		{
			//npmesh->vertices[count++] = mesh->mTangents[i].x;
			//npmesh->vertices[count++] = mesh->mTangents[i].y;
			//npmesh->vertices[count++] = mesh->mTangents[i].z;

			
		}else
		{
		//	count+=3;
		}
	

		if (hasTextureCoords)
		{
			npmesh->vertices[count++] = mesh->mTextureCoords[0][i].x;
			npmesh->vertices[count++] = mesh->mTextureCoords[0][i].y;
		}
		else
		{
				npmesh->vertices[count++] = 0;
			npmesh->vertices[count++] =0 ;
		}

	

		
	}
		
	npmesh->xMin =xMin;
	npmesh->yMin =yMin;
	npmesh->zMin =zMin;

	npmesh->xMax =xMax;
	npmesh->yMax =yMax;
	npmesh->zMax =zMax;
	//console()<<endl<<"mesh "<< name<< "meshSize w:" << (xMax-xMin)<<" h:" << (yMax-yMin) << endl;
	npmesh->numIndices = mesh->mNumFaces*3;
	npmesh->indices =new unsigned[npmesh->numIndices];

	count =0;
	for (int i=0;i< mesh->mNumFaces;i++)
	{
			for (unsigned int a = 0; a < 3; ++a){
				npmesh->indices[count++]=mesh->mFaces[i].mIndices[a];
			}
	}
	npmesh->createBuffer();

	
}


npMesh*  npCinderAssimpLoader::getMeshByName(const string &name)
{

    for(int i=0;i<meshes.size();i++)
    {
    
        if ( meshes[i]->name.find(name)== 0) return   meshes[i];  
    
    }



    return NULL;


}