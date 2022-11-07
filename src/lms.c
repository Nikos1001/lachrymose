
#include "lms.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "gl.h"
#include "window.h"

void lms_init() {
    glewExperimental = true;
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    lms_openWindows = NULL;
}

#include <stdio.h>

static void defaultErrorCallback(const char* msg) {
    fprintf(stderr, "\e[31m%s\n", msg);
    exit(-1);
}

void (*lms_errorCallback)(const char*) = defaultErrorCallback;

void lms_error(const char* fmt, ...) {
    char buff[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buff, 1024, fmt, args);
    va_end(args);
    lms_errorCallback(buff);
}

static void* defaultRealloc(void* ptr, size_t oldSize, size_t newSize) {
    return realloc(ptr, newSize);
}



void* (*lms_realloc)(void* ptr, size_t oldSize, size_t newSize) = defaultRealloc;

void* lms_malloc(size_t size) {
    return lms_realloc(NULL, 0, size);
}

void lms_free(void* ptr, size_t size) {
    lms_realloc(ptr, size, 0);
}
