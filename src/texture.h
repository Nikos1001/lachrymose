
#ifndef LMS_TEXTURE_H
#define LMS_TEXTURE_H

#include <stdbool.h>

typedef enum {
    LMS_FORMAT_RGB,
    LMS_FORMAT_RGBA,
    LMS_FORMAT_FLOAT_RGBA,
    LMS_FORMAT_FLOAT16_RGBA,
    LMS_FORMAT_DEPTH_STENCIL
} lms_textureFormat;

typedef struct {
    unsigned int texture;
    int w, h;
    lms_textureFormat format;
    unsigned char* data;
} lms_texture;

void lms_initTexture(lms_texture* tex);
void lms_uploadTexture(lms_texture* tex);
void lms_unloadTexture(lms_texture* tex);
void lms_useTexture(lms_texture* tex, int slot);

typedef enum {
    LMS_FILTER_POINT,
    LMS_FILTER_LINEAR,
    LMS_FILTER_LINEAR_NO_MIPMAP
} lms_filterType;
void lms_filtering(lms_texture* tex, lms_filterType filter);

#endif
