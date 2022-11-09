
#include "renderer.h"
#include "gl.h"

void lms_beginFrame() {
    glEnable(GL_DEPTH_TEST);
}

void lms_endFrame() {
    for(lms_window* win = lms_openWindows; win != NULL; win = win->nextWin) {
        glfwSwapBuffers(win->win);
    }
    glfwPollEvents();
}

void lms_beginWindowFrame(lms_window* win) {
    glfwMakeContextCurrent(win->win);
}

void lms_clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}