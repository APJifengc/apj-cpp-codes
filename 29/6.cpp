#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL n,m,l;
 LL phi(LL n) {
	int ans = n;
	for (int i=2; i<=sqrt(n); i++) {
		if (n%i==0) {
			ans = ans / i * (i-1);
			while(n%i==0) n/=i;
		}
	}
	if (n>1) ans = ans/n*(n-1);
	return ans;
}
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
	if (!b) d=a,x=1,y=0;
	else {
		exgcd(b,a%b, d, x, y);
		LL t=x;x=y;y=t-(a/b)*y;
	}
}
LL qpow(LL a,LL b,LL p) {
	LL ret=1;
	while(b) {
		if (b&1) ret=ret*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ret;
}
int main() {
	scanf("%lld%lld%lld", &n, &m, &l);
	m%=phi(n+1);
	LL d,x,y;
	LL a=qpow(2,m,n+1),b=l,c=n+1;
	exgcd(a,c,d,x,y);
	printf("%lld\n", (x*(b/d)%(c/d)+c/d)%(c/d));
	return 0;
}
