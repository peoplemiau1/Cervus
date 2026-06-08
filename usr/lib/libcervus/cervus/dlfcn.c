#include <dlfcn.h>
#include <string.h>
#include <stddef.h>

struct cervus_symbol {
    const char *name;
    void *addr;
};

extern const struct cervus_symbol __cervus_symbols[];
extern const size_t __cervus_symbols_count;

void *dlopen(const char *filename, int flag) {
    (void)filename;
    (void)flag;
    return RTLD_DEFAULT;
}

int dlclose(void *handle) {
    (void)handle;
    return 0;
}

void *dlsym(void *handle, const char *symbol) {
    (void)handle;
    if (!symbol) return NULL;
    for (size_t i = 0; i < __cervus_symbols_count; i++) {
        if (strcmp(__cervus_symbols[i].name, symbol) == 0) {
            return __cervus_symbols[i].addr;
        }
    }
    return NULL;
}

char *dlerror(void) {
    return NULL;
}
