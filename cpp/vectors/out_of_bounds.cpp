#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
	std::vector<int> vec = {1, 2, 3};
	// std::cout << vec[5] << std::endl;
	std::cout << vec.at(5) << std::endl;
	return 0;
}
