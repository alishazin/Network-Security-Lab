#include <iostream>
using namespace std;

int gcd1(int a, int b) {
	
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

int gcd(int a, int b) {

	if (b == 0) {
		return a;
	}

	return gcd(b, a%b);

}

int main() {
	
	int num1, num2;
	cout << "Enter two integers to compute gcd: ";
	cin >> num1 >> num2;
	cout << endl;
	
	int result = gcd1(num1, num2);
	cout << endl;
	cout << "GCD of " << num1 << " and " << num2 << " is " << result << endl;
	
	int result1 = gcd(num1, num2);
	cout << endl;
	cout << "GCD of " << num1 << " and " << num2 << " is " << result1 << endl;
	
	return 0;
}
