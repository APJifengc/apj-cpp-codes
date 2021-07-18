#include <bits/stdc++.h>
using namespace std;
const int MAXN = 15;
double w[MAXN][MAXN],a[MAXN][MAXN];
int n;
int main() {
	scanf("%d", &n);
	for(int i=1;i<=n+1;i++) {
		for(int j=1;j<=n;j++) {
			scanf("%lf", &w[i][j]);
			a[i][j]=w[i][j];
			a[i][n+2]+=w[i][j]*w[i][j];
		}
		a[i][n+1]=1;
		a[i][n+2]/=2.0;
	}
	/*for(int p=1;p<=n+1;p++) {
		for(int q=1;q<=n+2;q++) {
			printf("% .2lf ", a[p][q]);
		}
		printf("\n");
	} printf("\n");*/
	for(int i=1;i<=n+1;i++) {
		int r=i;
		for(int j=i+1;j<=n+1;j++) {
			if (fabs(a[j][i])>fabs(a[r][i])) r=j;
		}
		if (i!=r) swap(a[i], a[r]);
		for(int j=1;j<=n+1;j++) {
			if (i!=j) {
				double mul = a[j][i]/a[i][i];
				for(int k=1;k<=n+2;k++) a[j][k]-=a[i][k]*mul;
			}
		}
	/*for(int p=1;p<=n+1;p++) {
		for(int q=1;q<=n+2;q++) {
			printf("% .2lf ", a[p][q]);
		}
		printf("\n");
	}printf("\n");*/
	}
	for(int i=1;i<=n;i++) printf("%.3lf ",a[i][n+2]/a[i][i]);
	puts("");
	return 0;
}
