#include <iostream>

#define NUM 1000000000

int main(int argc, char *argv[]) {
	double x = 1.0;
	int i = 0;
	while (i < NUM) {
		x += 1.0;
		i += 1;
	}
	std::cout << x << std::endl;
	return 0;
}
