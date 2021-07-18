#include <bits/stdc++.h>
using namespace std;
long long n,p,a[3000005];
int main() {
	scanf("%lld%lld", &n, &p);
	printf("1\n");a[1]=1;
	for(int i=2;i<=n;i++) printf("%lld\n", a[i]=a[p%i]*(p-p/i)%p);
	return 0;
}
