#include <iostream>

#define myType long long

 myType pow(myType number, myType pow) {
     myType result = 1;

    for (myType i = 1; i <= pow; i++) {
        result *= number;
    }

    return result;
}

myType getTrianglePositionNumber(myType targetNumber) {
    myType currentSum = 0;
    myType currentPos = 1;

    while (currentSum < targetNumber) {
        currentSum += pow(currentPos, 3);
        currentPos++;
    }

    return currentSum == targetNumber ? currentPos - 1 : 0;
}

/*int getTrianglePositionNumber(myType targetNumber) {
    myType currentNumber = 1;
    int result = 1;

    while (currentNumber < targetNumber) {
        currentNumber = 0.5 * (result * (result + 1));
        result++;
    }

    return currentNumber == targetNumber ? result - 1 : 0;
}*/

int main(int argc, char **argv) {
    std::cout << "Hello triangles!" << std::endl;

    /*myType num = getTrianglePositionNumber(pow(46360, 2));
    std::cout << "Num is: " << 46360 << ", Pos: " << num << std::endl;
    return 0;*/

	for (myType i = 0; i < 9223372036854775807; i++) {
		//int num = getTrianglePositionNumber(1, 0, pow(i, 2));
        myType num = getTrianglePositionNumber(pow(i, 2));
        //int num = getTrianglePositionNumber(i);
		if (num != 0) {
			std::cout << "Num is: " << i << ", Pos: " << num << std::endl;
		}
	}
}