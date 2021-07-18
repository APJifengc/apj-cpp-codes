#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 15;
LL m[MAXN], a[MAXN], M=1, n;
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
	if (!b) d=a,x=1,y=0;
	else {
		exgcd(b, a%b, d, x, y);
		LL t=x;x=y;y=t-(a/b)*y;
	}
}
int main() {
	LL a,b,m;
	while(cin >> a >> b >> m) {
		LL x,y,d;
		exgcd(a,m,d,x,y);
		if (b%d!=0) printf("no\n");
		else printf("x=%lld y=%lld\n", x*(b/d),y*(b/d));
	}
	return 0;
}
