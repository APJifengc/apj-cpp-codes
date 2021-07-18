#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 15;
LL m[MAXN], a[MAXN], M=1, n;
void exgcd(LL a,LL b,LL &x,LL &y) {
	if (!b) x=1,y=0;
	else {
		exgcd(b, a%b, x, y);
		LL t=x;x=y;y=t-(a/b)*y;
	}
}
int main() {
	scanf("%lld", &n);	
	for(int i=1;i<=n;i++) scanf("%lld%lld", &m[i], &a[i]);
	for(int i=1;i<=n;i++) M*=m[i];
	LL ans=0;
	for(int i=1;i<=n;i++) {
		LL Mi=M/m[i];
		LL x,y;
		exgcd(Mi,m[i],x,y);
		ans=(ans+Mi*a[i]*((x+m[i])%m[i]))%M;
	}
	printf("%lld\n", ans);
	return 0;
}
