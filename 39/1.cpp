#include <bits/stdc++.h>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
#define int long long
using namespace std;
const int MAXN = 1e6+5;
int n,m,r,v[MAXN];
struct Graph {
    int fst[MAXN],nxt[MAXN<<1],to[MAXN<<1],tot;
    void add(int u,int v) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
    }
}g;
int startPos[MAXN],endPos[MAXN],dfsNo,revStartPos[MAXN];
struct SegmentTree {
    int l,r,value;
    SegmentTree *lc,*rc;
    SegmentTree(int l_,int r_):l(l_),r(r_){
        if (l==r) {
            value=v[revStartPos[l]];
            //printf("%lld~%lld:%lld\n",l,r,value);
            return;
        }
        int mid=this->mid();
        lc = new SegmentTree(l, mid);
        rc = new SegmentTree(mid+1, r);
        value=lc->value+rc->value;
        //printf("%lld~%lld:%lld\n",l,r,value);
    }
    void add(int i,int d) {
        if (l==r) value+=d;
        else {
            int mid = this->mid();
            if (i<=mid) lc->add(i,d);
            else rc->add(i,d);
            value=lc->value+rc->value;
        }
    }
    int query(int i,int j) {
        if (j<l||i>r) return 0;
        else if (i<=l&&r<=j) return value;
        else return lc->query(i,j)+rc->query(i,j);
    }
    inline int mid() { return (l+r)>>1; }
    inline int length() { return r-l+1; }
};
void dfs(int i,int pre) {
    startPos[i]=++dfsNo;
    revStartPos[dfsNo]=i;
    forGraph(g,i,v,edge) if (v!=pre) dfs(v,i);
    endPos[i]=dfsNo;
}
signed main() {
    scanf("%lld%lld%lld", &n, &m, &r);
    for(int i=1;i<=n;i++) scanf("%lld", &v[i]);
    for(int i=1;i<n;i++) {
        int x,y;
        scanf("%lld%lld", &x, &y);
        g.add(x,y);
        g.add(y,x);
    }
    dfs(r,r);
    //for(int i=1;i<=n;i++) printf("p %lld:%lld~%lld\n", i, startPos[i], endPos[i]);
    SegmentTree tree = SegmentTree(1,n);
    for(int i=1;i<=m;i++) {
        int op;
        scanf("%lld", &op);
        if (op==1) {
            int a,x;
            scanf("%lld%lld", &a, &x);
            tree.add(startPos[a],x);
        } else {
            int a;
            scanf("%lld", &a);
            printf("%lld\n", tree.query(startPos[a],endPos[a]));
        }
    }
    return 0;
}
