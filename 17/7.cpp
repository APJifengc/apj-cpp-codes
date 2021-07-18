#include <bits/stdc++.h>
#define lowbit(a) (a&(-a))
using namespace std;
const int MAXN=305,MAXC=105;
int n,m,q;
struct TreeArray {
	int a[MAXN][MAXN];
	TreeArray() {
		memset(a,0,sizeof(a));
	}
	int query(int i,int j) {
		int res = 0;
		while(i) {
			int t=j;
			while(t) {
				res+=a[i][t];
				t-=lowbit(t);
			}
			i-=lowbit(i);
		}
		return res;
	}
	void add(int i,int j,int d) {
		while(i<=n) {
			int t=j;
			while(t<=m) {
				a[i][t]+=d;
				t+=lowbit(t);
			}
			i+=lowbit(i);
		}
	}
	int queryArea(int i,int j,int x,int y) {
		return query(x,y)-query(i-1,y)-query(x,j-1)+query(i-1,j-1);
	}
}tr[MAXC];
int g[MAXN][MAXN];
int main() {
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			scanf("%d", &g[i][j]);
			tr[g[i][j]].add(i,j,1);
		}
	}
	scanf("%d", &q);
	while(q--) {
		int k;
		scanf("%d", &k);
		if (k==1) {
			int x,y,c;
			scanf("%d%d%d", &x, &y, &c);
			tr[g[x][y]].add(x,y,-1);
			tr[c].add(x,y,1);
			g[x][y]=c;
		}
		if (k==2) {
			int x1,y1,x2,y2,c;
			scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &c);
			printf("%d\n", tr[c].queryArea(x1,y1,x2,y2));
		}
	}
	return 0;
}
