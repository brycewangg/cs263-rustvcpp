## C++ For Loops (No Optimization) 

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

## C++ For Loops (O3 Optimization) 
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

## Rust For Loops (No Optimization)

```asm
main:
...
0x000055555555ad64 <+20>:	cmp    DWORD PTR [rsp+0x14],0x3b9aca00
0x000055555555ad6c <+28>:	jb     0x55555555ad73 <_ZN7loop_v24main17h5a8b63a8186a5e9eE+35>
0x000055555555ad6e <+30>:	add    rsp,0x18
0x000055555555ad72 <+34>:	ret
0x000055555555ad73 <+35>:	mov    eax,DWORD PTR [rsp+0x10]
0x000055555555ad77 <+39>:	inc    eax
0x000055555555ad79 <+41>:	mov    DWORD PTR [rsp+0xc],eax
0x000055555555ad7d <+45>:	seto   al
0x000055555555ad80 <+48>:	jo     0x55555555ad9c <_ZN7loop_v24main17h5a8b63a8186a5e9eE+76>
0x000055555555ad82 <+50>:	mov    eax,DWORD PTR [rsp+0xc]
0x000055555555ad86 <+54>:	mov    DWORD PTR [rsp+0x10],eax
0x000055555555ad8a <+58>:	mov    eax,DWORD PTR [rsp+0x14]
0x000055555555ad8e <+62>:	add    eax,0x1
0x000055555555ad91 <+65>:	mov    DWORD PTR [rsp+0x8],eax
0x000055555555ad95 <+69>:	setb   al
0x000055555555ad98 <+72>:	jb     0x55555555adb6 <_ZN7loop_v24main17h5a8b63a8186a5e9eE+102>
0x000055555555ad9a <+74>:	jmp    0x55555555adac <_ZN7loop_v24main17h5a8b63a8186a5e9eE+92>
0x000055555555ad9c <+76>:	lea    rdi,[rip+0x4a8fd]        # 0x5555555a56a0
0x000055555555ada3 <+83>:	lea    rax,[rip+0xfffffffffffffcc6]        # 0x55555555aa70 <_ZN4core9panicking11panic_const24panic_const_add_overflow17ha82d29f5d520b81bE>
0x000055555555adaa <+90>:	call   rax
0x000055555555adac <+92>:	mov    eax,DWORD PTR [rsp+0x8]
0x000055555555adb0 <+96>:	mov    DWORD PTR [rsp+0x14],eax
0x000055555555adb4 <+100>:	jmp    0x55555555ad64 <_ZN7loop_v24main17h5a8b63a8186a5e9eE+20>
```

## C++ For Loops (O3 Optimization) 
```asm
0x000055555555bf41 <+17>:	data16 data16 data16 data16 data16 cs nop WORD PTR [rax+rax*1+0x0]
0x000055555555bf50 <+32>:	addsd  xmm1,xmm0
0x000055555555bf54 <+36>:	addsd  xmm1,xmm0
0x000055555555bf58 <+40>:	addsd  xmm1,xmm0
0x000055555555bf5c <+44>:	addsd  xmm1,xmm0
0x000055555555bf60 <+48>:	addsd  xmm1,xmm0
0x000055555555bf64 <+52>:	addsd  xmm1,xmm0
0x000055555555bf68 <+56>:	addsd  xmm1,xmm0
0x000055555555bf6c <+60>:	addsd  xmm1,xmm0
0x000055555555bf70 <+64>:	addsd  xmm1,xmm0
0x000055555555bf74 <+68>:	addsd  xmm1,xmm0
0x000055555555bf78 <+72>:	add    eax,0xfffffff6
0x000055555555bf7b <+75>:	jne    0x55555555bf50 <_ZN10loop_fp_O34main17h5f1a313573789bacE+32>
```
