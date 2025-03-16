# Rust Threads
Analysis of threads in Rust

## Source Code
```Rust
use std::thread;

fn increment() {
    let mut counter:f64 = 0.0;
    let mut i:i32 = 0;
    while i < 1000000 {
        counter += 1.0;
        i += 1;
    }

    println!("Counter is: {}", counter);
}

fn main() {
    let mut handles = vec![];

    let mut i:i32 = 0;
    while i < 1000 {
        let handle = thread::spawn( || {
            increment();
        });
        handles.push(handle);
        i += 1;
    }

    for handle in handles {
        handle.join().unwrap();
    }
}
```

## Benchmarks Without O3 Optimization

## Runtime
Threads = 100
Counter = 1000000
```
real    0m0.091s
user    0m0.531s
sys     0m0.016s
```

Threads = 1000
Counter = 1000000
```
real    0m0.618s
user    0m4.551s
sys     0m0.072s
```

## Benchmarks With O3 Optimization
Threads = 100
Counter = 1000000
```
real    0m0.042s
user    0m0.169s
sys     0m0.017s
```

Threads = 100
Counter = 1000000000
```
real    0m15.628s
user    1m58.420s
sys     0m0.397s
```

Threads = 1000
Counter = 1000000
```
real    0m0.207s
user    0m1.262s
sys     0m0.062s
```

Threads = 1000
Counter = 1000000000
```
real    2m38.475s
user    19m39.369s
sys     0m4.980s
```

## Analysis
The runtime for both Rust and C++ seem to be about the same. This makes sense becuase both Rust and C++ probably use POSIX threads so the overhead for creating and joining threads is the same. The workload in each thread should be almost identical as tested in our loops so the overall runtime is very similar.

## Notes
Used an M1 chip with 8 cores (4p and 4e)