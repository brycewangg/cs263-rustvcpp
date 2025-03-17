#include <iostream>
#define NUM 1000000000

int main(int argc, char *argv[]) {
	double x = 1;
	for (int i = 0; i < NUM; i++) {
		x += 1;
	}
	std::cout << x << std::endl;
	return 0;
}
