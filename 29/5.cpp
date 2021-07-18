#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL qpow(LL a,LL b,LL p) {
	LL ret=1;
	while(b) {
		if (b&1) ret=ret*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ret;
}
int n,B;
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &B);
		printf("%lld\n", n*qpow(B, 9971, 9973) % 9973);
	}
	return 0;
}
