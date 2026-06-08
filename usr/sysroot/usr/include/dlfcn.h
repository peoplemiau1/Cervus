#ifndef _DLFCN_H
#define _DLFCN_H

#define RTLD_LAZY   1
#define RTLD_NOW    2
#define RTLD_GLOBAL 4
#define RTLD_LOCAL  8

#define RTLD_DEFAULT ((void *)0)

void *dlopen(const char *filename, int flag);
int dlclose(void *handle);
void *dlsym(void *handle, const char *symbol);
char *dlerror(void);

#endif
