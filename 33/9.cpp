#include <bits/stdc++.h>
#define P 1000000000
using namespace std;

struct BigInt {
	long long a[4000],t;
	BigInt() {
		memset(a,0,sizeof(a));
		t=1;
		a[1]=1;
	}
	void operator*=(int b) {
		int x=0;
		for(int i=1;i<=t;i++) {
			a[i]=a[i]*b+x;
			x=a[i]/P;
			a[i]%=P;
		}			
		while(x) {
			a[++t]=x%P;
			x/=P;
		}
	}
	void print() {
		printf("%lld", a[t]);
		for(int i=t-1;i>=1;i--) printf("%09lld", a[i]);
	}
};
int gcd(int a,int b) {
	return b==0?a:gcd(b,a%b);
}
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n,k;
		scanf("%d%d", &n, &k);
		if (n>k) {
			printf("0 1\n");
			continue;
		}
		int q=k-n+1;
		BigInt up,down;
		for(int i=1;i<=n;i++) {
			int g=gcd(q, k);
			q/=g;
			down*=(k/g);
		}
		up*=q;
		for(int i=1;i<n;i++) up*=(k+1);
		up.print();
		printf(" ");
		down.print();
		printf("\n");
	}
	return 0;
}
