#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 1e6+5;
LL n,p;
LL fac[MAXN],inv[MAXN],size[MAXN];
LL qpow(LL a,LL b) {
	LL ans=1;
	while(b) {
		if(b&1) ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
LL C(int n,int m) {
	if (m>n) return 0;
	return fac[n]*inv[m]%p*inv[n-m]%p;
}
LL Lucas(int n,int m) {
	if (m==0) return 1;
	return Lucas(n/p,m/p)*C(n%p,m%p)%p;
}
LL f(int i) {
	if (i>n) return 1;
	if ((i<<1|1)>n) return f(i<<1)*(max(size[i]-1, 1LL))%p;
	return f(i<<1)*f(i<<1|1)%p*Lucas(size[i]-1, size[i]-1-size[i<<1])%p;
}
LL dfs(int i) {
	if ((i<<1)<=n) size[i]+=dfs(i<<1);
	if ((i<<1|1)<=n) size[i]+=dfs(i<<1|1);
	size[i]++;
	return size[i];
}
int main() {
	scanf("%lld%lld", &n, &p);
	fac[1]=1,inv[0]=1;
	for(int i=2;i<MAXN;i++) fac[i]=fac[i-1]*i%p;
	LL q=min(p-1, (LL)MAXN-5);
	inv[q]=qpow(fac[q], p-2);
	for(int i=q-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%p;
	dfs(1);
	printf("%lld\n", f(1));
	return 0;
}
