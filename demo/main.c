
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* vertShader = "#version 330 core\n" llu_stringify(

    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aUv;

    uniform mat4 uTrans;

    out vec2 pUv;

    void main() {
        gl_Position = uTrans * vec4(aPos, 1.0f);
        pUv = aUv;
    }

); 

const char* fragShader = "#version 330 core\n" llu_stringify(

    in vec2 pUv;

    uniform sampler2D uTex;

    out vec4 oFragColor;

    void main() {
        oFragColor = texture(uTex, pUv);
    }

);

const char* postProcVertShader = "#version 330 core\n" llu_stringify(

    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aUv;

    out vec2 pUv;

    void main() {
        gl_Position = vec4(aUv * 2 - 1, 0.0f, 1.0f);
        pUv = aUv;
    }

); 

const char* postProcFragShader = "#version 330 core\n" llu_stringify(

    in vec2 pUv;

    uniform sampler2D uTex;

    out vec4 oFragColor;

    void main() {
        oFragColor = 1 - texture(uTex, pUv);
    }

);

int main() {
    lms_init();
    lms_window* win = lms_makeWindow();

    lms_shader shader;
    lms_initShader(&shader, vertShader, fragShader);
    lms_shader postProcShader;
    lms_initShader(&postProcShader, postProcVertShader, postProcFragShader);

    lms_mesh quad;
    lms_initMesh(&quad, 2, (int[]){3, 2});

    lms_framebuffer fb;
    lms_initFramebuffer(&fb, 320, 256, 2, (lms_framebufferAttachmentType[]){LMS_COLOR_ATTACHMENT, LMS_DEPTH_STENCIL_ATTACHMENT});

    quad.verts = 4;
    quad.tris = 2;

    float vertData[4 * quad.floatsPerVert];
    int triData[2 * 3];
    quad.vertData = vertData; 
    quad.triData = triData; 

    lms_texture tex;
    lms_initTexture(&tex);
    stbi_set_flip_vertically_on_load(true);
    int channels;
    tex.data = stbi_load("res/test.jpeg", &tex.w, &tex.h, &channels, 0);
    if(tex.data != NULL) {
        tex.format = channels == 3 ? LMS_FORMAT_RGB : LMS_FORMAT_RGBA;
        lms_uploadTexture(&tex);
        stbi_image_free(tex.data);
    } else {
        printf("Could not load texture.\n");
    }

    lms_set3DVertData(&quad, 0, 0,  0.5f,  0.5f, 0.0f);
    lms_set2DVertData(&quad, 0, 1,  1.0f,  1.0f);

    lms_set3DVertData(&quad, 1, 0, -0.5f,  0.5f, 0.0f);
    lms_set2DVertData(&quad, 1, 1,  0.0f,  1.0f);

    lms_set3DVertData(&quad, 2, 0,  0.5f, -0.5f, 0.0f);
    lms_set2DVertData(&quad, 2, 1,  1.0f,  0.0f);

    lms_set3DVertData(&quad, 3, 0, -0.5f, -0.5f, 0.0f);
    lms_set2DVertData(&quad, 3, 1,  0.0f,  0.0f);

    lms_setTriangle(&quad, 0, 0, 1, 2);
    lms_setTriangle(&quad, 1, 1, 2, 3);

    lms_uploadMesh(&quad);

    mat4 projection;
    glm_ortho(-2.5, 2.5, -2, 2, -1, 1, projection);
    lms_setMat4Uniform(&shader, "uTrans", projection);

    lms_setIntUniform(&shader, "uTex", 0);

    lms_filtering(lms_getFramebufferAttachment(&fb, 0), false);

    while(lms_allWindowsOpen()) {
        lms_beginFrame();
        lms_beginWindowFrame(win);

        lms_windowSize winSize = lms_getWindowSize(win);

        lms_renderToFramebuffer(&fb);
        lms_clear();
        float w = (float)winSize.w / 400.0f;
        float h = (float)winSize.h / 400.0f;
        glm_ortho(-w / 2, w / 2, -h / 2, h / 2, -1, 1, projection);
        lms_setMat4Uniform(&shader, "uTrans", projection);
        lms_useShader(&shader);
        lms_useTexture(&tex, 0);
        lms_renderMesh(&quad);

        lms_renderToWindow(win);
        lms_clear();
        lms_useShader(&postProcShader);
        lms_useTexture(lms_getFramebufferAttachment(&fb, 0), 0);
        lms_renderMesh(&quad);

        lms_endFrame();
    }
    
    lms_unloadMesh(&quad);
    lms_unloadShader(&shader);
    lms_unloadShader(&postProcShader);
    lms_unloadTexture(&tex);
    lms_unloadFramebuffer(&fb);
}
