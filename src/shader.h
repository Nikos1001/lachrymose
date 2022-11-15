
#ifndef LMS_SHADER_H
#define LMS_SHADER_H

#include "llu.h"
#include "gl.h"

typedef struct {
    unsigned int program;
} lms_shader;

void lms_initShader(lms_shader* shader, const char* vertSrc, const char* fragSrc);
void lms_useShader(lms_shader* shader);
void lms_unloadShader(lms_shader* shader);

int lms_uniformLocation(lms_shader* shader, const char* name);
void lms_setIntUniform(lms_shader* shader, const char* name, int val);
void lms_setFloatUniform(lms_shader* shader, const char* name, float val);
void lms_setVec2Uniform(lms_shader* shader, const char* name, vec2 val);
void lms_setVec3Uniform(lms_shader* shader, const char* name, vec3 val);
void lms_setMat4Uniform(lms_shader* shader, const char* name, mat4 val);

#endif
