#include <iostream>

long pow(long number, int pow) {
    long result = 1;

    for (int i = 1; i <= pow; i++) {
        result *= number;
    }

    return result;
}

int getTrianglePositionNumber(int currentPos, long currentSum, long targetNumber) {
    long nextSum = currentSum + pow(currentPos, 3);
    if (nextSum < targetNumber) {
        return getTrianglePositionNumber(++currentPos, nextSum, targetNumber);
    }

    if (nextSum == targetNumber) {
        return currentPos;
    }

    return 0;
}

int main(int argc, char **argv) {
    std::cout << "Hello triangles!" << std::endl;

	for (long i = 0; i < 9223372036854775807; i++) {
		int num = getTrianglePositionNumber(1, 0, pow(i, 2));
		if (num != 0) {
			std::cout << "Num is: " << i << ", Pos: " << num << std::endl;
		}
	}
}