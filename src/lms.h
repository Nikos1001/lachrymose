
#ifndef LMS_LMS_H
#define LMS_LMS_H

#include "llu.h"

extern void (*lms_errorCallback)(const char*);
void lms_error(const char* fmt, ...);

extern void* (*lms_realloc)(void* ptr, size_t oldSize, size_t newSize);
void* lms_malloc(size_t size);
#define lms_alloc(type) ((type*)lms_malloc(sizeof(type)))
#define lms_arrAlloc(type, cnt) ((type*)lms_malloc((cnt) * sizeof(type)))
void lms_free(void* ptr, size_t size);
#define lms_freeAlloc(alloc, type) lms_free(alloc, sizeof(type))
#define lms_freeArrAlloc(alloc, type, cnt) lms_free(alloc, (cnt) * sizeof(type))

void lms_init();

#endif
