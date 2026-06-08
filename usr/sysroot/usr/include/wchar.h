#ifndef _WCHAR_H
#define _WCHAR_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#ifndef WCHAR_MIN
#define WCHAR_MIN 0
#endif
#ifndef WCHAR_MAX
#define WCHAR_MAX 0x7FFFFFFF
#endif
#ifndef WEOF
#define WEOF ((wint_t)-1)
#endif

typedef unsigned int wint_t;
typedef struct { int __state; } mbstate_t;

static inline int wcwidth(wchar_t wc) {
    if (wc == 0) return 0;
    return 1;
}

static inline size_t mbrtowc(wchar_t *pwc, const char *s, size_t n, mbstate_t *ps) {
    (void)ps;
    if (!s || n == 0) return 0;
    if (pwc) *pwc = (wchar_t)(unsigned char)*s;
    return *s ? 1 : 0;
}

static inline size_t wcrtomb(char *s, wchar_t wc, mbstate_t *ps) {
    (void)ps;
    if (s) { *s = (char)(wc & 0x7F); return 1; }
    return 1;
}

static inline size_t mbsrtowcs(wchar_t *dst, const char **src, size_t len, mbstate_t *ps) {
    (void)ps;
    if (!src || !*src) return 0;
    size_t i = 0;
    while (i < len && (*src)[i]) {
        if (dst) dst[i] = (wchar_t)(unsigned char)(*src)[i];
        i++;
    }
    if (dst && i < len) dst[i] = 0;
    if ((*src)[i] == 0) *src = NULL;
    return i;
}

static inline size_t wcsrtombs(char *dst, const wchar_t **src, size_t len, mbstate_t *ps) {
    (void)ps;
    if (!src || !*src) return 0;
    size_t i = 0;
    while (i < len && (*src)[i]) {
        if (dst) dst[i] = (char)((*src)[i] & 0x7F);
        i++;
    }
    if (dst && i < len) dst[i] = 0;
    if ((*src)[i] == 0) *src = NULL;
    return i;
}

static inline size_t wcslen(const wchar_t *s) {
    size_t n = 0;
    while (s[n]) n++;
    return n;
}

static inline wchar_t *wcscpy(wchar_t *dst, const wchar_t *src) {
    wchar_t *d = dst;
    while ((*d++ = *src++));
    return dst;
}

static inline wchar_t *wcsncpy(wchar_t *dst, const wchar_t *src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i]; i++) dst[i] = src[i];
    for (; i < n; i++) dst[i] = 0;
    return dst;
}

static inline int wcscmp(const wchar_t *a, const wchar_t *b) {
    while (*a && *a == *b) { a++; b++; }
    return (int)*a - (int)*b;
}

static inline int wcsncmp(const wchar_t *a, const wchar_t *b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i]) return (int)a[i] - (int)b[i];
        if (!a[i]) break;
    }
    return 0;
}

static inline wchar_t *wcschr(const wchar_t *s, wchar_t c) {
    while (*s) { if (*s == c) return (wchar_t*)s; s++; }
    return c ? NULL : (wchar_t*)s;
}

static inline wchar_t *wcsrchr(const wchar_t *s, wchar_t c) {
    const wchar_t *last = NULL;
    while (*s) { if (*s == c) last = s; s++; }
    if (c == 0) return (wchar_t*)s;
    return (wchar_t*)last;
}

static inline wchar_t *wcscat(wchar_t *dst, const wchar_t *src) {
    wcscpy(dst + wcslen(dst), src);
    return dst;
}

static inline wchar_t *wmemcpy(wchar_t *d, const wchar_t *s, size_t n) {
    for (size_t i = 0; i < n; i++) d[i] = s[i];
    return d;
}

static inline wchar_t *wmemmove(wchar_t *d, const wchar_t *s, size_t n) {
    if (d < s) { for (size_t i = 0; i < n; i++) d[i] = s[i]; }
    else { for (size_t i = n; i > 0; i--) d[i-1] = s[i-1]; }
    return d;
}

static inline int wmemcmp(const wchar_t *a, const wchar_t *b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    }
    return 0;
}

static inline wchar_t *wmemchr(const wchar_t *s, wchar_t c, size_t n) {
    for (size_t i = 0; i < n; i++) if (s[i] == c) return (wchar_t*)&s[i];
    return NULL;
}

static inline wchar_t *wmemset(wchar_t *s, wchar_t c, size_t n) {
    for (size_t i = 0; i < n; i++) s[i] = c;
    return s;
}

static inline int mbtowc(wchar_t *pwc, const char *s, size_t n) {
    if (!s) return 0;
    if (n == 0) return -1;
    if (pwc) *pwc = (wchar_t)(unsigned char)*s;
    return *s ? 1 : 0;
}

static inline int wctomb(char *s, wchar_t wc) {
    if (!s) return 0;
    *s = (char)(wc & 0x7F);
    return 1;
}

static inline size_t mbstowcs(wchar_t *dst, const char *src, size_t n) {
    size_t i = 0;
    while (i < n && src[i]) {
        if (dst) dst[i] = (wchar_t)(unsigned char)src[i];
        i++;
    }
    if (dst && i < n) dst[i] = 0;
    return i;
}

static inline size_t wcstombs(char *dst, const wchar_t *src, size_t n) {
    size_t i = 0;
    while (i < n && src[i]) {
        if (dst) dst[i] = (char)(src[i] & 0x7F);
        i++;
    }
    if (dst && i < n) dst[i] = 0;
    return i;
}

static inline int mblen(const char *s, size_t n) {
    if (!s) return 0;
    if (n == 0) return -1;
    return *s ? 1 : 0;
}

static inline wint_t btowc(int c) { return (c == EOF) ? WEOF : (wint_t)(unsigned char)c; }
static inline int wctob(wint_t c) { return (c < 256) ? (int)c : EOF; }

static inline int swprintf(wchar_t *s, size_t n, const wchar_t *fmt, ...) { (void)s; (void)n; (void)fmt; return 0; }

static inline long wcstol(const wchar_t *nptr, wchar_t **endptr, int base) {
    (void)nptr; (void)endptr; (void)base;
    return 0;
}

static inline wchar_t *wcstok(wchar_t *str, const wchar_t *delim, wchar_t **ptr) {
    (void)str; (void)delim; (void)ptr;
    return NULL;
}

#endif
