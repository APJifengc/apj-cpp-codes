#include <bits/stdc++.h>
#define LL long long
using namespace std;
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
	if (!b) d=a,x=1,y=0;
	else {
		exgcd(b,a%b,d,x,y);
		LL t=x;x=y;y=t-(a/b)*y;
	}
}
LL x,y,m,n,L;
int main() {
	scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L);
	LL d,x0,y0,a=n-m,b=x-y,c=L;
	exgcd(a, c,d,x0,y0);
	if (b%d==0) {
		printf("%lld\n", (x0*(b/d)%(c/d)+(c/d))%(c/d));
	} else {
		printf("Impossible\n");
	}
	return 0;
}
