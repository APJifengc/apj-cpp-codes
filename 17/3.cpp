#include <bits/stdc++.h>
using namespace std;
const int MAXN=50005, MAXM=200005, MAXC=1000005;
struct query {
	int l,r,id,ans;

}q[MAXM];
bool operator<(const query &a, const query &b) {
	return a.r<b.r;
}
bool cmp(const query &a, const query &b) {
	return a.id<b.id;
}
int n,m,a[MAXN];
int last[MAXC];
struct TreeArray{
	int a[MAXN];
	TreeArray(){
		memset(a, 0, sizeof(a));
	}
#define lowbit(a) (a&(-a))
	void add(int i, int d) {
		while(i<=n) {
			a[i]+=d;
			i+=lowbit(i);
		}
	}
	int query(int i) {
		int res=0;
		while(i){
			res+=a[i];
			i-=lowbit(i);
		}
		return res;
	}
}tr;
int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i=1; i<=m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id=i;
	}
	sort(q+1, q+1+m);
	int j=1;
	for(int i=1; i<=n; i++) {
#ifdef debug
		printf("i=%d\n", i);
#endif
		if (last[a[i]]) tr.add(last[a[i]],-1);
		tr.add(i,1);
		for(;i==q[j].r;j++) {
			q[j].ans=tr.query(i)-tr.query(q[j].l-1);
#ifdef debug
			printf("q[%d].ans=%d\n", j, q[j].ans);
#endif
		}
#ifdef debug
		for(int j=1;j<=n;j++) printf("%d ", tr.a[j]);
		printf("\n");
#endif
		last[a[i]]=i;
	}
	sort(q+1, q+1+m, cmp);
	for(int i=1; i<=m; i++) printf("%d\n", q[i].ans);
	return 0;
}

