#include <iostream>
using namespace std;

int gcd(int a, int b) {
	
	int step = 1;
	
	while (b != 0) {
		cout << "Step " << step << ": a = " << a << ", b = " << b << endl;
		
		// Calculate a % b and store it in a temporary variable
		int temp = b;
		b = a % b;
		a = temp;
		step++;
	}
	
	return a;
}

int main() {
	
	int num1, num2;
	cout << "Enter two integers to compute gcd: ";
	cin >> num1 >> num2;
	cout << endl;
	
	int result = gcd(num1, num2);
	cout << endl;
	cout << "GCD of " << num1 << " and " << num2 << " is " << result << endl;
	
	return 0;
}
