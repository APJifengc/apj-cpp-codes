#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL w[7],n,m,p,pp[15],pc[15],pk[15],pcnt;
namespace ExLucas {
	void split() {
		LL t=p;
		for(LL i=2;i<=sqrt(p);i++) {
			if (t%i==0) {
				pcnt++;
				pp[pcnt]=i;
				pk[pcnt]=1;
				while(t%i==0) {
					t/=i;
					pk[pcnt]*=i;
					pc[pcnt]++;
				}
			}
		}
		if (t>1) {
			pcnt++;
			pp[pcnt]=t;
			pk[pcnt]=t;
			pc[pcnt]=1;
		}
	}
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
	LL fac(LL n,LL pk,LL p) {
		if (n==0) return 1;
		LL ans=1;
		for(LL i=1;i<pk;i++) {
			if (i%p) {
				ans=ans*i%pk;			
			}
		}
		ans=qpow(ans, n/pk, pk);
		for(LL i=1;i<=n%pk;i++) {
			if (i%p) {
				ans=ans*i%pk;
			}
		}
		LL ret = fac(n/p, pk, p) * ans % pk;
		//printf("fac(%lld,%lld,%lld)=%lld;\n", n, pk, p, ret);
		return ret;
	}
	LL calc(LL n, LL w[], LL wcnt, LL pk, LL p) {
		LL cnt=0;
		//printf("%lld find p=%lld count:\n", n, p);
		for(LL i=n;i;i/=p) {
			//printf("%lld: cnt %lld\n", i, i/p);
			cnt+=i/p;
		}
		for(LL i=1;i<=wcnt;i++) {
			//printf("%lld find p=%lld count:\n", w[i], p);
			for(LL j=w[i];j;j/=p) {
				//printf("%lld: cnt %lld\n", j, j/p);
				cnt-=j/p;
			}
		}
		LL ans=fac(n, pk, p)*qpow(p, cnt, pk)%pk;
		for(LL i=1;i<=wcnt;i++) ans=ans*inv(fac(w[i], pk, p), pk)%pk;
		//printf("calc(%lld, w[], %lld, %lld, %lld)=%lld;\n", n, wcnt, pk, p, ans);
		return ans;
	}
}
LL a[15];
int main() {
	scanf("%lld%lld%lld", &p, &n, &m);
	for(LL i=1;i<=m;i++) scanf("%lld", &w[i]);
	m++;
	w[m]=n;
	for(LL i=1;i<m;i++) w[m]-=w[i];
	if (w[m]<0) {
		printf("Impossible\n");
		return 0;
	}
	ExLucas::split();
	//for(LL i=1;i<=pcnt;i++) printf("P(%lld): %lld^%lld=%lld\n", i, pp[i], pc[i], pk[i]);
	for(LL i=1;i<=pcnt;i++) a[i]=ExLucas::calc(n, w, m, pk[i], pp[i]);
	//for(LL i=1;i<=pcnt;i++) printf("{x≡ %lld (mod %lld)\n", a[i], pk[i]);
	printf("%lld\n", ExLucas::CRT(a, pk, p, pcnt));
	return 0;
}
