# CS858

## Installation Guide

This section covers the a guide for setting up a VM, install bcc from source, and making bcc work on python.

### Setup a VM environment

The linux distribution selected for this project is Ubuntu 20.04. 

The VM manager that was used is multipass because it is very lightweight compare to other ones such as VirtualBox or QEMU. The only downside for this manager is that it does not have any graphical interface.

1. Install multipass from this [Multipass site](https://multipass.run)
2. Run the following command to create a new VM instance  (-n for name, -d for disk size, -m for memory). Default option may be slow at building everything so I use customized options.
   ```
   multipass launch -n eBPFLinux -d 15G -m 10G 
   ```
3. Run VM in terminal
   ```
   multipass start eBPFLinux
   multipass shell eBPFLinux
   ```
4. Basic installation and setup of new VM
   ```
   sudo apt-get update
   sudo apt-get install build-essential
   sudo apt-get install libncurses5
   ```

### Installation of bcc

As stated in the installation guide in the bcc github, the readily avaialble packages on the Ubuntu Universe is out of date. Hence to have the most up to date tool, the following installation steps are done directly from the source code.

1. Install all the basic packages
   ```
   sudo apt-get -y install bison build-essential cmake flex git libedit-dev \
   libllvm6.0 llvm-6.0-dev libclang-6.0-dev python zlib1g-dev libelf-dev \
   iperf3 luajit libluajit-5.1-dev netperf linux-headers-$(uname -r)
   ```
2. Build and compile bcc
   ```
   git clone https://github.com/iovisor/bcc.git
   mkdir bcc/build; cd bcc/build
   cmake ..
   make -j 8 # provide number of jobs to speed things up
   sudo make install
   cmake -DPYTHON_CMD=python3 .. # build python3 binding
   pushd src/python/
   make
   sudo make install
   popd
   ```
3. Check and make sure bcc is importable from python by opening python3 and try importing bcc. Please note that when running python3, it requires escalated priviledge so remember to use sudo.
4. Example python programs are in the examples folder within the cloned repository

# Linux kernel JIT spray for SMEP / KERNEXEC bypass

All credit to source listed below:
http://mainisusuallyafunction.blogspot.com/2012/11/attacking-hardened-linux-systems-with.html 


## How to run:

```
cd ko && make
cd ..
sudo insmod ko/jump.ko
echo 1 | sudo tee /proc/sys/net/core/bpf_jit_enable
gcc -Wall -O2 -o alameda alameda.c
./alameda
```

# CVE Vulnerability exploits

Credits: <br>
https://github.com/xmzyshypnc/CVE-2020-27194 <br>
https://github.com/ret2hell/CVE-2020-8835

## How to run
You can run either root or modprobe for the 27194 vulnerability

```
gcc -o expl root.c
./expl

```

For 8835 vulnerability, run with following
```
gcc -o expl exploit.c
./expl
```
