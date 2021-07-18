#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL n;
LL phi(LL n) {
	LL ans=n;
	for(int i=2;i<=sqrt(n);i++) {
		if (n%i==0) {
			while(n%i==0) n/=i;
			ans=ans/i*(i-1);
		}
	}
	if (n>1) ans=ans/n*(n-1);
	return ans;
}
LL ans;
int main() {
	scanf("%lld", &n);
	for(int i=1;i<=sqrt(n);i++) {
		if (n%i==0) {
			ans+=i*phi(n/i);
			if (i*i!=n) ans+=(n/i)*phi(i);
		}
	}     	
	printf("%lld\n", ans);
	return 0;
}
