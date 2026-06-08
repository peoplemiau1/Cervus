#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

#include <sys/types.h>
#include <limits.h>

#define MAXPATHLEN PATH_MAX

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#endif
