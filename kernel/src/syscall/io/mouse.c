#include "../../../include/syscall/syscall_internal.h"
#include "../../../include/drivers/ps2.h"

int64_t sys_mouse_state(uint64_t out_ptr)
{
    if (!out_ptr) return -EINVAL;
    if (!syscall_uptr_validate((void *)out_ptr, sizeof(cervus_mouse_state_t))) return -EFAULT;

    const mouse_state_t *ms = ps2_mouse_get_state();

    cervus_mouse_state_t out;
    out.x          = ms->x;
    out.y          = ms->y;
    out.btn_left   = ms->btn_left   ? 1 : 0;
    out.btn_right  = ms->btn_right  ? 1 : 0;
    out.btn_middle = ms->btn_middle ? 1 : 0;
    out.scroll     = (int32_t)ms->scroll;

    return syscall_copy_to_user((void *)out_ptr, &out, sizeof(out));
}
