#include <bits/stdc++.h>
#define int long long
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
using namespace std;
const int MAXN = 100005;
int n,q,v[MAXN],revStartPos[MAXN],startPos[MAXN],endPos[MAXN],dfsNum,rt;
struct Graph {
    int fst[MAXN],nxt[MAXN<<1],to[MAXN<<1],tot;
    void add(int u,int v) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
    }
}g;
struct SegmentTree {
    int l,r,value;
    SegmentTree *lc, *rc;
    SegmentTree(int l_,int r_):l(l_),r(r_) {
        if (l==r) {
            value=v[revStartPos[l]];
            return;
        }
        int mid = this->mid();
        lc = new SegmentTree(l, mid);
        rc = new SegmentTree(mid+1, r);
        value=min(lc->value,rc->value);
    }
    int query(int i,int j) {
        if (i>j) return LLONG_MAX;
        if (i>r||j<l) return LLONG_MAX;
        if (i<=l && j>=r) return value;
        return min(lc->query(i,j), rc->query(i,j));
    }
    void set(int i,int d) {
        if(l==r) value=d;
        else {
            if (i<=mid()) lc->set(i,d);
            else rc->set(i,d);
            value=min(lc->value,rc->value);
        }
    }
    inline int mid() { return (l+r)>>1; }
    inline int length() { return r-l+1; }
};
int f[MAXN][20],lg2[MAXN],depth[MAXN];
void init() {
    lg2[0]=-1,lg2[1]=0;
    for(int i=2;i<=n;i++) lg2[i]=lg2[i/2]+1;
    for(int j=1;j<=lg2[n];j++)
        for(int i=1;i<=n;i++)
            f[i][j]=f[f[i][j-1]][j-1];
}
int lca(int x,int y) {
    if (depth[x]<depth[y]) swap(x,y);
    int a=depth[x]-depth[y];
    for(int i=0;i<=lg2[a];i++) 
        if (a & (1<<i)) x=f[x][i];
    if (x==y) return y;
    for(int i=lg2[depth[x]];i>=0;i--)
        if (f[x][i] && f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
void dfs(int i,int pre) {
    depth[i]=depth[pre]+1;
    startPos[i]=++dfsNum;
    revStartPos[dfsNum]=i;
    forGraph(g,i,j,edge) if (j!=pre) dfs(j,i);
    endPos[i]=dfsNum;
}
signed main() {
    scanf("%lld%lld", &n, &q);
    for(int i=1;i<=n;i++) {
        int fa;
        scanf("%lld%lld", &fa, &v[i]);
        if (i!=1) {
            g.add(i,fa);
            g.add(fa,i);
            f[i][0]=fa;
        }
    }
    init();
    dfs(1,1);
    /*while(1) {
        int x,y;
        scanf("%lld%lld", &x, &y);
        printf("%lld\n", lca(x,y));
    }*/
    SegmentTree tree = SegmentTree(1,n);
    for(int i=1;i<=q;i++) {
        char c[2];int x;
        scanf("%s%lld", c, &x);
        if (c[0]=='V') {
            int y; scanf("%lld", &y);
            tree.set(startPos[x], y);
        } else if (c[0]=='E') {
            rt = x;
        } else {
            if (x==rt) {
                printf("%lld\n", tree.query(1, n));
            } else {
                if (startPos[x]<=startPos[rt] && endPos[x]>=startPos[rt]) {
                        int y=rt;
                        for(int j=lg2[depth[y]];j>=0;j--) if (depth[f[y][j]]>depth[x]) y=f[y][j];
                        printf("%lld\n", min(tree.query(1, startPos[y]-1), tree.query(endPos[y]+1, n)));
                } else {
                    printf("%lld\n", tree.query(startPos[x], endPos[x]));
                }
            }
        }
    }
    return 0;
}
