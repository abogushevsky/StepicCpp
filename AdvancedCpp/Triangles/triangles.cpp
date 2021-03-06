#include <cstdio>
#include <cmath>

#define ull_int unsigned long long

ull_int solveQuadraticEquation(ull_int triangleNumber) {
	ull_int c = triangleNumber * 2;
	ull_int d = 1 + (4 * c);

	if (d < 0) {
		return 0;
	}

	ull_int x1 = (-1 + sqrt(d)) / 2;
	ull_int x2 = (-1 - sqrt(d)) / 2;
	return x1;
}

bool isCorrectTriangleNumber(ull_int sourceTriangleNumber, ull_int sequentialNumber) {
	return sourceTriangleNumber == ((pow(sequentialNumber, 2) + sequentialNumber) / 2);
}

ull_int getSequentionalNumberOfTriangleNumber(ull_int triangleNumber) {	
	ull_int result = solveQuadraticEquation(triangleNumber);
	return isCorrectTriangleNumber(triangleNumber, result) ? result : 0;
}

int main(int argc, char **argv) {	
	long double triangleNumber = 0;
	scanf("%Lf", &triangleNumber);
	ull_int roundedNumber = llround(triangleNumber);
	if (triangleNumber - roundedNumber != 0) {
		printf("%d", 0);
		return 0;
	}
	printf("%llu", getSequentionalNumberOfTriangleNumber(roundedNumber));

	return 0;
}
