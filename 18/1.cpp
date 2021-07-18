#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int a[MAXN];
struct SegmentTree {
	int l,r,v;
	SegmentTree *lc,*rc;
	SegmentTree(int l_,int r_):l(l_),r(r_),v(0){
		if (l_==r_) {
			v = a[l_];
			return;
		}
		int mid = (l_+r_)/2;
		lc = new SegmentTree(l_, mid);
		rc = new SegmentTree(mid+1, r_);
		v = lc->v+rc->v;
	}
	int sum(int l, int r) {
		if (l<=this->l && r>=this->r) {
			return v;
		} else if (r>=this->l && l<=this->r) {
			int an = lc->sum(l,r) + rc->sum(l,r);
			return an;
		} else return 0;
	}
	void add(int k, int d) {
		v += d;
		if (l==r) return;
		int mid = (l+r)/2;
		if (k<=mid) lc->add(k,d);
		else rc->add(k,d);
	}
	void set(int k, int d) {
		add(k, a[k]-d);
	}
};
int n;
int main() {
	scanf("%d", &n);
	if (n==0) return 0;
	for(int i=1; i<=n; i++) scanf("%d", &a[i]);
	SegmentTree tree = SegmentTree(1, n);
	char op[5];
	int m;
	scanf("%d", &m);
	while(m--) {
		int x,y;
		scanf("%s%d%d", op, &x, &y);
		if (op[0]=='S') {
			printf("%d\n", tree.sum(x, y));
		} else {
			tree.add(x, y);
		}
	}
	return 0;
}
