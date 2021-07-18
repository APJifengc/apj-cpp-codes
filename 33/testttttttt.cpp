#include <bits/stdc++.h>
using namespace std;
bool a[1000];
int step[1000];
int all, tru;
void dfs(int n,int k,int p, bool fa) {
	if (k==0) {
		if (fa) {
			all++;
			tru++;
			printf("% 2d: V ", all);
			for(int j=p;j>=1;j--) printf("%d ", step[j]); puts("");
		} else {
			all++;
			printf("% 2d: X ", all);
			for(int j=p;j>=1;j--) printf("%d ", step[j]); puts("");
		}
		return;
	}
	for(int i=1;i<=n;i++) {
		int l=i;
		while(a[l] && l<=n) l++;
		if (l==n+1) {
			step[k]=i;
			dfs(n, k-1, p, false);
		}
		else {
			a[l]=1;
			step[k]=i;
			dfs(n, k-1, p, fa);
			a[l]=0;
		}
	}
}
int qpow(int a,int b) {
	int ans=1;
	while(b) {
		if (b&1) ans*=a;
		a*=a;
		b>>=1;
	}
	return ans;
}
int main() {
	while(1) {
		int n,k;
		all=0,tru=0;
		cin >> k >> n;
		dfs(n,k,k,true);
		printf("%d/%d\n", tru, all);
	}
	return 0;
}
