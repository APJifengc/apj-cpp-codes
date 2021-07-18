#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 5000;
LL f[MAXN][MAXN];
LL n,p;
int main() {
	scanf("%lld%lld", &n, &p);
	f[1][1]=1;
	for(int i=2;i<=n;i++) {
		f[i][1]=f[i-1][i-1];
		for(int j=2;j<=i;j++) {
			f[i][j]=(f[i][j-1]+f[i-1][i-j])%p;
		}
	}
	printf("%lld\n", f[n][n]*2%p);
	return 0;
}
