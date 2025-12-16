#!/bin/bash

echo "Compiling init and shell..."
gcc init.c -static -o init
gcc shell.c -static -o shell

echo "Setting up initramfs structure..."
mkdir -p initramfs/bin
mkdir -p initramfs/dev

echo "Copying binaries to initramfs..."
cp init initramfs/
cp shell initramfs/bin/

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
qemu-system-x86_64 -kernel arch/x86/boot/bzImage -initrd ../initramfs.cpio.gz -append "console=ttyS0" -nographic
