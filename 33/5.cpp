#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 1000005, P=1000000007;
LL n,k;
LL fac[MAXN],inv[MAXN],d[MAXN];
LL qpow(LL a,LL b) {
	LL ans = 1;
	while(b) {
		if (b&1) ans=ans*a%P;
		a=a*a%P;
		b>>=1;
	}
	return ans;
}
LL C(int n,int m) {
	return fac[n]*inv[m]%P*inv[n-m]%P;
}
LL ans;
int main() {
	scanf("%lld %lld", &n, &k);
	fac[1]=1,d[0]=2,d[1]=4,inv[0]=1;
	for(int i=2;i<=MAXN-5;i++) {
		fac[i]=fac[i-1]*i%P;
		d[i]=d[i-1]*d[i-1]%P;
	}
	for(int i=0;i<=MAXN-5;i++) d[i]=(d[i]==0?P-1:d[i]-1);
	inv[MAXN-5]=qpow(fac[MAXN-5], P-2);
	for(int i=MAXN-6;i>=1;i--) inv[i]=inv[i+1]*(i+1)%P;
	LL m=n-k;
	ans=d[m];
	for(int i=1;i<=10;i++) printf("%d ", inv[i]);
	puts("");
	for(int i=1;i<=m;i++) {
		if (i&1) ans=(ans+P-C(m,i)*d[m-i]%P)%P;
		else ans=(ans+C(m,i)*d[m-i]%P)%P;
	}
	printf("%lld\n", C(n,k)*ans%P);
	return 0;
}
