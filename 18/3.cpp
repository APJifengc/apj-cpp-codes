#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
int a[MAXN],n,m;
struct SegmentTree {
	int l,r,v;
	SegmentTree *lc, *rc;
	SegmentTree(int l_, int r_):l(l_),r(r_){
		if (l_==r_) {
			v = a[l_];
			return;
		}
		int mid = (l+r)/2;
		lc = new SegmentTree(l_, mid);
		rc = new SegmentTree(mid+1, r_);
		v = min(lc->v, rc->v);
	}
	int query(int l,int r) {
		if (l<=this->l && r>=this->r) {
			return v;
		} else if (l<=this->r && r>=this->l) {
			return min(lc->query(l,r), rc->query(l,r));
		}
		return INT_MAX;
	}
};
int main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; i++) scanf("%d", &a[i]);
	SegmentTree tree = SegmentTree(1, n);
	while(m--) {
		int a,b;
		scanf("%d%d", &a,&b);
		printf("%d ", tree.query(a,b));
	}
	printf("\n");
	return 0;
}
