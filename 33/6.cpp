#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXS = 2000005, P = 1000000007;
int prime[10], primeCnt;
int inv[11] = {0,1,500000004,166666668,41666667,808333339,301388891,900198419,487524805,831947206,283194722};
int s, q;
LL n;
LL C(LL n, int m) {
	if (n<m) return 0;
	LL ans=1;
	for(LL i=n;i>n-m;i--) ans=ans*(i%P)%P;
	//printf("C(%lld,%d)=%lld\n", n, m, ans*inv[m]%P);
	return ans*inv[m]%P;
}
LL f[2][7*MAXS];
LL ans;
int main() {
	scanf("%d%d", &s, &q);
	int t=s;
	for(int i=2;i<=s;i++) {
		if (s%i==0) {
			prime[++primeCnt] = i;
			//printf("%d: %d\n", primeCnt, i);
			s/=i;
			if (s%i==0) {
				while(q--) puts("0");
				return 0;
			}
		}
	}	
	s=t;
	f[1][0]=1;
	int V = primeCnt*s,ptr=0;
	for(int i=1;i<=primeCnt;i++,ptr^=1) {
		memcpy(f[ptr], f[ptr^1], sizeof(f[ptr]));
		for(int j=0;j<=V;j++) {
			if (j>=prime[i]) f[ptr][j]=(f[ptr][j]+f[ptr][j-prime[i]])%P;
			if (j>=s) f[ptr][j]=(f[ptr][j]+P-f[ptr^1][j-s])%P;
			//printf("f[%d][%d]=%lld (prime[%d]=%d)\n", ptr, j, f[ptr][j], i, prime[i]);
		}
	}
	while(q--) {
		scanf("%lld", &n);
		for(int i=1;i<=primeCnt;i++) n-=prime[i];
		if (n<0) {
			puts("0");
			continue;
		}
		ans=0;
		for(int i=n%s;i<=V&&i<=n;i+=s) {
			//printf("f[%d]=%lld\n", i, f[ptr^1][i]);
			ans=(ans + C((n-i)/s+primeCnt-1, primeCnt-1) * f[ptr^1][i]) % P;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
