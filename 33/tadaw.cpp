#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXS = 2000005, P = 1000000007;
int prime[10], primeCnt;
int inv[11] = {0,1,500000004,166666668,41666667,808333339,301388891,900198419,487524805,831947206,283194722};
int s, q;
LL n;
LL C(LL n, int m) {
	LL ans=1;
	for(LL i=n;i>n-m;i--) ans=ans*i%P;
	return ans*inv[m]%P;
}
LL f[2][7*MAXS];
LL ans;
int main() {
	scanf("%d%d", &s, &q);
	for(int i=2;i<=s;i++) {
		if (s%i==0) {
			prime[++primeCnt] = i;
			printf("%d: %d\n", primeCnt, i);
			s/=i;
			if (s%i==0) {
				while(q--) puts("0 (not sfn)");
				return 0;
			}
		}
	}	
	f[0][0]=1;
	int V = primeCnt*s,ptr=0;
	for(int i=1;i<=primeCnt;i++,ptr^=1) {
		memcpy(f[ptr], f[ptr^1], sizeof(f[ptr]));
		for(int j=0;j<=V;j++) {
			if (j>=prime[i]) f[ptr][j]=(f[ptr][j]+f[ptr][j-prime[i]])%P;
			if (j>=s) f[ptr][j]=(f[ptr][j]+P-f[ptr^1][j-s])%P;
		}
	}
	memcpy(f[ptr], f[ptr^1], sizeof(f[ptr]));
	while(q--) {
		scanf("%lld", &n);
		for(int i=1;i<=primeCnt;i++) n-=prime[i];
		if (n<0) {
			puts("0 (n<0)");
			continue;
		}
		if (n==0) {
			puts("1 (n=0)");
			continue;
		}
		ans=0;
		for(int i=n%s;i<=V&&i<=n;i+=s) {
			ans=(ans + C((n-i)/s+primeCnt-1, primeCnt-1) * f[ptr][i]) % P;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
