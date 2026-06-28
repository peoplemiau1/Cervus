#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>

#include "info.h"
#include "../utils/wrappers.h"

// print the current user
int user(char *dest) {
    struct passwd *pw;

    unsigned uid = getuid();
    if((int)uid == -1) {
        // couldn't get UID
        return ERR_NO_INFO;
    }

    pw = getpwuid(uid);
    if(pw != NULL) {
        safeStrncpy(dest, pw->pw_name, DEST_SIZE);
    } else {
        // fallback
        char *user_env = getenv("USER");
        if(!user_env || !user_env[0]) user_env = getenv("LOGNAME");
        if(!user_env || !user_env[0]) user_env = "root";
        safeStrncpy(dest, user_env, DEST_SIZE);
    }

    return RET_OK;
}
