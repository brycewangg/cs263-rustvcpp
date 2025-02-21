# Out-of-Bounds Access: C++ vs. Rust

## Program Overview
Both programs (out_of_bounds.cpp and out_of_bounds.rs) attempt to access an out-of-bounds index in a vector. The key differences lie in how each language handles this scenario.

## C++ Implementation
Unsafe Access:
```
movq	-88(%rbp), %rsi  ; Load the vector pointer
movq	-80(%rbp), %rdx  ; Load the size of the vector
callq	_ZNSt6vectorIiSaIiEEixEm  ; Call vec[5]
movl	(%rax), %esi  ; Load the value at vec[5]
```

Safe Access:
```
callq	_ZNSt6vectorIiSaIiEE2atEm  ; Call vec.at(5)
```

## Rust Implementation
Unsafe Access:
```
callq	__ZN4core9panicking18panic_bounds_check17h4fadfa91bf056b25E  ; Panic on out-of-bounds access
```

## Results
C++:
- Provides flexibility with both unsafe (operator[]) and safe (at()) access.
- Unsafe access is faster but can lead to undefined behavior.
- Safe access is slower but ensures bounds checking.

Rust:
- Enforces memory safety by default, preventing common issues like out-of-bounds access.
- Provides safe alternatives (vec.get(5)) for graceful error handling.
- Panics on out-of-bounds access, ensuring the program does not continue with invalid memory access.