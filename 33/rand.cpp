#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(0));
	freopen("2.in", "w", stdout);
	cout << 500 << endl;
	for(int i=1;i<=500;i++) {
		int a = rand() % 200000000;
		int b = rand() % a;
		cout << a << " " << b << endl;
	}
	return 0;
}
