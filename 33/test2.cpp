#include <bits/stdc++.h>
using namespace std;
int a[1000];
bool b[1000];
int n,S;
int ans;
int f[1000000],prime[1000000],cnt;
void dfs(int m, int step) {
	if (m==0) {
		ans++;
		printf("% 3d: ", ans);
		for(int i=1;i<=step-1;i++) printf("%d ", a[i]);
		printf("\n");
	}
	if (m<0) return;
	for(int i=1;i<=cnt&&prime[i]<=a[step-1];i++) {
		a[step]=prime[i];
		dfs(m-prime[i], step+1);
	}
}

int main() {
	a[0]=INT_MAX;	
	cin >> S;
	cnt=0;
	for(int i=2;i<=S;i++) {
		if (S%i==0) {
			prime[++cnt]=i;
			printf("%dprime: %d\n",cnt,i);
			while(S%i==0) S/=i;
		}
	}

	while(1) {
		cin >> n;
		memset(a,0,sizeof(a));
		a[0]=INT_MAX;
		ans=0;
		memset(f,0,sizeof(f));
		
		for(int i=1;i<=cnt;i++) {
			f[prime[i]]++;
			for(int j=1;j<=n;j++) {
				if (j>=prime[i])
					f[j]+=f[j-prime[i]];
			}
		}
		if (n<=100) for(int i=1;i<=n;i++) printf("% 3d: %d\n", i, f[i]);
		else printf("%d\n", f[n]);
		//dfs(n, 1);
		//printf("ans:%d\n", ans);
	}
	return 0;
}
