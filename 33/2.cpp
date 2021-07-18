#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 20000;
const int MOD = 10007;
LL inv[MAXN],jc[MAXN],jc_inv[MAXN];
LL C(LL n,LL m) {
	return jc[n]*jc_inv[m]*jc_inv[n-m]%MOD;
}
LL Lucas(LL n, LL m)
{
	if(m == 0) return 1;
	return C(n % MOD, m % MOD) * Lucas(n / MOD, m / MOD) % MOD;
}
int main() {
	inv[1]=1,jc[1]=1,jc_inv[1]=1,jc_inv[0]=1;
	for(int i=2;i<10009;i++) {
		jc[i]=jc[i-1]*i%MOD;
		inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
		jc_inv[i]=jc_inv[i-1]*inv[i]%MOD;
	}
	int T;
	scanf("%d", &T);
	while(T--) {
		int n,m;
		scanf("%d%d", &n, &m);
		printf("%lld\n", Lucas(n,m));
	}
	return 0;
}
