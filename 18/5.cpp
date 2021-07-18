#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int a[MAXN],n,m;
struct SegmentTree {
	int l,r,v,lazy;
	SegmentTree *lc ,*rc;
	SegmentTree(int l_,int r_):r(r_),l(l_),lazy(0){
		if (l_==r_) {
			v=a[l_];
			return;
		}
		int mid = this->mid();
		lc = new SegmentTree(l, mid);
		rc = new SegmentTree(mid+1, r);
		v=lc->v+rc->v;
	}
	inline int mid() {
		return (l+r)>>1;
	}
	inline int length() {
		return r-l+1;
	}
	void pushDown() {
		if (lazy) {
			lc->lazy+=lazy;
			rc->lazy+=lazy;
			lc->v+=lc->length()*lazy;
			rc->v+=rc->length()*lazy;
			lazy=0;
		}
	}
	int query(int i) {
		if (this->l==this->r) return v;
		pushDown();
		int mid = this->mid();
		if (i<=mid) return lc->query(i);
		else return rc->query(i);
	}
	void addArea(int i,int j,int d) {
		if (i>r || j<l) return;
		if (i<=l && j>=r) {
			lazy+=d;
			v+=length()*d;
			return;
		}
		pushDown();
		lc->addArea(i,j,d);
		rc->addArea(i,j,d);
		v=lc->v+rc->v;
	}
};
int read() {
	int f=1,x=0;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
	return x*f;	
}
int main() {
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	SegmentTree tree = SegmentTree(1,n);
	m=read();
	char op[5];
	while(m--) {
		scanf("%s", op);
		if (op[0]=='A') {
			int i=read(),j=read(),d=read();
			tree.addArea(i,j,d);
		} else {
			printf("%d\n", tree.query(read()));
		}
	}
	return 0;
}
