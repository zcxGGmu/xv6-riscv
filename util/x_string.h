#ifndef __X_STRING_H__
#define __X_STRING_H__

#include "x_types.h"

int x_strcmp(const char *a, const char *b);
int x_strncmp(const char *a, const char *b, size_t cnt);

size_t x_strlen(const char *str);
//size_t x_strnlen(const char *str, size_t cnt);

char *x_strcpy(char *dst, char *src);
char *x_strncpy(char *dst, char *src, size_t cnt);

char *x_strchr(const char *s, int c);
char *x_strrchr(const char *s, int c);

void *x_memset(void *s, int c, size_t cnt);
void *x_memcpy(void *dst, const void *src, size_t cnt);
void *x_memmove(void *dst, const void *src, size_t cnt);
int x_memcmp(const void *s1, const void *s2, size_t cnt);
void *x_memchr(const void *s, int c, size_t cnt);

#endif