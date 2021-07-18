#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 2005;
const int MAXT = 20005, MOD=10000;
struct BigInt {
	int a[MAXT],t;
	BigInt(LL v){
		memset(a,0,sizeof(a));
		if(v!=0) t=1,a[1]=v%MOD;
		else {
			t=0;
			return;
		}
		while(v/MOD!=0) {
			v/=MOD;
			a[++t]=v%MOD;
		}
	}
	BigInt(){
		memset(a,0,sizeof(a));
		t=0;
	}
	BigInt operator*(BigInt b) {
		if (t==0 || b.t==0) return BigInt();
		BigInt c = BigInt();
		c.t = t+b.t-1;
		for(int i=1;i<=t;i++) {
			int x=0;
			for(int j=1;j<=b.t;j++) {
				c.a[i+j-1]+=a[i]*b.a[j]+x;
				x=c.a[i+j-1]/MOD;
				c.a[i+j-1]%=MOD;
			}
			if (x!=0) c.a[i+b.t]+=x;
		}
		while(c.a[c.t+1]!=0) c.t++;
		return c;
	}
	BigInt operator*(int b) {
		return (*this)*BigInt(b);
	}
	BigInt operator-(BigInt b) {
		BigInt c = BigInt();
		int k = max(b.t, t);
		int x=0;
		for(int i=1;i<=k;i++) {
			c.a[i]=a[i]-b.a[i]-x;
			if (c.a[i]<0) x=1,c.a[i]+=MOD;
			else x=0;
		}
		for(int i=k;i>=1;i--) if (c.a[i]!=0) {
			c.t=i;
			break;
		}
		return c;
	}
	void print() {
		printf("%d", a[t]);
		for(int i=t-1;i>=1;i--) printf("%04d", a[i]);
		printf("\n");
	}
}a(5);
LL m,n;
int main() {
	scanf("%lld%lld", &n, &m);
	BigInt ans1 = BigInt(1), ans2 = BigInt(2);
	for(int i=n+2;i>=1;i--) ans1=ans1*i;
	for(int i=n+3;i>=n+3-m+1;i--) ans1=ans1*i;
	for(int i=n+1;i>=1;i--) ans2=ans2*i;
	for(int i=n+2;i>=n+2-m+1;i--) ans2=ans2*i;
	(ans1-ans2).print();
	return 0;
}
