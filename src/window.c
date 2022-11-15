
#include "window.h"
#include "gl.h"
#include "lms.h"

lms_window* lms_openWindows = NULL;

lms_window* lms_makeWindow() {
    lms_window* win = lms_alloc(lms_window);
    win->win = glfwCreateWindow(1000, 800, "Lacrymose", NULL, lms_openWindows == NULL ? NULL : lms_openWindows->win);
    glfwMakeContextCurrent(win->win);
    glewInit();
    win->nextWin = lms_openWindows;
    lms_openWindows = win;
    return win;
}

bool lms_windowOpen(lms_window* win) {
    return !glfwWindowShouldClose(win->win);
}

bool lms_allWindowsOpen() {
    for(lms_window* win = lms_openWindows; win != NULL; win = win->nextWin)
        if(!lms_windowOpen(win))
            return false;
    return true;
}

lms_windowSize lms_getWindowSize(lms_window* win) {
    lms_windowSize size;
    glfwGetWindowSize(win->win, &size.w, &size.h);
    return size;
}

lms_windowSize lms_getViewportSize(lms_window* win) {
    lms_windowSize size = lms_getWindowSize(win);
    float xScale, yScale;
    glfwGetWindowContentScale(win->win, &xScale, &yScale);
    size.w = (float)size.w * xScale;
    size.h = (float)size.h * xScale;
    return size;
}

void lms_windowTitle(lms_window* win, const char* title) {
    glfwSetWindowTitle(win->win, title);
}
