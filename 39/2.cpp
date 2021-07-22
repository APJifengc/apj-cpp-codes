#include <bits/stdc++.h>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
#define int long long
using namespace std;
const int MAXN = 1e6+5;
int n,m,r,v[MAXN],revStartPos[MAXN],startPos[MAXN],endPos[MAXN],dfsNum;
struct Graph {
    int fst[MAXN],to[MAXN<<1],nxt[MAXN<<1],tot;
    void add(int u,int v) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
    }
}g;
int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}
struct SegmentTree {
    int l,r,value,lazy;
    SegmentTree *lc,*rc;
    SegmentTree(int l_,int r_):l(l_),r(r_),lazy(0){
        if (l==r) {
            value=v[revStartPos[l]];
            return;
        }
        int mid=this->mid();
        lc = new SegmentTree(l, mid);
        rc = new SegmentTree(mid+1, r);
        value=lc->value+rc->value;
    }
    void pushDown() {
        if (lazy) {
            lc->lazy+=lazy;
            rc->lazy+=lazy;
            lc->value+=lc->length()*lazy;
            rc->value+=rc->length()*lazy;
            lazy=0;
        }
    }
    int query(int i,int j) {
        if (i>r || j<l) return 0;
        if (i<=l && r<=j) return value;
        pushDown();
        return lc->query(i,j)+rc->query(i,j);
    }
    void addArea(int i,int j,int d) {
        if (i<=l && r<=j) {
            lazy+=d;
            value+=length()*d;
            return;
        }
        if (i>r || j<l) return;
        pushDown();
        int mid = this->mid();
        if (i<=mid) lc->addArea(i,j,d);
        if (j>mid) rc->addArea(i,j,d);
        value=lc->value+rc->value;
    }
    inline int mid() { return (l+r)>>1; }
    inline int length() { return r-l+1; }
};
void dfs(int i,int pre) {
    startPos[i]=++dfsNum;
    revStartPos[dfsNum]=i;
    forGraph(g,i,j,edge) if (j!=pre) dfs(j,i); 
    endPos[i]=dfsNum;
}
signed main() {
    n=read();m=read();r=read();
    for(int i=1;i<=n;i++) v[i]=read();
    for(int i=1;i<n;i++) {
        int x=read(),y=read();
        g.add(x,y);
        g.add(y,x);
    }
    dfs(r,r);
    SegmentTree tree = SegmentTree(1,n);
    for(int i=1;i<=m;i++) {
        int op=read();
        if (op==1) {
            int a=read(),x=read();
            tree.addArea(startPos[a], endPos[a], x);
        } else {
            int a=read();
            printf("%lld\n", tree.query(startPos[a],endPos[a]));
        }
    }
    return 0;
}
