#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 100005;
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
	if (!b) d=a,x=1,y=0;
	else {
		exgcd(b, a%b, d, x, y);
		LL t=x;x=y;y=t-(a/b)*y;
	}
}
LL gcd(LL a,LL b) {
	return b==0?a:gcd(b,a%b);
}
LL a,m;
LL aa[MAXN], mm[MAXN];
LL n;
LL multiMod(LL a,LL b,LL p) {
	//printf("%lld*%lld=", a,b);
	LL ans=0,w=1;
	if (b<0) {
		b*=-1,w=-1;
	}
	while(b) {
		if (b&1) ans=(ans+a)%p;
		a=(a+a)%p;
		b>>=1;
	}
	//printf("%lld\n", ans*w);
	return ans*w;
}
bool cmp(pair<int,int> a,pair<int,int> b) {
	return a.first!=b.first?a.first>b.first:a.second<b.second;
}
pair<int,int> pairs[MAXN];
int main() {
	while(scanf("%lld", &n) != EOF) {
		for(int i=1;i<=n;i++) scanf("%lld%lld", &mm[i], &aa[i]);
		for(int i=1;i<=n;i++) pairs[i]=make_pair(aa[i],mm[i]);
		sort(pairs+1,pairs+1+n,cmp);
		n = unique(pairs+1,pairs+1+n) - pairs -1;
		for(int i=1;i<=n;i++) aa[i]=pairs[i].first,mm[i]=pairs[i].second;
		//for(int i=1;i<=n;i++) printf("(%d)%lld %lld\n", i,aa[i],mm[i]);
		a=aa[1],m=mm[1];
		for(int i=2;i<=n;i++) {
			if (a<aa[i]) swap(a,aa[i]),swap(m,mm[i]);
			LL c=a-aa[i],d=gcd(m,mm[i]);
			if (c%d!=0) {
				//printf("a=%lld, aa[%d]=%lld, c=%lld, d=%lld\n",a, i,aa[i], c, d);
				printf("-1\n");
				goto next;
			}
			else {
				LL ap=m/d,bp=mm[i]/d,cp=c/d;
				LL x,y,dp;
				exgcd(ap,bp,dp,x,y);
				//printf("%lldx+%lldy=%lld -> %lldx'+%lldy'=1, x'=%lld,y'=%lld, c'=%lld, x0=%lld, y0=%lld\n", 
				//		m, mm[i], c, ap, bp, 
				//		x, y, cp, x*cp, y*cp);
				LL mod = m/d*mm[i];
				LL X = a-multiMod(m,x*cp,mod);
				X = (X%mod+mod) % mod;
				a=X,m=mod;
				//printf("(% 3d)x = %lld (mod %lld)\n",i,a,m);
			}
		}
		printf("%lld\n", a);
next:
		continue;
	}
	return 0;
}
