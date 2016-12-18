#include <iostream>
#include <string>

std::string scanInput() {
	std::string result = "";
	std::string tmp;
    
    /*while(std::cin >> tmp) {
        result += tmp + " ";
		std::cout << "Current: " << result << std::endl;
    }*/

    std::cin >> result;
    std::cout << "There are " << std::cin.rdbuf()->in_avail() << " symbols in input buffer" << std::endl;

    return result;
}

int main(int argc, char **argv) {
	auto inputString  = scanInput();
    std::cout << inputString << std::endl;
    //std::floor(N) == N
    return 0;
}