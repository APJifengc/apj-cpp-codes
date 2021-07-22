#include <bits/stdc++.h>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
using namespace std;
const int MAXN = 1005;
int n,q;
struct Graph {
    int fst[MAXN],nxt[MAXN<<1],w[MAXN<<1],to[MAXN<<1],tot;
    void add(int u,int v,int w) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        this->w[tot]=w;
        fst[u]=tot;
    }
}g;
struct BinaryIndexTree {
    int a[MAXN<<1];
#define lowbit(x) (x&(-x))
    void add(int i,int d) {
        while(i<=2*n) {
            a[i]+=d;
            i+=lowbit(i);
        }
    }
    int query(int i) {
        int res=0;
        while(i) {
            res+=a[i];
            i-=lowbit(i);
        }
        return res;
    }
    BinaryIndexTree() { memset(a, 0, sizeof a); }
}bit;
int l[MAXN],r[MAXN],depth[MAXN],dfsNum;
int f[MAXN][11];
void dfs(int i,int pre,int edge) {
    depth[i]=depth[pre]+1;
    f[i][0]=pre;
    l[i]=++dfsNum;
    bit.add(dfsNum, g.w[edge]);
    forGraph(g,i,j,edge) {
        if (j!=pre) {
            dfs(j,i,edge);
        }
    }
    ++dfsNum;
    bit.add(dfsNum, -g.w[edge]);
}
void init() {
    for(int j=1;j<=10;j++) {
        for(int i=1;i<=n;i++) {
            f[i][j]=f[f[i][j-1]][j-1];
        }
    }
}
int lca(int x,int y) {
    if (depth[x]<depth[y]) swap(x,y);
    int d=depth[x]-depth[y];
    for(int j=0;j<=10;j++) if(d&(1<<j)) x=f[x][j];
    if (x==y) return x;
    for(int j=10;j>=0;j--) if(f[x][j]!=f[y][j]) x=f[x][j],y=f[y][j];
    return f[x][0];
}
int main() {
    scanf("%d%d", &n, &q);
    for(int i=1;i<n;i++) {
        int x,y,w;
        scanf("%d%d%d", &x, &y, &w);
        g.add(x,y,w);
        g.add(y,x,w);
    }
    dfs(1,0,0);
    init();
    for(int i=1;i<=q;i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        printf("%d\n", bit.query(l[x])+bit.query(l[y])-2*bit.query(l[lca(x,y)]));
    }
    return 0;
}
