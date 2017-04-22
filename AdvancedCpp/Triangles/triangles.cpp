#include <cstdio>
#include <cmath>

#define myType unsigned long long

myType solveQuadraticEquation(myType triangleNumber) {
	myType c = triangleNumber * 2;
	myType d = 1 + (4 * c);
	myType x1 = (-1 + sqrt(d)) / 2;
	myType x2 = (-1 - sqrt(d)) / 2;
	return x1;
}

myType getSequentionalNumberOfTriangleNumber(myType triangleNumber) {	
	return solveQuadraticEquation(triangleNumber);
}

int main(int argc, char **argv) {	
	myType triangleNumber;

	printf("Enter a triangle number: ");
	scanf("%llu", &triangleNumber);
	printf("Trinangle number is: %llu", getSequentionalNumberOfTriangleNumber(triangleNumber));
	scanf("%llu", &triangleNumber);
	return 0;
}