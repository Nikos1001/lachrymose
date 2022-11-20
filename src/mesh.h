
#ifndef LMS_MESH_H
#define LMS_MESH_H

typedef struct {
    int dimension;
    int offset;
} lms_meshAttrib;

typedef struct {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    float* vertData;
    int verts;
    int nAttribs; 
    lms_meshAttrib attribs[16];
    int floatsPerVert;
    int* triData;
    int tris; 
} lms_mesh;

void lms_initMesh(lms_mesh* mesh, int attribs, int* attribDims); 
void lms_uploadMesh(lms_mesh* mesh);
void lms_renderMesh(lms_mesh* mesh);
void lms_unloadMesh(lms_mesh* mesh);

float* lms_meshVertPointer(lms_mesh* mesh, int vert, int attrib);
void lms_set2DVertData(lms_mesh* mesh, int vert, int attrib, float x, float y);
void lms_set3DVertData(lms_mesh* mesh, int vert, int attrib, float x, float y, float z);

int* lms_meshTriPointer(lms_mesh* mesh, int tri);
void lms_setTriangle(lms_mesh* mesh, int tri, int v0, int v1, int v2);

#endif
