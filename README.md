# cs263-rustvcpp
This project analyzes the difference between c++ and rust programs. This project will include micro-benchmarks testing various aspects of the two programming languages. We will also be comparing the assembly dumps of the programs to analyze the different optimization levels provided by the c++ and rust compiler. This is important because the c++ compiler is known to do egregious optimizations that can violate memory safe practices, while the rust compiler is hypothesized to be more conservative to maintain memory safety.

## Build Environments
The programs will be using LLVM as the compiler backend (clang++ for c++ and rustc for rust).

### x86_64
The main target machine architecture is x86_64 (64 bit).
