#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 100005;
LL a[MAXN];
struct SegmentTree {
	int l,r;
	LL v,lazy;
	SegmentTree *lc, *rc;
	SegmentTree(int l_, int r_):l(l_),r(r_),lazy(0){
		if (l_==r_) {
			v = a[l_];
			return;
		}
		int mid = this->mid();
		lc = new SegmentTree(l, mid);
		rc = new SegmentTree(mid+1, r);
		v = lc->v+rc->v;	
	}
	inline int length() {
		return r-l+1;
	}
	inline int mid() {
		return (l+r)/2;
	}
	inline void pushDown() {
		if (lazy) {
			lc->lazy += lazy;
			rc->lazy += lazy;
			lc->v += lc->length()*lazy;
			rc->v += rc->length()*lazy;
			lazy=0;
		}
	}
	LL query(int l,int r) {
		if (this->l!=this->r) pushDown();
		if (l<=this->l && r>=this->r) {
			return v;
		} else if (l<=this->r && r>=this->l) {
			return lc->query(l,r)+rc->query(l,r);
		}
		return 0;
	}
    void addArea(int l,int r,LL d)  {
		if (l>this->r || r<this->l) return;
		if (l<=this->l && r>=this->r) {
			lazy+=d;
			v+=length()*d;
			return;
		}
		/*if (this->l==this->r) {
			v+=d;
			return;
	 	}*/
		int mid=this->mid();
		pushDown();
		lc->addArea(l, r, d);
		rc->addArea(l, r, d);
		v = lc->v+rc->v;
	}
};
int n,m;
SegmentTree *t;
int main() {
	scanf("%d", &n);
	for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
	SegmentTree tree = SegmentTree(1,n);
	t = &tree;
	scanf("%d", &m);
	char op[5];
	while(m--) {
		int i,j;
		scanf("%s%d%d", op, &i, &j);
		if (op[0] == 'A') {
			LL d;
			scanf("%lld", &d);
			tree.addArea(i,j,d);
		} else {
			printf("%lld\n", tree.query(i, j));
		}	
	}
	return 0;
}
