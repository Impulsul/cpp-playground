#include <iostream>

int main(int argc, char* argv[]) {
	if (argc <= 1)
	{
		std::cout << "No program arguments found." << std::endl;
		return 1;
	}

	int i = 1;
	while (i < argc) {
		std::cout << argv[i] << "\n";
		i++;
	}


	return 0;
}