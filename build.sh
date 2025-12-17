#!/bin/bash

echo "Cleaning previous build..."
rm -rf initramfs
rm -f initramfs.cpio.gz
rm -f init shell

echo "Setting up initramfs structure..."
mkdir -p initramfs/dev

echo "Compiling init..."
gcc init.c -static -o init
cp init initramfs/

echo "Building all components from includes/..."
cd includes
make
cd ..

echo "Copying non-source files from includes/..."
cd includes
find . -type f ! -name '*.c' ! -name '*.h' ! -name '*.o' ! -name 'Makefile' -exec sh -c 'mkdir -p "../initramfs/$(dirname "{}")" && cp "{}" "../initramfs/{}"' \;
cd ..

echo "Creating device files..."
cd initramfs
sudo mknod -m 666 dev/console c 5 1 2>/dev/null || true
sudo mknod -m 666 dev/null c 1 3 2>/dev/null || true
cd ..

echo "Building initramfs..."
cd initramfs
find . | cpio -o -H newc | gzip > ../initramfs.cpio.gz
cd ..

echo "Booting in QEMU..."
cd linux-6.18.1

qemu-system-x86_64 -kernel arch/x86/boot/bzImage \
  -initrd ../initramfs.cpio.gz \
  -append "console=ttyS0" \
  -netdev user,id=net0 \
  -device e1000,netdev=net0 \
  -nographic