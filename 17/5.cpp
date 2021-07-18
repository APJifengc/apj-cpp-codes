#include <bits/stdc++.h>
using namespace std;
const int MAXN=100005, MAXM=100005;
int n,m;
struct TreeArray {
	int a[MAXN];
	TreeArray() {
		memset(a, 0, sizeof(a));
	}
	void add(int i, int d) {
#define lowbit(a) (a&(-a))
		while(i<=n) {
			a[i]^=d;
			i+=lowbit(i);
		}
	}
	int query(int i) {
		int res=0;
		while(i) {
			res^=a[i];
			i-=lowbit(i);
		}
		return res;
	}
	void set(int i, int d) {
		add(i, query(i)^query(i-1)^d);
	}
}tr;
int main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; i++) {
		int a;
		scanf("%d", &a);
		tr.add(i, a);
	}
	while(m--) {
		int k,x,y;
		scanf("%d%d%d", &k, &x, &y);
		if (k) {
			printf("%d\n", tr.query(y)^tr.query(x-1));
		} else {
			tr.set(x, y);
		}
	}
	return 0;
}
