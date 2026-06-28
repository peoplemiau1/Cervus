#!/bin/bash
set -e

CERVUS_ROOT="/home/asadula/Cervus"
SYSROOT_INC="$CERVUS_ROOT/usr/sysroot/usr/include"
SYSROOT_LIB="$CERVUS_ROOT/usr/sysroot/usr/lib"

CC="gcc"
CFLAGS="-U__linux__ -D__cervus__ -DHAVE_VERSION_H -ffreestanding -nostdlib -fno-stack-protector -mno-red-zone -fno-pie -fno-pic -O2 -nostdinc -isystem $SYSROOT_INC -I. -Isrc"
LDFLAGS="-nostdlib -static -L$SYSROOT_LIB $SYSROOT_LIB/crt0.o -lcervus"

SRCS=(
  src/config/config.c
  src/config/parsing.c
  src/info/battery.c
  src/info/bios.c
  src/info/colors.c
  src/info/cpu.c
  src/info/cursor_theme.c
  src/info/date.c
  src/info/desktop.c
  src/info/gpu.c
  src/info/gtk_theme.c
  src/info/host.c
  src/info/hostname.c
  src/info/icon_theme.c
  src/info/kernel.c
  src/info/light_colors.c
  src/info/local_ip.c
  src/info/login_shell.c
  src/info/memory.c
  src/info/os.c
  src/info/packages.c
  src/info/public_ip.c
  src/info/pwd.c
  src/info/shell.c
  src/info/swap.c
  src/info/term.c
  src/info/uptime.c
  src/info/user.c
  src/optdeps/glib.c
  src/optdeps/libpci.c
  src/utils/debug.c
  src/utils/queue.c
  src/utils/utils.c
  src/utils/wrappers.c
  src/main.c
)

echo "Compiling albafetch for Cervus OS..."
$CC $CFLAGS "${SRCS[@]}" $LDFLAGS -o albafetch

echo "Installing albafetch to sysroot..."
mkdir -p "$CERVUS_ROOT/usr/sysroot/usr/bin"
cp albafetch "$CERVUS_ROOT/usr/sysroot/usr/bin/albafetch"

echo "Done!"
