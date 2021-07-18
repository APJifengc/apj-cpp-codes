#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int P = 1e9+7;
const int MAXN = 1000005;
int t,n,m;
int qpow(LL a,LL b) {
	LL ans=1;
	while(b) {
		if (b&1) ans=ans*a%P;
		a=a*a%P;
		b>>=1;
	}
	return ans;
}
int fac[MAXN], inv[MAXN], d[MAXN];
int C(int n,int m) {
	if (m>n) return 0;
	return (LL)fac[n]*inv[m]%P*inv[n-m]%P;
}
int A(int n,int m) {
	return (LL)fac[n]*inv[n-m]%P;
}
int main() {
	inv[0]=1;
	fac[1]=1;
	for(int i=2;i<MAXN;i++) fac[i]=(LL)fac[i-1]*i%P;
	inv[MAXN-5]=qpow(fac[MAXN-5], P-2);
	for(int i=MAXN-6;i>=1;i--) inv[i]=(LL)inv[i+1]*(i+1)%P;
	d[0]=1,d[1]=0;
	for(int i=2;i<MAXN;i++) d[i]=(LL)(i-1)*((d[i-1]+d[i-2])%P)%P;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		printf("%lld\n", (LL)C(n,m)*d[n-m]%P);
	}
	return 0;
}
