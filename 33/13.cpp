#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL gcd(LL a,LL b) {
	return b==0?a:gcd(b,a%b);
}
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
	if (!b) d=a,x=1,y=0;
	else {
		exgcd(b, a%b, d, x, y);
		LL t=x;x=y;y=t-(a/b)*y;
	}
}
LL equiv(LL a,LL b,LL p) {
	LL d,x,y;
	exgcd(a, p, d, x, y);
	//printf("equiv(%lld, %lld, %lld)=%lld;\n", a, b, p, (x*(b/d)%(p/d)+(p/d))%(p/d));
	if (b%d==0) return (x*(b/d)%(p/d)+(p/d))%(p/d);
	return 0;
}
LL inv(LL a,LL p) {
	LL ret = equiv(a, 1, p);
	//printf("inv(%lld, %lld)=%lld\n", a, p, ret);
	return ret;
}
LL CRT(LL a[], LL m[], LL M, LL cnt) {
	//printf("CRT(a[], m[], %lld, %lld)\n", M, cnt);
	LL ans=0;
	for(LL i=1;i<=cnt;i++) {
		LL Mi = M / m[i];
		ans = (ans + Mi*a[i]%M*inv(Mi,m[i])%M)%M;
		//printf("%lld*%lld*%lld\n", Mi, a[i], inv(Mi, m[i]));
	}
	return ans;
}
LL qpow(LL a,LL b,LL p) {
	LL t=b,q=a;
	LL ans=1;
	while(b) {
		if (b&1) ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	//printf("qpow(%lld, %lld, %lld)=%lld\n", q, t, p, ans);
	return ans;
}
LL fac[40006],inv_fac[40006];
LL pre(LL p) {
	fac[0]=fac[1]=1,inv_fac[0]=1;
	for(int i=2;i<p;i++) fac[i]=fac[i-1]*i%p;
	inv_fac[p-1]=qpow(fac[p-1], p-2, p);
	for(int i=p-2;i;i--) inv_fac[i]=inv_fac[i+1]*(i+1)%p;
}
LL C(LL n,LL m,LL p) {
	if (m>n) return 0;;
	return fac[n]*inv_fac[m]%p*inv_fac[n-m]%p;
}
LL Lucas(LL n,LL m,LL p) {
	if (m==0) return 1;
	return Lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;
}
LL ints[100000],intcnt;
LL solve(LL n,LL p) {
	LL ans=0;
	pre(p);
	//printf("mod %lld\n", p);
	//for(int i=1;i<=10;i++) printf("fac%d %lld %lld\n", i, fac[i], inv_fac[i]);
	for(LL i=1;i<=intcnt;i++) {
		//printf("C(%lld,%lld)mod%lld=%lld\n", n, i, p, Lucas(n,i,p));
		ans=(ans+Lucas(n,ints[i],p))%p;
	}
	return ans;
}
const int P = 999911659;
LL n,g,m[5]={0,2,3,4679,35617},a[5];
int main() {
	scanf("%lld%lld", &n, &g);
	for(int i=1;i<=sqrt(n);i++) {
		if (n%i==0) {
			ints[++intcnt]=i;
			if (i*i!=n) ints[++intcnt]=n/i;
		}
	}
	for(LL i=1;i<=4;i++) a[i]=solve(n, m[i]);
	//for(LL i=1;i<=4;i++) printf("{x=%lld(mod %lld)\n", a[i], m[i]);
	LL q=CRT(a,m,P-1,4);
	//printf("%lld\n", q);
	printf("%lld\n", qpow(g, q, P));
	return 0;
}
