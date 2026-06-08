#include <stddef.h>

struct cervus_symbol {
    const char *name;
    void *addr;
};

/* libc standard I/O and utility functions */
extern void printf();
extern void sprintf();
extern void snprintf();
extern void vsprintf();
extern void vsnprintf();
extern void fprintf();
extern void vfprintf();
extern void puts();
extern void putchar();
extern void getchar();
extern void fgets();
extern void fputs();
extern void fputc();
extern void fgetc();
extern void fopen();
extern void fclose();
extern void fread();
extern void fwrite();
extern void fflush();
extern void fseek();
extern void ftell();
extern void rewind();
extern void feof();
extern void ferror();
extern void clearerr();
extern void fileno();
extern void malloc();
extern void calloc();
extern void realloc();
extern void free();
extern void exit();
extern void abort();
extern void abs();
extern void labs();
extern void llabs();
extern void atoi();
extern void atol();
extern void atoll();
extern void strtol();
extern void strtoul();
extern void strtoll();
extern void strtoull();
extern unsigned long long __cervus_strtod_bits(const char *s, char **endptr);

double strtod(const char *s, char **endp)
{
    unsigned long long b = __cervus_strtod_bits(s, endp);
    double d;
    __builtin_memcpy(&d, &b, sizeof(d));
    return d;
}

float strtof(const char *s, char **endp)
{
    return (float)strtod(s, endp);
}

long double strtold(const char *s, char **endp)
{
    return (long double)strtod(s, endp);
}
extern void rand();
extern void srand();
extern void system();

/* POSIX File / Process / System functions */
extern void open();
extern void close();
extern void read();
extern void write();
extern void lseek();
extern void ioctl();
extern void stat();
extern void fstat();
extern void mkdir();
extern void rmdir();
extern void access();
extern void chdir();
extern void getcwd();
extern void symlink();
extern void readlink();
extern void truncate();
extern void ftruncate();
extern void fsync();
extern void fdatasync();
extern void getdents();
extern void fork();
extern void execve();
extern int execv(const char *path, char *const argv[]);
extern void execvp();
typedef __builtin_va_list va_list;
#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
int execl(const char *path, const char *arg, ...)
{
    char *argv[64];
    argv[0] = (char *)arg;
    int argc = 1;
    va_list args;
    va_start(args, arg);
    while (argc < 63) {
        char *a = va_arg(args, char *);
        argv[argc++] = a;
        if (!a) break;
    }
    argv[63] = NULL;
    va_end(args);
    return execv(path, argv);
}
extern void _exit();
extern void wait();
extern void waitpid();
extern void getpid();
extern void getppid();
extern void getuid();
extern void getgid();
extern void setuid();
extern void setgid();
extern void sleep();
extern void usleep();
unsigned int alarm(unsigned int seconds)
{
    (void)seconds;
    return 0;
}
extern void time();
extern void clock_gettime();
extern void gettimeofday();

/* String and memory functions */
extern void strlen();
extern void strcpy();
extern void strncpy();
extern void strcat();
extern void strncat();
extern void strcmp();
extern void strncmp();
extern void strchr();
extern void strrchr();
extern void strstr();
extern void strspn();
extern void strcspn();
extern void strpbrk();
extern void strtok();
extern void strdup();
extern void strndup();
extern void strerror();
extern void memset();
extern void memcpy();
extern void memmove();
extern void memcmp();
extern void memchr();

/* Math functions */
extern void sin();
extern void cos();
extern void tan();
extern void asin();
extern void acos();
extern void atan();
extern void atan2();
extern void sinh();
extern void cosh();
extern void tanh();
extern void exp();
extern void log();
extern void log10();
extern double pow(double base, double exp);
typedef long long int64_t;

double sqrt(double x)
{
    double result;
    __asm__ volatile ("sqrtsd %1, %0" : "=x"(result) : "x"(x));
    return result;
}

double ceil(double x)
{
    int64_t i = (int64_t)x;
    return (double)(i + (x > (double)i));
}

double floor(double x)
{
    int64_t i = (int64_t)x;
    return (double)(i - (x < (double)i));
}

double round(double x)
{
    return (x >= 0.0) ? floor(x + 0.5) : ceil(x - 0.5);
}
double cbrt(double x)
{
    if (x == 0.0) return 0.0;
    if (x < 0.0) return -pow(-x, 1.0/3.0);
    return pow(x, 1.0/3.0);
}

double hypot(double x, double y)
{
    return sqrt(x*x + y*y);
}

double trunc(double x)
{
    return (x >= 0.0) ? floor(x) : ceil(x);
}
extern void fmod();
extern void fabs();

/* Custom Cervus APIs */
extern void cervus_mouse_poll();

/* libgui functions and variables */
extern void gui_init();
extern void gui_clear();
extern void gui_draw_rect();
extern void gui_draw_filled_circle();
extern void gui_draw_window();
extern void gui_draw_cursor();
extern void gui_flush();
extern void gui_deinit();
extern void gui_mouse_poll();
extern int  gui_screen_w;
extern int  gui_screen_h;

const struct cervus_symbol __cervus_symbols[] = {
    { "printf", &printf },
    { "sprintf", &sprintf },
    { "snprintf", &snprintf },
    { "vsprintf", &vsprintf },
    { "vsnprintf", &vsnprintf },
    { "fprintf", &fprintf },
    { "vfprintf", &vfprintf },
    { "puts", &puts },
    { "putchar", &putchar },
    { "getchar", &getchar },
    { "fgets", &fgets },
    { "fputs", &fputs },
    { "fputc", &fputc },
    { "fgetc", &fgetc },
    { "fopen", &fopen },
    { "fclose", &fclose },
    { "fread", &fread },
    { "fwrite", &fwrite },
    { "fflush", &fflush },
    { "fseek", &fseek },
    { "ftell", &ftell },
    { "rewind", &rewind },
    { "feof", &feof },
    { "ferror", &ferror },
    { "clearerr", &clearerr },
    { "fileno", &fileno },
    { "malloc", &malloc },
    { "calloc", &calloc },
    { "realloc", &realloc },
    { "free", &free },
    { "exit", &exit },
    { "abort", &abort },
    { "abs", &abs },
    { "labs", &labs },
    { "llabs", &llabs },
    { "atoi", &atoi },
    { "atol", &atol },
    { "atoll", &atoll },
    { "strtol", &strtol },
    { "strtoul", &strtoul },
    { "strtoll", &strtoll },
    { "strtoull", &strtoull },
    { "strtod", &strtod },
    { "strtof", &strtof },
    { "strtold", &strtold },
    { "rand", &rand },
    { "srand", &srand },
    { "system", &system },

    { "open", &open },
    { "close", &close },
    { "read", &read },
    { "write", &write },
    { "lseek", &lseek },
    { "ioctl", &ioctl },
    { "stat", &stat },
    { "fstat", &fstat },
    { "mkdir", &mkdir },
    { "rmdir", &rmdir },
    { "access", &access },
    { "chdir", &chdir },
    { "getcwd", &getcwd },
    { "symlink", &symlink },
    { "readlink", &readlink },
    { "truncate", &truncate },
    { "ftruncate", &ftruncate },
    { "fsync", &fsync },
    { "fdatasync", &fdatasync },
    { "getdents", &getdents },
    { "fork", &fork },
    { "execve", &execve },
    { "execv", &execv },
    { "execvp", &execvp },
    { "execl", &execl },
    { "_exit", &_exit },
    { "wait", &wait },
    { "waitpid", &waitpid },
    { "getpid", &getpid },
    { "getppid", &getppid },
    { "getuid", &getuid },
    { "getgid", &getgid },
    { "setuid", &setuid },
    { "setgid", &setgid },
    { "sleep", &sleep },
    { "usleep", &usleep },
    { "alarm", &alarm },
    { "time", &time },
    { "clock_gettime", &clock_gettime },
    { "gettimeofday", &gettimeofday },

    { "strlen", &strlen },
    { "strcpy", &strcpy },
    { "strncpy", &strncpy },
    { "strcat", &strcat },
    { "strncat", &strncat },
    { "strcmp", &strcmp },
    { "strncmp", &strncmp },
    { "strchr", &strchr },
    { "strrchr", &strrchr },
    { "strstr", &strstr },
    { "strspn", &strspn },
    { "strcspn", &strcspn },
    { "strpbrk", &strpbrk },
    { "strtok", &strtok },
    { "strdup", &strdup },
    { "strndup", &strndup },
    { "strerror", &strerror },
    { "memset", &memset },
    { "memcpy", &memcpy },
    { "memmove", &memmove },
    { "memcmp", &memcmp },
    { "memchr", &memchr },

    { "sin", &sin },
    { "cos", &cos },
    { "tan", &tan },
    { "asin", &asin },
    { "acos", &acos },
    { "atan", &atan },
    { "atan2", &atan2 },
    { "sinh", &sinh },
    { "cosh", &cosh },
    { "tanh", &tanh },
    { "exp", &exp },
    { "log", &log },
    { "log10", &log10 },
    { "pow", &pow },
    { "sqrt", &sqrt },
    { "cbrt", &cbrt },
    { "hypot", &hypot },
    { "ceil", &ceil },
    { "floor", &floor },
    { "round", &round },
    { "trunc", &trunc },
    { "fmod", &fmod },
    { "fabs", &fabs },

    { "cervus_mouse_poll", &cervus_mouse_poll },

    { "gui_init", &gui_init },
    { "gui_clear", &gui_clear },
    { "gui_draw_rect", &gui_draw_rect },
    { "gui_draw_filled_circle", &gui_draw_filled_circle },
    { "gui_draw_window", &gui_draw_window },
    { "gui_draw_cursor", &gui_draw_cursor },
    { "gui_flush", &gui_flush },
    { "gui_deinit", &gui_deinit },
    { "gui_mouse_poll", &gui_mouse_poll },
    { "gui_screen_w", &gui_screen_w },
    { "gui_screen_h", &gui_screen_h },
};
const size_t __cervus_symbols_count = sizeof(__cervus_symbols) / sizeof(__cervus_symbols[0]);
