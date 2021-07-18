#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 21000005;
LL a[MAXN];
int                n ;
int phi[MAXN];
LL phif(LL n) {
	int ans = n;
	for (int i=2; i<=sqrt(n); i++) {
		if (n%i==0) {
			ans = ans / i * (i-1);
			while(n%i==0) n/=i;
		}
	}
	if (n>1) ans = ans/n*(n-1);
	return ans;
}
int prime[MAXN],cnt;
int main() {
	scanf("%d", &n);
	phi[1]=1;
	for(int i=2;i<=n;i++) {
		if (a[i] == 0) {
			a[i]=i,prime[++cnt]=i;
		}
		for(int j=1;j<=cnt&&i*prime[j]<=n&&prime[j]<=a[i];j++) {
			a[i*prime[j]]=prime[j];
		}
	}
	/*for(int i=1; i<=n; i++) {
		if (phi[i]!=phif(i)) {
			printf("phi(%d) %dx %lldv\n", i, phi[i], phif(i));
		}
	}*/
	return 0;
}
