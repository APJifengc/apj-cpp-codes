#include <bits/stdc++.h>
using namespace std;
const int MAXN=50005;
int n,m;
struct TreeArray {
	int a[MAXN];
	TreeArray(){
		memset(a, 0, sizeof(a));
	}
	void add(int i, int d) {
#define lowbit(a) (a&(-a))
		while(i<=n) {
			a[i]+=d;
			i+=lowbit(i);
		}
	}
	int query(int i) {
		int res = 0;
		while(i) {
			res+=a[i];
			i-=lowbit(i);
		}
		return res;
	}
}tr1, tr2;
int main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=m; i++) {
		int k,l,r;
		scanf("%d%d%d", &k, &l, &r);
		if (k==1) {
			tr1.add(l,1);
			tr2.add(r,1);
		}
		if (k==2) {
			printf("%d\n", tr1.query(r)-tr2.query(l-1));
		}
	}
	return 0;
}
