#include <bits/stdc++.h>
#define LL long long
using namespace std;
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
	if (!b) d=a,x=1,y=0;
	else {
		exgcd(b, a%b, d, x, y);
		LL t=x;x=y;y=t-(a/b)*y;
	}
}
LL a,b;
int main() {
	scanf("%lld%lld", &a, &b);
	if (a==b) {
		printf("%lld\n0 1\n", a);
		return 0;
	}
	LL d,x,y;
	exgcd(b,a,d,x,y);
	LL x1 = (x%(a/d)+a/d)%(a/d);
	LL t=x1-x;
	LL y1=y-(b/d)*t;
	//printf("x0=%lld,y0=%lld,d=%lld,t=%lld,x1=%lld,y1=%lld\n", x,y,d,t,x1,y1);
	printf("%lld\n%lld %lld\n", d, b*x1/a,x1);
	return 0;
}
