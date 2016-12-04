#include <iostream>

long pow(long number, long pow) {
    long result = 1;

    for (long i = 1; i <= pow; i++) {
        result *= number;
    }

    return result;
}

/*int getTrianglePositionNumber1(int currentPos, long currentSum, long targetNumber) {
    long nextSum = currentSum + pow(currentPos, 3);
    if (nextSum < targetNumber) {
        return getTrianglePositionNumber(++currentPos, nextSum, targetNumber);
    }

    if (nextSum == targetNumber) {
        return currentPos;
    }

    return 0;
}*/

long getTrianglePositionNumber(long targetNumber) {
    long currentSum = 0;
    long currentPos = 1;

    while (currentSum < targetNumber) {
        currentSum += pow(currentPos, 3);
        currentPos++;
    }

    return currentSum == targetNumber ? currentPos - 1 : 0;
}

/*int getTrianglePositionNumber(long targetNumber) {
    long currentNumber = 1;
    int result = 1;

    while (currentNumber < targetNumber) {
        currentNumber = 0.5 * (result * (result + 1));
        result++;
    }

    return currentNumber == targetNumber ? result - 1 : 0;
}*/

int main(int argc, char **argv) {
    std::cout << "Hello triangles!" << std::endl;

	for (long i = 0; i < 9223372036854775807; i++) {
		//int num = getTrianglePositionNumber(1, 0, pow(i, 2));
        long num = getTrianglePositionNumber(pow(i, 2));
        //int num = getTrianglePositionNumber(i);
		if (num != 0) {
			std::cout << "Num is: " << i << ", Pos: " << num << std::endl;
		}
	}
}