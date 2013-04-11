#include "DestructibleBlock.h"

void DestructibleBlock::setup(float posX,float posY,float w, float h,float d, int subW, int subH)
{

	float sizeW = w/subW;
	float sizeH =h/subH;
	numCubes =  (subH-1)*(subW-1);
	numIndices  = numCubes*6*6;
	indices = new unsigned int[numIndices];


	int indexCount =0; 
	int indexPosCount =0; 
	for (int i=0 ;i< numCubes*6;i++)
	{
		indices[indexCount++] = indexPosCount;
		indices[indexCount++] =indexPosCount+1;
		indices[indexCount++] =indexPosCount+2;

		indices[indexCount++] =indexPosCount;
		indices[indexCount++] =indexPosCount+2;
		indices[indexCount++] =indexPosCount+3;
		indexPosCount+=4;
	}

	stride  =3;
	numVertices =numCubes* 4*6 ;
	vertices = new float [numVertices*stride];

	

	int startCount = 0;
	for (int y =0; y<subH-1;y++)
	{
		for (int x =0; x<subW-1;x++)
		{
			DeformCube *cube =new DeformCube();
			float offset  =0;
			if (y%2==0)offset =sizeH/2;
			cube->setup(posX +sizeW*x+offset,posY +sizeH*y ,sizeW-5,sizeH-5,d);
			cube->getVertices(vertices,  startCount );
			 startCount += stride*4*6;
			cubes.push_back(cube);
		}
	}
	/*int count =0;
	int blockCount =0;
	for (int i=0;i< numVertices;i++)
	{
		console() << vertices[i] << " "; 
		count ++;
		if (count ==  4*6 )
		{
			console()  << endl << endl; 
		count =0;
		 blockCount++;
		}
	}
		console() <<"blockCOunt:" << blockCount << endl; */
	createBuffer();
}
void DestructibleBlock::createBuffer()
{
	glGenBuffers(1, &vertexBuffer);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVertices*stride*sizeof(float), vertices,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenBuffers(1, &indexBuffer);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  

}
