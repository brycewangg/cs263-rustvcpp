# cs263-rustvcpp
This project analyzes the difference between c++ and rust programs. This project will include micro-benchmarks testing various aspects of the two programming languages. We will also be comparing the assembly dumps of the programs to analyze the different optimization levels provided by the c++ and rust compiler. This is important because the c++ compiler is known to do egregious optimizations that can violate memory safe practices, while the rust compiler is hypothesized to be more conservative to maintain memory safety.

## Build Environments
The programs will be using LLVM as the compiler backend (clang++ for c++ and rustc for rust).

### x86_64
The main target machine architecture is x86_64 (64 bit).

## Progress Report/Comments

### 02-21-2025
There is no source code updates for me this week, but I did the following:
- Tried using the `perf` utility to profile programs. There were no issues so far.
- Also tried installing `AMD uProf`. Unfortunately does not support the Linux distro I am using. Might have to revisit this tool later.

- Continued learning rust, including threads, so I can compare them to `c`/`cpp` implementations.

## Final Report Plan
1. Finish the thread micro benchmark <===
    - General runtime.
2. Test with different optimization levels (O3)
    - threads and spot check the vectors as well
3. Rerun/test on M1 mac cpu also

By this weekend

-----
4. Find some real world applications? If time permits
5. Maybe explore cache behavior with `perf` utility?
