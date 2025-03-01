# C++ implementation of a Loop
Preliminary analysis of for loops in c++

## Runtime
Using the time utility, the total runtime is about:
```
real	0m0.384s
user	0m0.383s
sys	0m0.000s
```

## Source code and assembly
```c++
#define NUM 1000000000
// ...
int x = 1;
for (int i = 0; i < NUM; i++) {
    x += 1;
}
```
Below is the loop body in main
```asm
main:
...
    0x0000555555555140 <+32>:	cmp    DWORD PTR [rbp-0x18],0x3b9aca00
    0x0000555555555147 <+39>:	jge    0x55555555515d <main(int, char**)+61>
    0x0000555555555149 <+41>:	mov    eax,DWORD PTR [rbp-0x14]
    0x000055555555514c <+44>:	add    eax,0x1
    0x000055555555514f <+47>:	mov    DWORD PTR [rbp-0x14],eax
    0x0000555555555152 <+50>:	mov    eax,DWORD PTR [rbp-0x18]
    0x0000555555555155 <+53>:	add    eax,0x1
    0x0000555555555158 <+56>:	mov    DWORD PTR [rbp-0x18],eax
    0x000055555555515b <+59>:	jmp    0x555555555140 <main(int, char**)+32>
```
I also tried loop_v2.cpp but it's the same asm code

## O3 Optimization Results

```c++
#include <iostream>

#define NUM 1000000000

int main(int argc, char *argv[]) {
	double x = 1.0;
	int i = 0;
	while (i < NUM) {
		x += 1.0;
		i += 1;
	}
	std::cout << x << std::endl;
	return 0;
}
```

```asm
0x0000555555555195 <+21>:	data16 cs nop WORD PTR [rax+rax*1+0x0]
0x00005555555551a0 <+32>:	addsd  xmm0,xmm1
0x00005555555551a4 <+36>:	addsd  xmm0,xmm1
0x00005555555551a8 <+40>:	addsd  xmm0,xmm1
0x00005555555551ac <+44>:	addsd  xmm0,xmm1
0x00005555555551b0 <+48>:	addsd  xmm0,xmm1
0x00005555555551b4 <+52>:	addsd  xmm0,xmm1
0x00005555555551b8 <+56>:	addsd  xmm0,xmm1
0x00005555555551bc <+60>:	addsd  xmm0,xmm1
0x00005555555551c0 <+64>:	addsd  xmm0,xmm1
0x00005555555551c4 <+68>:	addsd  xmm0,xmm1
0x00005555555551c8 <+72>:	add    eax,0xfffffff6
0x00005555555551cb <+75>:	jne    0x5555555551a0 <main(int, char**)+32>
```

The execution time is shown below:
```
real	0m0.598s
user	0m0.597s
sys	0m0.000s
```
