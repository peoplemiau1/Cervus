#include <string.h>
#include <sys/utsname.h>

#include "info.h"
#include "../utils/wrappers.h"

int hostname(char *dest) {
    struct utsname name;
    uname(&name);

    char *ptr = strstr(name.nodename, ".local");
    if(ptr)
        *ptr = 0;

    safeStrncpy(dest, name.nodename, DEST_SIZE);

    return RET_OK;
}
