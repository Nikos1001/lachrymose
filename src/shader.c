
#include "shader.h"
#include "lms.h"
#include "gl.h"

static unsigned int makeShader(const char* src, GLenum type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        lms_error("%s shader compilation error.\n%s", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", infoLog);
    }
    return shader; 
} 

void lms_initShader(lms_shader* shader, const char* vertSrc, const char* fragSrc) {
    int vertProgram = makeShader(vertSrc, GL_VERTEX_SHADER); 
    int fragProgram = makeShader(fragSrc, GL_FRAGMENT_SHADER); 

    shader->program = glCreateProgram();
    glAttachShader(shader->program, vertProgram);
    glAttachShader(shader->program, fragProgram);
    glLinkProgram(shader->program);

    int success;
    char infoLog[512];
    glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader->program, 512, NULL, infoLog);
        lms_error("Shader linking error.\n%s", infoLog);
    }
}

void lms_useShader(lms_shader* shader) {
    glUseProgram(shader->program);
}

void lms_unloadShader(lms_shader* shader) {
    glDeleteProgram(shader->program);
}



int lms_uniformLocation(lms_shader* shader, const char* name) {
    lms_useShader(shader);
    int loc = glGetUniformLocation(shader->program, name);    
    if(loc == -1) {
        lms_error("Uniform variable %s does not exist.", name);
    } 
    return loc;
}

void lms_setIntUniform(lms_shader* shader, const char* name, int val) {
    int loc = lms_uniformLocation(shader, name);
    glUniform1i(loc, val);
}

void lms_setMat4Uniform(lms_shader* shader, const char* name, mat4 val) {
    int loc = lms_uniformLocation(shader, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (float*)val);
}
