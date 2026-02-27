# Linux Kernel Process Runnable Inspector

## Overview
This Linux Kernel Module inspects and lists runnable processes in the system.

It creates a custom `/proc` entry:

/proc/proc_runnable_inspector

When read, it prints all processes currently in TASK_RUNNING state.

## Files

- proc_inspector_runnable.c  → Kernel module source
- Makefile                   → Build configuration
- README.md                  → Documentation
- LICENSE                    → License file

## Build

make

## Sign Module (Secure Boot Enabled Systems)

sudo /usr/src/linux-headers-$(uname -r)/scripts/sign-file sha256 \
~/kernel_keys/MOK.key \
~/kernel_keys/MOK.crt \
proc_inspector_runnable.ko

## Insert Module

sudo insmod proc_inspector_runnable.ko

## Use

cat /proc/proc_runnable_inspector

## Remove Module

sudo rmmod proc_inspector_runnable

## Check Logs

dmesg | tail

## Learning Concepts

- Linux Kernel Module basics
- proc filesystem
- task_struct traversal
- process states
- Secure Boot module signing

