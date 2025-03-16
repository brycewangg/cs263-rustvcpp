# C++ Threads
Analysis of threads in C++

## Source Code
```C++
#include <iostream>
#include <thread>
#include <vector>

void increment() {
    double counter = 0;
    for (int i = 0; i < 1000000; i++) {
        counter++;
    }

    std::cout << "Counter is: " << counter << "\n";
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; i++) {
        threads.push_back(std::thread(increment));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
```

## Benchmarks Without O3 Optimization

### Runtime
Threads = 100
Counter = 1000000
```
real    0m0.085s
user    0m0.499s
sys     0m0.015s
```

Threads = 1000
Counter = 1000000
```
real    0m0.595s
user    0m4.261s
sys     0m0.069s
```

## Benchmarks With O3 Optimization

### Runtime
Threads = 100
Counter = 1000000
```
real    0m0.042s
user    0m0.164s
sys     0m0.016s
```

Threads = 100
Counter = 1000000000
```
real    0m15.391s
user    1m58.526s
sys     0m0.331s
```

Threads = 1000
Counter = 1000000
```
real    0m0.203s
user    0m1.270s
sys     0m0.076s
```

Threads = 1000
Counter = 1000000000
```
real    2m40.030s
user    19m41.438s
sys     0m5.625s
```