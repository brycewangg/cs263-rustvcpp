# Out-of-Bounds Access: C++ vs. Rust

## Program Overview
Both programs (out_of_bounds.cpp and out_of_bounds.rs) attempt to access an out-of-bounds index in a vector. The key differences lie in how each language handles this scenario.

## C++ Implementation
Unsafe Access with [] operator:
```asm
movq	-88(%rbp), %rsi  ; Load the vector pointer
movq	-80(%rbp), %rdx  ; Load the size of the vector
callq	_ZNSt6vectorIiSaIiEEixEm  ; Call vec[5]
movl	(%rax), %esi  ; Load the value at vec[5]
```

```asm
Dump of assembler code for function _ZNSt6vectorIiSaIiEEixEm:
0x0000555555555410 <+0>:     push   rbp
0x0000555555555411 <+1>:     mov    rbp,rsp
0x0000555555555414 <+4>:     mov    QWORD PTR [rbp-0x8],rdi
0x0000555555555418 <+8>:     mov    QWORD PTR [rbp-0x10],rsi
0x000055555555541c <+12>:    mov    rax,QWORD PTR [rbp-0x8]
0x0000555555555420 <+16>:    mov    rax,QWORD PTR [rax]
0x0000555555555423 <+19>:    mov    rcx,QWORD PTR [rbp-0x10]
0x0000555555555427 <+23>:    shl    rcx,0x2
0x000055555555542b <+27>:    add    rax,rcx
0x000055555555542e <+30>:    pop    rbp
0x000055555555542f <+31>:    ret  
```

Safe Access with at() function:
```asm
callq	_ZNSt6vectorIiSaIiEE2atEm  ; Call vec.at(5)
```

This is a call to a wrapper function what checks the index first
```asm
Dump of assembler code for function _ZNSt6vectorIiSaIiEE2atEm:
0x0000555555555430 <+0>:     push   rbp
0x0000555555555431 <+1>:     mov    rbp,rsp
0x0000555555555434 <+4>:     sub    rsp,0x20
0x0000555555555438 <+8>:     mov    QWORD PTR [rbp-0x8],rdi
0x000055555555543c <+12>:    mov    QWORD PTR [rbp-0x10],rsi
0x0000555555555440 <+16>:    mov    rdi,QWORD PTR [rbp-0x8]
0x0000555555555444 <+20>:    mov    QWORD PTR [rbp-0x18],rdi
0x0000555555555448 <+24>:    mov    rsi,QWORD PTR [rbp-0x10]
0x000055555555544c <+28>:    call   0x555555555d70 <_ZNKSt6vectorIiSaIiEE14_M_range_checkEm>
0x0000555555555451 <+33>:    mov    rdi,QWORD PTR [rbp-0x18]
0x0000555555555455 <+37>:    mov    rsi,QWORD PTR [rbp-0x10]
0x0000555555555459 <+41>:    call   0x555555555dd0 <_ZNSt6vectorIiSaIiEEixEm>
0x000055555555545e <+46>:    add    rsp,0x20
0x0000555555555462 <+50>:    pop    rbp
0x0000555555555463 <+51>:    ret
```

```asm
Dump of assembler code for function _ZNKSt6vectorIiSaIiEE14_M_range_checkEm:
0x0000555555555d70 <+0>:     push   rbp
0x0000555555555d71 <+1>:     mov    rbp,rsp
0x0000555555555d74 <+4>:     sub    rsp,0x30
0x0000555555555d78 <+8>:     mov    QWORD PTR [rbp-0x8],rdi
0x0000555555555d7c <+12>:    mov    QWORD PTR [rbp-0x10],rsi
0x0000555555555d80 <+16>:    mov    rdi,QWORD PTR [rbp-0x8]
0x0000555555555d84 <+20>:    mov    QWORD PTR [rbp-0x20],rdi
0x0000555555555d88 <+24>:    mov    rax,QWORD PTR [rbp-0x10]
0x0000555555555d8c <+28>:    mov    QWORD PTR [rbp-0x18],rax
0x0000555555555d90 <+32>:    call   0x555555555df0 <_ZNKSt6vectorIiSaIiEE4sizeEv>
0x0000555555555d95 <+37>:    mov    rcx,rax
0x0000555555555d98 <+40>:    mov    rax,QWORD PTR [rbp-0x18]
0x0000555555555d9c <+44>:    cmp    rax,rcx
0x0000555555555d9f <+47>:    jb     0x555555555dc7 <_ZNKSt6vectorIiSaIiEE14_M_range_checkEm+87>
0x0000555555555da1 <+49>:    mov    rdi,QWORD PTR [rbp-0x20]
0x0000555555555da5 <+53>:    mov    rax,QWORD PTR [rbp-0x10]
0x0000555555555da9 <+57>:    mov    QWORD PTR [rbp-0x28],rax
0x0000555555555dad <+61>:    call   0x555555555df0 <_ZNKSt6vectorIiSaIiEE4sizeEv>
0x0000555555555db2 <+66>:    mov    rsi,QWORD PTR [rbp-0x28]
0x0000555555555db6 <+70>:    mov    rdx,rax
0x0000555555555db9 <+73>:    lea    rdi,[rip+0x275]        # 0x555555556035
0x0000555555555dc0 <+80>:    mov    al,0x0
0x0000555555555dc2 <+82>:    call   0x5555555550c0 <_ZSt24__throw_out_of_range_fmtPKcz@plt>
0x0000555555555dc7 <+87>:    add    rsp,0x30
0x0000555555555dcb <+91>:    pop    rbp
0x0000555555555dcc <+92>:    ret
```

```asm
Dump of assembler code for function _ZNKSt6vectorIiSaIiEE4sizeEv:
=> 0x0000555555555df0 <+0>:     push   rbp
   0x0000555555555df1 <+1>:     mov    rbp,rsp
   0x0000555555555df4 <+4>:     mov    QWORD PTR [rbp-0x8],rdi
   0x0000555555555df8 <+8>:     mov    rcx,QWORD PTR [rbp-0x8]
   0x0000555555555dfc <+12>:    mov    rax,QWORD PTR [rcx+0x8]
   0x0000555555555e00 <+16>:    mov    rcx,QWORD PTR [rcx]
   0x0000555555555e03 <+19>:    sub    rax,rcx
   0x0000555555555e06 <+22>:    sar    rax,0x2
   0x0000555555555e0a <+26>:    pop    rbp
   0x0000555555555e0b <+27>:    ret
```
```asm
Dump of assembler code for function _ZSt24__throw_out_of_range_fmtPKcz@plt:
=> 0x00005555555550c0 <+0>:     jmp    QWORD PTR [rip+0x2f82]        # 0x555555558048 <_ZSt24__throw_out_of_range_fmtPKcz@got.plt>
   0x00005555555550c6 <+6>:     push   0x9
   0x00005555555550cb <+11>:    jmp    0x555555555020
```

## Rust Implementation
Unsafe Access with [] operator (DO NOT USE THIS, THIS IS INCORRECT DATA):
```
callq	__ZN4core9panicking18panic_bounds_check17h4fadfa91bf056b25E  ; Panic on out-of-bounds access
```

Safe access with get() function:

```asm
0x000055555555bcfd <+77>:    call   0x55555555b900 <_ZN5alloc5slice29_$LT$impl$u20$$u5b$T$u5d$$GT$8into_vec17h80b784a9109a3f97E>                                                                             
   0x000055555555bd02 <+82>:    mov    rdi,QWORD PTR [rsp+0x18]                                                                                                                                                 
=> 0x000055555555bd07 <+87>:    call   0x55555555bb90 <_ZN72_$LT$alloc..vec..Vec$LT$T$C$A$GT$$u20$as$u20$core..ops..deref..Deref$GT$5deref17h4dfc7c74d9d9a0b2E> 
```

```asm
Dump of assembler code for function _ZN72_$LT$alloc..vec..Vec$LT$T$C$A$GT$$u20$as$u20$core..ops..deref..Deref$GT$5deref17h4dfc7c74d9d9a0b2E:
=> 0x000055555555bb90 <+0>:     sub    rsp,0x38
   0x000055555555bb94 <+4>:     mov    QWORD PTR [rsp+0x10],rdi
   0x000055555555bb99 <+9>:     mov    QWORD PTR [rsp+0x18],rdi
   0x000055555555bb9e <+14>:    mov    rax,QWORD PTR [rdi+0x8]
   0x000055555555bba2 <+18>:    mov    QWORD PTR [rsp],rax
   0x000055555555bba6 <+22>:    mov    QWORD PTR [rsp+0x20],rax
   0x000055555555bbab <+27>:    mov    QWORD PTR [rsp+0x28],rax
   0x000055555555bbb0 <+32>:    mov    rax,QWORD PTR [rdi+0x10]
   0x000055555555bbb4 <+36>:    mov    QWORD PTR [rsp+0x8],rax
   0x000055555555bbb9 <+41>:    mov    QWORD PTR [rsp+0x30],rax
   0x000055555555bbbe <+46>:    mov    rcx,QWORD PTR [rsp+0x8]
   0x000055555555bbc3 <+51>:    mov    rdi,QWORD PTR [rsp]
   0x000055555555bbc7 <+55>:    mov    edx,0x4
   0x000055555555bbcc <+60>:    mov    rsi,rdx
   0x000055555555bbcf <+63>:    call   0x55555555b370 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE>
   0x000055555555bbd4 <+68>:    mov    rdx,QWORD PTR [rsp+0x8]
   0x000055555555bbd9 <+73>:    mov    rax,QWORD PTR [rsp]
   0x000055555555bbdd <+77>:    add    rsp,0x38
   0x000055555555bbe1 <+81>:    ret
```

```asm
Dump of assembler code for function _ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE:                                             
=> 0x000055555555b370 <+0>:     sub    rsp,0xa8                                                                                                             
   0x000055555555b377 <+7>:     mov    QWORD PTR [rsp+0x10],rdi                                                                                             
   0x000055555555b37c <+12>:    mov    QWORD PTR [rsp+0x18],rsi                                                                                             
   0x000055555555b381 <+17>:    mov    QWORD PTR [rsp+0x20],rdx                                                                                             
   0x000055555555b386 <+22>:    mov    QWORD PTR [rsp+0x28],rcx                                                                                             
   0x000055555555b38b <+27>:    lea    rax,[rip+0x4c196]        # 0x5555555a7528                                                                            
   0x000055555555b392 <+34>:    mov    QWORD PTR [rsp+0x30],rax                                                                                             
   0x000055555555b397 <+39>:    mov    QWORD PTR [rsp+0x70],rdi                                                                                             
   0x000055555555b39c <+44>:    mov    QWORD PTR [rsp+0x78],rsi                                                                                             
   0x000055555555b3a1 <+49>:    mov    QWORD PTR [rsp+0x80],rdx                                                                                             
   0x000055555555b3a9 <+57>:    mov    QWORD PTR [rsp+0x88],rcx                                                                                             
   0x000055555555b3b1 <+65>:    mov    QWORD PTR [rsp+0x90],rdi                                                                                             
   0x000055555555b3b9 <+73>:    mov    QWORD PTR [rsp+0x98],rdi                                                                                             
   0x000055555555b3c1 <+81>:    cmp    rdi,0x0                                                                                                              
   0x000055555555b3c5 <+85>:    jne    0x55555555b3c9 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+89>                       
   0x000055555555b3c7 <+87>:    jmp    0x55555555b43a <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+202>                      
   0x000055555555b3c9 <+89>:    mov    rcx,QWORD PTR [rsp+0x20]                                                                                             
   0x000055555555b3ce <+94>:    mov    rax,rcx                                                                                                              
   0x000055555555b3d1 <+97>:    shr    rax,1                                                                                                                
   0x000055555555b3d4 <+100>:   movabs rdx,0x5555555555555555                                                                                               
   0x000055555555b3de <+110>:   and    rax,rdx                                                                                                              
   0x000055555555b3e1 <+113>:   sub    rcx,rax                                                                                                              
   0x000055555555b3e4 <+116>:   movabs rdx,0x3333333333333333                                                                                               
   0x000055555555b3ee <+126>:   mov    rax,rcx                                                                                                              
   0x000055555555b3f1 <+129>:   and    rax,rdx                                                                                                              
   0x000055555555b3f4 <+132>:   shr    rcx,0x2          
   0x000055555555b3f8 <+136>:   and    rcx,rdx                                                                                                              
   0x000055555555b3fb <+139>:   add    rax,rcx                                                                                                              
   0x000055555555b3fe <+142>:   mov    rcx,rax                                                                                                              
   0x000055555555b401 <+145>:   shr    rcx,0x4                                                                                                              
   0x000055555555b405 <+149>:   add    rax,rcx                                                                                                              
   0x000055555555b408 <+152>:   movabs rcx,0xf0f0f0f0f0f0f0f                                                                                                
   0x000055555555b412 <+162>:   and    rax,rcx                                                                                                              
   0x000055555555b415 <+165>:   movabs rcx,0x101010101010101                                                                                                
   0x000055555555b41f <+175>:   imul   rax,rcx                                                                                                              
   0x000055555555b423 <+179>:   shr    rax,0x38                                                                                                             
   0x000055555555b427 <+183>:   mov    DWORD PTR [rsp+0xa4],eax                                                                                             
   0x000055555555b42e <+190>:   cmp    DWORD PTR [rsp+0xa4],0x1                                                                                             
   0x000055555555b436 <+198>:   je     0x55555555b43f <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+207>                      
   0x000055555555b438 <+200>:   jmp    0x55555555b458 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+232>                      
   0x000055555555b43a <+202>:   jmp    0x55555555b4c9 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+345>                                    
   0x000055555555b43f <+207>:   mov    rax,QWORD PTR [rsp+0x10]                      
   0x000055555555b444 <+212>:   mov    rcx,QWORD PTR [rsp+0x20]                      
   0x000055555555b449 <+217>:   sub    rcx,0x1                                       
   0x000055555555b44d <+221>:   and    rax,rcx                                       
   0x000055555555b450 <+224>:   cmp    rax,0x0                                       
   0x000055555555b454 <+228>:   je     0x55555555b4b1 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+321>                                    
   0x000055555555b456 <+230>:   jmp    0x55555555b43a <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+202>                                    
   0x000055555555b458 <+232>:   lea    rax,[rip+0x4c0c9]        # 0x5555555a7528                                                                                          
   0x000055555555b45f <+239>:   mov    QWORD PTR [rsp+0x38],rax                      
   0x000055555555b464 <+244>:   mov    QWORD PTR [rsp+0x40],0x1                      
   0x000055555555b46d <+253>:   mov    rcx,QWORD PTR [rip+0x3eb8c]        # 0x55555559a000                                                                                
   0x000055555555b474 <+260>:   mov    rax,QWORD PTR [rip+0x3eb8d]        # 0x55555559a008                                                                                
   0x000055555555b47b <+267>:   mov    QWORD PTR [rsp+0x58],rcx                      
   0x000055555555b480 <+272>:   mov    QWORD PTR [rsp+0x60],rax                      
   0x000055555555b485 <+277>:   mov    QWORD PTR [rsp+0x48],0x8        
   0x000055555555b48e <+286>:   mov    QWORD PTR [rsp+0x50],0x0                                                                                             
   0x000055555555b497 <+295>:   lea    rsi,[rip+0x4c09a]        # 0x5555555a7538                                                                                          
   0x000055555555b49e <+302>:   lea    rax,[rip+0xfffffffffffff21b]        # 0x55555555a6c0 <_ZN4core9panicking9panic_fmt17h3d8fc78294164da7E>                                             
   0x000055555555b4a5 <+309>:   lea    rdi,[rsp+0x38]                                
   0x000055555555b4aa <+314>:   call   rax                                           
   0x000055555555b4ac <+316>:   jmp    0x55555555b537 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+455>                                                     
   0x000055555555b4b1 <+321>:   mov    rax,QWORD PTR [rsp+0x18]                      
   0x000055555555b4b6 <+326>:   cmp    rax,0x0                                                                                                                            
   0x000055555555b4ba <+330>:   sete   cl                                                                                                                                 
   0x000055555555b4bd <+333>:   mov    BYTE PTR [rsp+0xf],cl                                                                                                              
   0x000055555555b4c1 <+337>:   cmp    rax,0x0                                       
   0x000055555555b4c5 <+341>:   je     0x55555555b4de <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+366>                                                     
   0x000055555555b4c7 <+343>:   jmp    0x55555555b4e9 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+377>                                    
   0x000055555555b4c9 <+345>:   lea    rdi,[rip+0x3ed58]        # 0x55555559a228                                                                                          
   0x000055555555b4d0 <+352>:   lea    rax,[rip+0xfffffffffffff2a9]        # 0x55555555a780 <_ZN4core9panicking14panic_nounwind17hb98133c151c787e4E>                                       
   0x000055555555b4d7 <+359>:   mov    esi,0xa2                                      
   0x000055555555b4dc <+364>:   call   rax                                           
   0x000055555555b4de <+366>:   mov    QWORD PTR [rsp+0x68],0xffffffffffffffff                                                                                                             
   0x000055555555b4e7 <+375>:   jmp    0x55555555b4f3 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+387>                                                     
   0x000055555555b4e9 <+377>:   mov    al,BYTE PTR [rsp+0xf]                                 
   0x000055555555b4ed <+381>:   test   al,0x1                                                
   0x000055555555b4ef <+383>:   jne    0x55555555b51c <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+428>                                                     
   0x000055555555b4f1 <+385>:   jmp    0x55555555b501 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+401>                                                     
   0x000055555555b4f3 <+387>:   mov    rax,QWORD PTR [rsp+0x28]                              
   0x000055555555b4f8 <+392>:   cmp    rax,QWORD PTR [rsp+0x68]                              
   0x000055555555b4fd <+397>:   jbe    0x55555555b53b <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+459>                                                     
   0x000055555555b4ff <+399>:   jmp    0x55555555b539 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+457>                                                     
   0x000055555555b501 <+401>:   mov    rcx,QWORD PTR [rsp+0x18]                              
   0x000055555555b506 <+406>:   movabs rax,0x7fffffffffffffff                                
   0x000055555555b510 <+416>:   xor    edx,edx                                               
   0x000055555555b512 <+418>:   div    rcx                                                   
   0x000055555555b515 <+421>:   mov    QWORD PTR [rsp+0x68],rax                              
   0x000055555555b51a <+426>:   jmp    0x55555555b4f3 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+387>                                                     
   0x000055555555b51c <+428>:   lea    rdi,[rip+0x4c02d]        # 0x5555555a7550                                                                                                           
   0x000055555555b523 <+435>:   lea    rax,[rip+0xfffffffffffff8f6]        # 0x55555555ae20 <_ZN4core9panicking11panic_const23panic_const_div_by_zero17h5e45bd48e3e1455dE>                 
   0x000055555555b52a <+442>:   call   rax                                                   
   0x000055555555b52c <+444>:   jmp    0x55555555b537 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+455>                                                     
   0x000055555555b52e <+446>:   lea    rax,[rip+0xfffffffffffff43b]        # 0x55555555a970 <_ZN4core9panicking19panic_cannot_unwind17he9511e6e72319a3eE>                                  
   0x000055555555b535 <+453>:   call   rax                                                   
   0x000055555555b537 <+455>:   ud2                                                          
   0x000055555555b539 <+457>:   jmp    0x55555555b4c9 <_ZN4core5slice3raw14from_raw_parts18precondition_check17hb9f54b1c5a4f85ebE+345>                                                     
   0x000055555555b53b <+459>:   add    rsp,0xa8                                              
   0x000055555555b542 <+466>:   ret
```


## Results
We will be mainly comparing the C++ vector operation `at()` and the rust vector operation `get()` for safe element accesses. Under these conditions, the rust implementation has more assembly code than c++ code already (even without tracing the indirect calls (`call rax`) instructions).


# Optimized vector access
C++ safe `at()` access

```asm
Dump of assembler code for function main(int, char**):
   0x0000555555555140 <+0>:     push   rax
=> 0x0000555555555141 <+1>:     lea    rdi,[rip+0xebc]        # 0x555555556004
   0x0000555555555148 <+8>:     mov    esi,0x5
   0x000055555555514d <+13>:    mov    edx,0x3
   0x0000555555555152 <+18>:    xor    eax,eax
   0x0000555555555154 <+20>:    call   0x555555555030 <_ZSt24__throw_out_of_range_fmtPKcz@plt>
```


Rust safe `get()` access

```asm
Dump of assembler code for function main:
=> 0x000055555555ac40 <+0>:     push   rax
   0x000055555555ac41 <+1>:     mov    rcx,rsi
   0x000055555555ac44 <+4>:     movsxd rdx,edi
   0x000055555555ac47 <+7>:     lea    rax,[rip+0xffffffffffffffd2]        # 0x55555555ac20 <_ZN13out_of_bounds4main17hff2564204c4f92b3E>
   0x000055555555ac4e <+14>:    mov    QWORD PTR [rsp],rax
   0x000055555555ac52 <+18>:    lea    rsi,[rip+0x4aa3f]        # 0x5555555a5698
   0x000055555555ac59 <+25>:    mov    rdi,rsp
   0x000055555555ac5c <+28>:    xor    r8d,r8d
   0x000055555555ac5f <+31>:    call   QWORD PTR [rip+0x4cf73]        # 0x5555555a7bd8
   0x000055555555ac65 <+37>:    pop    rcx
   0x000055555555ac66 <+38>:    ret
```

***NOTE: The compiler does the range check for O3 optimization during compile time and throws the exception immediately (AKA: the compiler inlines the exception call in the assembly code)***


<!-- C++: -->
<!-- - Provides flexibility with both unsafe (operator[]) and safe (at()) access. -->
<!-- - Unsafe access is faster but can lead to undefined behavior. -->
<!-- - Safe access is slower but ensures bounds checking. -->
<!---->
<!-- Rust: -->
<!-- - Enforces memory safety by default, preventing common issues like out-of-bounds access. -->
<!-- - Provides safe alternatives (vec.get(5)) for graceful error handling. -->
<!-- - Panics on out-of-bounds access, ensuring the program does not continue with invalid memory access. -->
