#!/bin/bash

echo "Cleaning previous build..."
rm -rf initramfs
rm -f initramfs.cpio.gz
rm -f init shell

echo "Compiling init..."
gcc init.c -static -o init

echo "Compiling shell..."
cd corepack/shell
gcc -c registry.c -o registry.o
gcc -c executor.c -o executor.o
gcc -c main.c -o main.o
gcc registry.o executor.o main.o -static -o shell_binary
cd ../..

echo "Setting up initramfs structure..."
mkdir -p initramfs/bin
mkdir -p initramfs/dev
mkdir -p initramfs/etc/vulpos
mkdir -p initramfs/var/lib/vulpos/manifests
mkdir -p initramfs/usr/local/bin
mkdir -p initramfs/corepack

echo "Copying binaries to initramfs..."
cp init initramfs/
cp corepack/shell/shell_binary initramfs/corepack/shell  # Copy from corepack/shell/ dir to initramfs/corepack/ as 'shell'

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

qemu-system-x86_64 -kernel arch/x86/boot/bzImage \
  -initrd ../initramfs.cpio.gz \
  -append "console=ttyS0" \
  -netdev user,id=net0 \
  -device e1000,netdev=net0 \
  -nographic