#include <bits/stdc++.h>
#define lowbit(a) (a&(-a))
using namespace std;
const int MAXN = 1e5+5;
int n;
int w[MAXN];
struct TreeArray {
	int a[MAXN];
	TreeArray(){
		memset(a, 0, sizeof(0));
	}
	void add(int i,int d) {
		while(i<=n) {
			a[i]+=d;
			i+=lowbit(i);
		}
	}
	void addArea(int i,int j,int d) {
		add(i,d);
		add(j+1,-d);
	}
	int query(int i) {
		int res=0;
		while(i) {
			res+=a[i];
			i-=lowbit(i);
		}
		return res;
	}
}tr;
int main() {
	scanf("%d", &n);
	for (int i=1; i<=n; i++) scanf("%d", &w[i]);
	for (int i=1; i<=n; i++) tr.add(i, w[i]-w[i-1]);
	int m;
	scanf("%d", &m);
	while(m--) {
		char op[7];
		scanf("%s", op);
		switch (op[0]) {
			case 'A':
				int i,j,d;
				scanf("%d%d%d", &i, &j, &d);
				tr.addArea(i, j, d);
				break;
			case 'Q':
				int s;
				scanf("%d", &s);
				printf("%d\n", tr.query(s));
				break;
		}
	}
}
