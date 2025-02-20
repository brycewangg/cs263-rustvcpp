# Rust implementation of a Loop
Preliminary analysis of for loops in rust.

## Runtime
Using the time utility, the total runtime is about:
```
real	0m0.765s
user	0m0.765s
sys	0m0.000s
```

Note: The runtime for `loop` is even slower (over 5 seconds) with the `for i in 0..NUM` syntax. More analysis is needed to confirm why.
```
real	0m5.351s
user	0m5.346s
sys	0m0.000s
```

## Source code and assembly
```rust
const NUM: u32 = 1000000000; 
// ...
let mut x = 1;
let mut i = 0;
while i < NUM {
    x += 1;
    i += 1;
}
```
Below is the loop body in main
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
Interesting observations:
1. The `<main+20> jb` instruction jumps to the `<main+35> mov` instruction to avoid the `ret` instruction.
2. Also, the `<main+74> jmp` instruction jumps to `<main+92>` instruction. This is to skip over the panic handling code rust inserts to ensure some type of consistency.
3. Rust inserts overflow checks (e.g., `seto` and `jo` instructions) to ensure safety. These checks add extra instructions to the loop body, increasing the runtime.
4. The `for i in 0..NUM` syntax uses iterators, which introduce additional control flow and function calls (e.g., `next()`). This results in more complex assembly and slower execution compared to a simple while loop.

## Results/Analysis
Even if the instructions that handle the ret and panic were removed, the number of instructions emitted by the rust compiler is larger than that of c++. Additionally, there are more jump instructions taken per loop cycle. Even without considering the overhead introduced by additional jump instructions (assuming perfect speculative execution and other branch prediction hardware on modern cpus), longer loop body is probably contributing to the longer execution time than c++.

The measurable overhead in Rust loops, particularly with the `for i in 0..N syntax`, is primarily due to:
- Safety Mechanisms: Rust's default overflow checks and other safety guarantees introduce additional instructions.
- Iterator-Based Loops: The `for` loop in Rust uses iterators, which add overhead compared to a simple counter-based loop.
- Control Flow Complexity: Rust's assembly contains more jump instructions and a longer loop body, which can negatively impact performance.

The `for i in 0..N syntax` in Rust is implemented using iterators, which involve:
- Creating a range `(0..N)`.
- Calling `next()` on the iterator for each iteration.
- Handling the iterator's state and control flow.

This additional complexity results in more instructions and slower execution compared to a simple for loop.