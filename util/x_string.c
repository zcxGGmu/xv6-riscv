#include "x_string.h"

int x_strcmp(const char *a, const char *b)
{
    for (; *a == *b && *a != '\0'; a++, b++)
        ;
    return *a - *b;
}

int x_strncmp(const char *a, const char *b, size_t cnt)
{
    for (; cnt > 0 && *a == *b && *a != '\0'; a++, b++, cnt--)
        ;
    if (!cnt)
        return 0;
    return *a - *b;    
}

size_t x_strlen(const char *str)
{
    unsigned long len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

char *x_strcpy(char *dst, char *src)
{
    char *ret = dst;
    while (*src != '\0') {
        *dst++ = *src++;
    }
    return ret;
}

char *x_strncpy(char *dst, char *src, size_t cnt)
{
    char *ret = dst;
    while (cnt-- && *src != '\0') {
        *dst++ = *src++;
    }
    return ret;
}

char *x_strchr(const char *s, int c);
char *x_strrchr(const char *s, int c);

void *x_memset(void *s, int c, size_t cnt);
void *x_memcpy(void *dst, const void *src, size_t cnt);
void *x_memmove(void *dst, const void *src, size_t cnt);
int x_memcmp(const void *s1, const void *s2, size_t cnt);
void *x_memchr(const void *s, int c, size_t cnt);