#include <iostream>
#include <thread>
#include <vector>

void increment() {
    double counter = 0;
    for (int i = 0; i < 1000000000; i++) {
        counter++;
    }

    std::cout << "Counter is: " << counter << "\n";
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 1000; i++) {
        threads.push_back(std::thread(increment));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}