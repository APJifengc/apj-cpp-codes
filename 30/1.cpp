#include <bits/stdc++.h>
#define MAXN 55
#define ZERO 1e-9
using namespace std;
double a[MAXN][MAXN],ans[MAXN];
bool infSol;
int n;
int main() {
	scanf("%d", &n);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n+1;j++) 
			scanf("%lf", &a[i][j]);
	int cur=0;
	for(int i=1;i<=n;i++) {
		cur++;
		if (cur > n) break;
		int r=i; // 寻找最大的系数
		for(int j=i+1;j<=n;j++) {
			if (fabs(a[j][cur])>fabs(a[r][cur])) r=j;
		}
		if (i!=r) swap(a[i],a[r]);
		if (fabs(a[i][cur])<ZERO) { // 检测系数是否为0
			for(int j=cur+1;j<=n;j++) {
				if (fabs(a[i][j])>=ZERO) { // 非空，无穷解
					infSol = 1;
					i--;
					goto next; 
				}
			}
			if (fabs(a[i][n+1])<ZERO) { // 0=0，无穷解，可能无解，先保存
				infSol = 1;
				i--;
				goto next;
			} else { // 0=d，无解
				printf("-1\n");
				return 0;
			}
		}
		// 消元
		for(int j=1;j<=n;j++) {
			if (i==j) continue;
			double mul = a[j][cur]/a[i][cur];
			for(int k=1;k<=n+1;k++) a[j][k]-=mul*a[i][k];
		}
next:
		continue;
	}
	for (int i=1;i<=n;i++) { // 检测是否无解
		bool empty=true;
		for (int j=1;j<=n;j++) {
			if (fabs(a[i][j])>ZERO) empty=false;
		}
		if (empty && fabs(a[i][n+1])>ZERO) { // 0=d
			printf("-1\n");
			return 0;
		} 
	}
	if (infSol) {
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++) {
		if (fabs(a[i][n+1])<ZERO) printf("x%d=0\n", i);
		else printf("x%d=%.2lf\n", i, a[i][n+1]/a[i][i]);
	}
	return 0;
}
