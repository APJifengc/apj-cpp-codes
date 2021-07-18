#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 10000005;
int fac[MAXN], inv[MAXN], ans[MAXN], v[MAXN], prime[700000], cnt;
bool isPrime[MAXN];
LL n,m,t,r;
int main() {
	scanf("%lld%lld", &t, &r);
	fac[1]=1,inv[1]=1,ans[1]=1,v[1]=1;
	for (int i=2;i<=MAXN-5;i++) {
		fac[i]=(LL)fac[i-1]*(LL)i%r;
		inv[i]=(LL)(r-r/i)*(LL)inv[r%i]%r;
	}
	for (int i=2;i<=MAXN-5;i++) {
		if (v[i]==0) {
			v[i]=i;
			prime[++cnt]=i;
			isPrime[i]=1;
		}
		for(int j=1;j<=cnt&&prime[j]<=v[i]&&i*prime[j]<=MAXN-5;j++) {
			v[i*prime[j]]=prime[j];
		}
	}
	for (int i=2;i<=MAXN-5;i++) {
		if (isPrime[i]) {
			ans[i]=(LL)ans[i-1]*(LL)(i-1)%r*(LL)inv[i]%r;
		} else {
			ans[i]=ans[i-1];
		}
	}
	while(t--) {
		scanf("%lld%lld", &n, &m);
		printf("%lld\n", (LL)fac[n]*(LL)ans[m]%r);
	}
	return 0;
}
