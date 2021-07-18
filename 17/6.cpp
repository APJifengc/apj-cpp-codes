#include <bits/stdc++.h>
using namespace std;
#define lowbit(a) (a&(-a))
const int MAXS = 1026;
int s;
struct TreeArray {
	int a[MAXS][MAXS];
	TreeArray() {
		memset(a, 0, sizeof(a));
	}
	int query(int i,int j) {
		int res=0;
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
		while(i<=s) {
			int t=j;
			while(t<=s) {
				a[i][t]+=d;
				t+=lowbit(t);
			}
			i+=lowbit(i);
		}
	}
	int queryArea(int x,int y,int a,int b) {
		return query(a,b)-query(x-1,b)-query(a,y-1)+query(x-1,y-1);
	}
}tr;
int main() {
	int k;
	while(1) {
		scanf("%d", &k);
		if (k==0) {
			scanf("%d", &s);
		}
		if (k==1) {
			int x,y,a;
			scanf("%d%d%d", &x, &y, &a);
			tr.add(x+1,y+1,a);
		}
		if (k==2) {
			int l,b,r,t;
			scanf("%d%d%d%d", &l, &b, &r, &t);
			printf("%d\n", tr.queryArea(l+1,b+1,r+1,t+1));
		}
		if (k==3) {
			break;
		}
	}
	return 0;
}
