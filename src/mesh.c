
#include "mesh.h"
#include "gl.h"
#include "lms.h"

void lms_initMesh(lms_mesh* mesh, int attribs, int* attribDims) {
    mesh->nAttribs = attribs;
    mesh->floatsPerVert = 0;
    for(int i = 0; i < attribs; i++) {
        mesh->attribs[i].offset = mesh->floatsPerVert;
        mesh->attribs[i].dimension = attribDims[i];
        mesh->floatsPerVert += attribDims[i];
    } 
    mesh->verts = 0;
    mesh->vertData = NULL; 
    mesh->tris = 0;
    mesh->triData = NULL; 

    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);
    glGenBuffers(1, &mesh->vbo);
    glGenBuffers(1, &mesh->ebo);
    lms_uploadMesh(mesh);
    for(int i = 0; i < attribs; i++) {
        glVertexAttribPointer(i, attribDims[i], GL_FLOAT, GL_FALSE, mesh->floatsPerVert * sizeof(float), (void*)(intptr_t)(mesh->attribs[i].offset * sizeof(float)));
        glEnableVertexAttribArray(i);
    }
} 

void lms_uploadMesh(lms_mesh* mesh) {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->verts * mesh->floatsPerVert, mesh->vertData, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mesh->tris * 3, mesh->triData, GL_DYNAMIC_DRAW);
}

void lms_renderMesh(lms_mesh* mesh) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->tris * 3, GL_UNSIGNED_INT, 0);
}

void lms_unloadMesh(lms_mesh* mesh) {
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteBuffers(1, &mesh->ebo);
    glDeleteVertexArrays(1, &mesh->vao);
}

float* lms_meshVertPointer(lms_mesh* mesh, int vert, int attrib) {
    return mesh->vertData + vert * mesh->floatsPerVert + mesh->attribs[attrib].offset;
}

void lms_set2DVertData(lms_mesh* mesh, int vert, int attrib, float x, float y) {
    float* data = lms_meshVertPointer(mesh, vert, attrib);
    data[0] = x;
    data[1] = y;
}

void lms_set3DVertData(lms_mesh* mesh, int vert, int attrib, float x, float y, float z) {
    float* data = lms_meshVertPointer(mesh, vert, attrib);
    data[0] = x;
    data[1] = y;
    data[2] = z;
}

int* lms_meshTriPointer(lms_mesh* mesh, int tri) {
    return mesh->triData + tri * 3;
}

void lms_setTriangle(lms_mesh* mesh, int tri, int v0, int v1, int v2) {
    int* data = lms_meshTriPointer(mesh, tri);
    data[0] = v0;
    data[1] = v1;
    data[2] = v2;
}
