#include <iostream>
#include <algorithm>
int a[1024+1];
int main() {
	for (int i = 0; i <= a[0]; i++) std::cin >> a[i];
	std::cout << (std::prev_permutation(a+1, a + 1 + a[0]) ? "no" : "yes") << std::endl;
}
