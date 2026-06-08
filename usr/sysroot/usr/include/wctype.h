#ifndef _WCTYPE_H
#define _WCTYPE_H

#include <wchar.h>
#include <ctype.h>

typedef unsigned long wctype_t;
typedef unsigned long wctrans_t;

static inline int iswalpha(wint_t c)  { return isalpha((int)c); }
static inline int iswdigit(wint_t c)  { return isdigit((int)c); }
static inline int iswalnum(wint_t c)  { return isalnum((int)c); }
static inline int iswspace(wint_t c)  { return isspace((int)c); }
static inline int iswupper(wint_t c)  { return isupper((int)c); }
static inline int iswlower(wint_t c)  { return islower((int)c); }
static inline int iswprint(wint_t c)  { return isprint((int)c); }
static inline int iswpunct(wint_t c)  { return ispunct((int)c); }
static inline int iswcntrl(wint_t c)  { return iscntrl((int)c); }
static inline int iswxdigit(wint_t c) { return isxdigit((int)c); }
static inline int iswgraph(wint_t c)  { return isgraph((int)c); }
static inline int iswblank(wint_t c)  { return c == ' ' || c == '\t'; }

static inline wint_t towupper(wint_t c) { return toupper((int)c); }
static inline wint_t towlower(wint_t c) { return tolower((int)c); }

static inline wctype_t wctype(const char *name) { (void)name; return 0; }
static inline int iswctype(wint_t wc, wctype_t t) { (void)wc; (void)t; return 0; }
static inline wctrans_t wctrans(const char *name) { (void)name; return 0; }
static inline wint_t towctrans(wint_t wc, wctrans_t t) { (void)wc; (void)t; return wc; }

#endif
