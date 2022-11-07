
#ifndef LMS_FRAMEBUFFER_H
#define LMS_FRAMEBUFFER_H

#include "texture.h"
#include "window.h"

typedef enum {
    LMS_COLOR_ATTACHMENT,
    LMS_DEPTH_STENCIL_ATTACHMENT
} lms_framebufferAttachmentType;

typedef struct {
    lms_texture tex;
} lms_framebufferAttachment;

typedef struct {
    unsigned int fbo;
    int nAttachments;
    lms_framebufferAttachment attachments[16];
    int w, h;
} lms_framebuffer;

void lms_initFramebuffer(lms_framebuffer* fb, int w, int h, int attachments, lms_framebufferAttachmentType* attachmentTypes);
void lms_unloadFramebuffer(lms_framebuffer* fb);
lms_texture* lms_getFramebufferAttachment(lms_framebuffer* fb, int attachment);

void lms_renderToFramebuffer(lms_framebuffer* fb);
void lms_renderToWindow(lms_window* win);

void lms_resizeFramebuffer(lms_framebuffer* fb, int w, int h);
void lms_resizeFramebufferToWindow(lms_framebuffer* fb, lms_window* win);

#endif
