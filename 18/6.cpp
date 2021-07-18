#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int m,n,a[MAXN];
struct SegmentTree {
	int l,r,v,mm,ml,mr,lm,lr,rm,rl;
	SegmentTree *lc, *rc;
	SegmentTree(int l_,int r_):l(l_),r(r_){
		if (l==r) {
			v=a[l],mm=v,lm=v,rm=v,ml=l,mr=r,lr=r,rl=l;
			return;
		}
		int mid = this->mid();
		lc=new SegmentTree(l,mid);
		rc=new SegmentTree(mid+1,r);
		pushUp();
	}
	SegmentTree(){}
	inline int mid() {return (l+r)>>1;}
	inline int length() {return r-l+1;}
	inline void pushUp() {
		int mm1=lc->mm,mm2=rc->mm,mm3=lc->rm+rc->lm;
		if (mm1>=mm2) {
			if (mm1>=mm3) {
				mm=mm1,ml=lc->ml,mr=lc->mr;
			} else {
				mm=mm3,ml=lc->rl,mr=rc->lr;
			}
		} else {
			if (mm2>mm3) {
				mm=mm2,ml=rc->ml,mr=rc->mr;
			} else {
				mm=mm3,ml=lc->rl,mr=rc->lr;
			}
		}
		if (lc->lm>=lc->v+rc->lm) {
			lm=lc->lm,lr=lc->lr;
		} else {
			lm=lc->v+rc->lm,lr=rc->lr;
		}
		if (rc->rm>=rc->v+lc->rm) {
			rm=rc->rm,rl=rc->rl;
		} else {
			rm=rc->v+lc->rm,rl=lc->rl;
		}
		v=lc->v+rc->v;
	}
	SegmentTree* query(int i,int j) {
		if (i<=l && j>=r) {
			return this;	
		} else if (i<=r && j>=l){
			SegmentTree *lc = this->lc->query(i,j);
			SegmentTree *rc = this->rc->query(i,j);
			if (!lc) {
				return rc;
			} else if (!rc) {
				return lc;
			} else {
				SegmentTree *t = new SegmentTree();
				int mm1=lc->mm,mm2=rc->mm,mm3=lc->rm+rc->lm;
				if (mm1>=mm2) {
					if (mm1>=mm3) {
						t->mm=mm1,t->ml=lc->ml,t->mr=lc->mr;
					} else {
						t->mm=mm3,t->ml=lc->rl,t->mr=rc->lr;
					}
				} else {
					if (mm2>mm3) {
						t->mm=mm2,t->ml=rc->ml,t->mr=rc->mr;
					} else {
						t->mm=mm3,t->ml=lc->rl,t->mr=rc->lr;
					}
				}
				if (lc->lm>=lc->v+rc->lm) {
					t->lm=lc->lm,t->lr=lc->lr;
				} else {
					t->lm=lc->v+rc->lm,t->lr=rc->lr;
				}
				if (rc->rm>=rc->v+lc->rm) {
					t->rm=rc->rm,t->rl=rc->rl;
				} else {
					t->rm=rc->v+lc->rm,t->rl=lc->rl;
				}
				t->v=lc->v+rc->v;
				return t;
			}	
		}
		return NULL;
	}
};
int main() {
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++) scanf("%d", &a[i]);
	SegmentTree tree = SegmentTree(1,n);
	while(m--) {
		int a,b;
		scanf("%d%d", &a, &b);
		SegmentTree *q = tree.query(a,b);
		printf("%d %d %d\n", q->ml, q->mr, q->mm);
	}
	return 0;
}
