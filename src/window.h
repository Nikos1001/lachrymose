
#ifndef LMS_WINDOW_H
#define LMS_WINDOW_H

#include <stdbool.h>

typedef struct lms_window {
    void* win; 
    struct lms_window* nextWin;
} lms_window;

extern lms_window* lms_openWindows;

lms_window* lms_makeWindow();
bool lms_allWindowsOpen();
bool lms_windowOpen(lms_window* win);

typedef struct {
    int w, h;
} lms_windowSize;

lms_windowSize lms_getWindowSize(lms_window* win);
lms_windowSize lms_getViewportSize(lms_window* win);
void lms_windowTitle(lms_window* win, const char* title);

#endif
