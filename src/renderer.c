
#include "renderer.h"
#include "gl.h"

float lms_dt = 0.0f;

static float frameStartTime;

void lms_beginFrame() {
    glEnable(GL_DEPTH_TEST);
    frameStartTime = glfwGetTime();
}

void lms_endFrame() {
    for(lms_window* win = lms_openWindows; win != NULL; win = win->nextWin) {
        glfwSwapBuffers(win->win);
    }
    glfwPollEvents();
    lms_dt = glfwGetTime() - frameStartTime;
}

void lms_beginWindowFrame(lms_window* win) {
    glfwMakeContextCurrent(win->win);
}

void lms_clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void lms_blend(lms_blendMode mode) {
    switch(mode) {
        case LMS_BLEND_NONE: {
            glDisable(GL_BLEND);
            break;
        }
        case LMS_BLEND_ADD: {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            break;
        }
    }
}

void lms_depthTest(bool test) {
    if(test)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}
