
#include "npMesh.h"
void npMesh::resolveModelMatrix()
{
    Quaternion<float> q = Quaternion<float>(objectMatrix);
     normalMatrix = objectMatrix.subMatrix33(0, 0);
    objectMatrix=objectMatrixModel* objectMatrix;
    //objectMatrix = objectMatrixModel;
    
    q.set(normalMatrix);
    //console()<< normalMatrix;
    //normalMatrix.invert();
}

void npMesh::createBuffer()
{
	glGenBuffers(1, &vertexBuffer);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVertices*stride*sizeof(float), vertices,GL_STREAM_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenBuffers(1, &indexBuffer);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  

}
npMesh * npMesh::clone()
{

    npMesh *mesh = new npMesh();
    mesh->objectMatrixModel = objectMatrixModel;
    mesh->vertices  = vertices;
    mesh->indices =indices;
    mesh->numVertices = numVertices;
    mesh->numIndices =numIndices;
    mesh->stride = stride;
    mesh->createBuffer();
    return mesh;
}