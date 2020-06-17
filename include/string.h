#ifndef STRING_H
#define STRING_H

#include "def.h"


void * memcpy(void *dst, void *src, size_t n);

int8_t * memset(int8_t *dst, int8_t value, size_t n);

char * itoa(unsigned int num, char *str);

int strcmp(const char * str1, const char * str2);

uint32_t strlen(const char * str);

#endif