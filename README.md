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

Credits:
https://github.com/xmzyshypnc/CVE-2020-27194
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
