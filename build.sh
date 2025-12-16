#!/bin/bash

echo "Compiling init and shell...."
gcc init.c -static -o init
gcc shell.c -static -o shell

echo "Copying binaries to initramfs...."
cp init initramfs/
cp shell initramfs/bin

echo "Building initramds..."
cd initramfs
find . | cpio -o -H newc | gzip > ../initramfs.cpio.gz
cd ..

echo "Booting in QEMU...."
cd linux-6.18.1
qemu-system-x86_64 -kernel arch/x86/boot/bzImage -initrd ../initramfs.cpio.gz -append "console=ttyS0" -nographic