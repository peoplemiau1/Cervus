#include <sys/cervus.h>
#include <sys/syscall.h>
#include <stdint.h>

int cervus_mouse_poll(cervus_mouse_state_t *out) {
    return (int)syscall1(SYS_MOUSE_STATE, out);
}
