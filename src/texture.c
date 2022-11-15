
#include "texture.h"
#include "gl.h"

void lms_initTexture(lms_texture* tex) {
    glGenTextures(1, &tex->texture);
    glBindTexture(GL_TEXTURE_2D, tex->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void lms_uploadTexture(lms_texture* tex) {
    GLenum internalFormat, format, type;
    switch(tex->format) {
        case LMS_FORMAT_RGB: {
            internalFormat = GL_RGB;
            format = GL_RGB;
            type = GL_UNSIGNED_BYTE;
            break;
        }
        case LMS_FORMAT_RGBA: {
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            break;
        }
        case LMS_FORMAT_FLOAT_RGBA: {
            internalFormat = GL_R11F_G11F_B10F;
            format = GL_RGBA;
            type = GL_FLOAT;
            break;
        }
        case LMS_FORMAT_FLOAT16_RGBA: {
            internalFormat = GL_RGBA16F;
            format = GL_RGBA;
            type = GL_FLOAT;
            break;
        }
        case LMS_FORMAT_DEPTH_STENCIL: {
            internalFormat = GL_DEPTH24_STENCIL8;
            format = GL_DEPTH_STENCIL;
            type = GL_UNSIGNED_INT_24_8;
        }
    } 
    glBindTexture(GL_TEXTURE_2D, tex->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tex->w, tex->h, 0, format, type, tex->data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void lms_unloadTexture(lms_texture* tex) {
    glDeleteTextures(1, &tex->texture);
}

void lms_useTexture(lms_texture* tex, int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, tex->texture);
}

void lms_filtering(lms_texture* tex, lms_filterType filter) {
    glBindTexture(GL_TEXTURE_2D, tex->texture);
    GLenum minFilter, magFilter;
    switch(filter) {
        case LMS_FILTER_POINT: {
            minFilter = GL_NEAREST;
            magFilter = GL_NEAREST;
            break;
        }
        case LMS_FILTER_LINEAR: {
            minFilter = GL_LINEAR_MIPMAP_LINEAR;
            magFilter = GL_LINEAR;
            break;
        }
        case LMS_FILTER_LINEAR_NO_MIPMAP: {
            minFilter = GL_LINEAR;
            magFilter = GL_LINEAR;
            break;
        }
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}
