#ifndef _LANGINFO_H
#define _LANGINFO_H

typedef int nl_item;

#define CODESET    0
#define D_T_FMT    1
#define D_FMT      2
#define T_FMT      3
#define RADIXCHAR  4
#define THOUSEP     5
#define YESEXPR    6
#define NOEXPR     7
#define ERA        8
#define ERA_D_FMT  9
#define ERA_D_T_FMT 10
#define ERA_T_FMT  11
#define ALT_DIGITS 12

static inline char *nl_langinfo(nl_item item) {
    switch (item) {
    case CODESET: return "UTF-8";
    case RADIXCHAR: return ".";
    case THOUSEP: return "";
    default: return "";
    }
}

#endif
