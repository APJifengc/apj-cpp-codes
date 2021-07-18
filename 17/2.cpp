#include <bits/stdc++.h>
using namespace std;
#define lowbit(a) (a&(-a))
const int MAXN = 15005, MAXX=32005, MAXY=32005;
int n;
struct TreeArray {
	int a[MAXX];
	TreeArray() {
		memset(a,0,sizeof(a));
	}
	void add(int i,int d) {
		while(i<=MAXX) {
			a[i]+=d;
			i+=lowbit(i);
		}
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
int ans[MAXN];
int main() {
	scanf("%d", &n);
	for (int i=1; i<=n; i++) {
		int x,y;
		scanf("%d%d", &x, &y);
		x++,y++;
		ans[tr.query(x)]++;
		tr.add(x, 1);
#ifdef debug
		for(int j=1; j<=10; j++) cout << tr.a[j] << " ";
		cout << endl;
#endif
	}
	for (int i=0; i<n; i++) printf("%d\n", ans[i]);
	return 0;
}
