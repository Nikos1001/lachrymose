
#ifndef LMS_RENDERER_H
#define LMS_RENDERER_H

#include "window.h"

void lms_beginFrame();
void lms_beginWindowFrame(lms_window* win);
void lms_endFrame();
void lms_clear();

typedef enum {
    LMS_BLEND_NONE,
    LMS_BLEND_ADD
} lms_blendMode;

void lms_blend(lms_blendMode mode);
void lms_depthTest(bool test);

#endif
