#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
int a[MAXN],n;
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
		v = max(lc->v, rc->v);
	}
	int query(int l,int r) {
		if (l<=this->l && r>=this->r) {
			return v;
		} else if (l<=this->r && r>=this->l) {
			return max(lc->query(l,r), rc->query(l,r));
		}
		return 0;
	}
};
int main() {
	scanf("%d", &n);
	n++;
	for(int i=1; i<=n; i++) scanf("%d", &a[i]);
	int q;
	SegmentTree tree = SegmentTree(1, n);
	scanf("%d", &q);
	while(q--) {
		int a,b;
		scanf("%d%d", &a,&b);
		a++,b++;
		printf("%d\n", tree.query(a,b));
	}
	return 0;
}
