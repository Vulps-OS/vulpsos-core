#!/bin/bash

echo "Cleaning previous build..."
rm -rf initramfs
rm -rf initramfs.cpio.gz
rm -rf init

echo "Compiling init..."
gcc init.c -static -o init

echo "Compiling shell..."
cd shell
gcc -c registry.c -o registry.o
gcc -c executor.c -o executor.o
gcc -c main.c -o main.o
gcc registry.o executor.o main.o -static -o shell
mv shell ../
cd ..

echo "Setting up initramfs structure..."
mkdir -p initramfs/bin
mkdir -p initramfs/dev
mkdir -p initramfs/etc/vulpos
mkdir -p initramfs/var/lib/vulpos/manifests
mkdir -p initramfs/usr/local/bin

echo "Copying binaries to initramfs..."
cp init initramfs/
cp shell initramfs/bin/

echo "Creating empty registry..."
touch initramfs/etc/vulpos/commands.registry

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