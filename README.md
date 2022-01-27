# Barebone-OS-rasPi3

A simple OS that prints "Hello World", for RaspberryPi 3

## Pre-requisite

Here I am going to describe the steps that I went through to get my dev environment set up. I am, however, going to assume that you are working in a Linux environment.

### The Compiler

Most likely, your computer is running on an Intel or AMD processor that uses the x86_64 architecture. The raspberry pi processor, however, uses the ARM architecture. This difference means that we cannot use regular `gcc` that is likely already installed on your machine.

Building this kernel requires `binutils` and a `GCC cross compiler` built for the aarch64-elf target.

This [tutorial](https://wiki.osdev.org/GCC_Cross-Compiler) can be followed for any Operating System. 

> **ArchLinux** - I however am using the [AUR build](https://aur.archlinux.org/packages/aarch64-none-elf-gcc-bin/) for aarch64-elf target ie: `aarch64-none-elf`.

### The Virtual Machine

I am going to use `QEMU` to run the virtual machine. Newer versions of QEMU can emulate the raspberry pi hardware. We need QEMU AARCH64 VM.

We can check if it is installed by doing `qemu-system-aarch64 --version`

## Building

**NOTE** : You should pass `--enable-languages=c,c++` to the GCC `configure` script. Make sure to add the install location to your `$PATH` if it isn't already.

This repo doesn't contains the `bin/` & `sysroot/` directory structures will not be present. 

```bash
make setup        #Run to create this structure.
```

To compile, assemble, and link the code into `sysroot/kernel8.img`

```bash
make
```

To remove all build files 

```bash
make clean
```

## Testing

To test this code on QEMU

```bash
qemu-system-aarch64 -M raspi3b -serial null -serial stdio -kernel bin/rxchit.elf
```

To test on actual hardware

> `Not tested on actual hardware yet, Use on your own accord.`

## References

- [OSDev](https://wiki.osdev.org/)

- [Jake Sandler's Tutorial](https://jsandler18.github.io/)

- [bzt's *Bare Metal Programming on Raspberry Pi 3*](https://github.com/bztsrc/raspi3-tutorial)
