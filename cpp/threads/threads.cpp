#include <iostream>
#include <thread>
#include <vector>

void increment() {
    double counter = 0;
    for (int i = 0; i < 100000; i++) {
        counter++;
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.push_back(std::thread(increment));
    }
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Threads finished" << std::endl;
    return 0;
}