
#include "framebuffer.h"
#include "gl.h"
#include "lms.h"

void lms_initFramebuffer(lms_framebuffer* fb, int w, int h, int attachments, lms_framebufferAttachmentType* attachmentTypes) {
    fb->w = w;
    fb->h = h;
    glGenFramebuffers(1, &fb->fbo); 
    glBindFramebuffer(GL_FRAMEBUFFER, fb->fbo);
    fb->nAttachments = attachments;
    for(int i = 0; i < attachments; i++) {
        lms_initTexture(&fb->attachments[i].tex);
        lms_filtering(&fb->attachments[i].tex, false);
        fb->attachments[i].tex.w = w;
        fb->attachments[i].tex.h = h;
        GLenum attachment;
        switch(attachmentTypes[i]) {
            case LMS_COLOR_ATTACHMENT: {
                fb->attachments[i].tex.format = LMS_FORMAT_RGBA;
                attachment = GL_COLOR_ATTACHMENT0 + i;
                break;
            }
            case LMS_DEPTH_STENCIL_ATTACHMENT: {
                fb->attachments[i].tex.format = LMS_FORMAT_DEPTH_STENCIL;
                attachment = GL_DEPTH_STENCIL_ATTACHMENT;
                break;
            }
        }
        fb->attachments[i].tex.data = NULL;
        lms_uploadTexture(&fb->attachments[i].tex);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, fb->attachments[i].tex.texture, 0);
    }

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        lms_error("Framebuffer incomplete."); 
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void lms_unloadFramebuffer(lms_framebuffer* fb) {
    for(int i = 0; i < fb->nAttachments; i++) {
        lms_unloadTexture(&fb->attachments[i].tex);
    }
    glDeleteFramebuffers(1, &fb->fbo);
}

lms_texture* lms_getFramebufferAttachment(lms_framebuffer* fb, int attachment) {
    return &fb->attachments[attachment].tex;
}

void lms_renderToFramebuffer(lms_framebuffer* fb) {
    glViewport(0, 0, fb->w, fb->h);
    glBindFramebuffer(GL_FRAMEBUFFER, fb->fbo);
}

void lms_renderToWindow(lms_window* win) {
    lms_windowSize size = lms_getViewportSize(win);
    glViewport(0, 0, size.w, size.h);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void lms_resizeFramebuffer(lms_framebuffer* fb, int w, int h) {
    fb->w = w;
    fb->h = h;
    for(int i = 0; i < fb->nAttachments; i++) {
        fb->attachments[i].tex.w = w;
        fb->attachments[i].tex.h = h;
        lms_uploadTexture(&fb->attachments[i].tex);
    }
}

void lms_resizeFramebufferToWindow(lms_framebuffer* fb, lms_window* win) {
    lms_windowSize size = lms_getViewportSize(win);
    if(size.w != fb->w || size.h != fb->h) {
        lms_resizeFramebuffer(fb, size.w, size.h);
    }
}

